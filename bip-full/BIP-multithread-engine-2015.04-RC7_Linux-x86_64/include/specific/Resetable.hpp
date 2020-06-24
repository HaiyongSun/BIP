#ifndef _BIP_Engine_Resetable_HPP_
#define _BIP_Engine_Resetable_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include "FastMutex.hpp"
#include "Job.hpp"
#include "ExecuteConnectorJob.hpp"
#include "ExecuteAtomJob.hpp"

class Thread;


/** \brief 
 */
class ResetableItf {
 public:
  // constructor and destructor
  ResetableItf(bool checkThreadSafety = true) : mIsReset(false), mShouldBeInitialized(false), mCheckThreadSafety(checkThreadSafety), mIsThreadSafe(true) { 
#ifndef NDEBUG
    if (mIsReset) mShouldBeInitialized.store(true);
#endif
  }
  virtual ~ResetableItf() { }

  // operations
  void reset();
  void resetDependent();
  void dependsOn(ResetableItf &resetable);
  bool isDependentOf(ResetableItf &resetable) const;

  // setters and getters
  void setIsReset(bool b) const {
#ifndef NDEBUG
    mShouldBeInitialized.store(true);
#endif
    mIsReset.store(b);
  }
  bool isReset() const { return mIsReset.load(); }

  const vector<ExecuteConnectorJob *> &connectorJobs() const { return mConnectorJobs; }
  void addConnectorJob(ExecuteConnectorJob &connectorJob);
  const vector<ExecuteAtomJob *> &atomJobs() const { return mAtomJobs; }
  vector<ExecuteAtomJob *> allAtomJobs() const;
  void addAtomJob(ExecuteAtomJob &atomJob) { mAtomJobs.push_back(&atomJob); }

  void addTraversalThread(Thread &thrd);
  void addTraversalThreads(const vector<Thread *> &threads);

  bool checkThreadSafety() const { return mCheckThreadSafety; }
  bool isThreadSafe() const { return mIsThreadSafe; }

 protected:
  void allAtomJobs(vector<ExecuteAtomJob *> &ret, vector<const ResetableItf *> &visitedResetables) const;

  // protected attributes
  vector<ResetableItf *> mDependent;
  vector<ResetableItf *> mDependencies;
  mutable atomic<bool> mIsReset;
  mutable atomic<bool> mShouldBeInitialized;

  vector<ExecuteConnectorJob *> mConnectorJobs;
  vector<ExecuteAtomJob *> mAtomJobs;
  vector<Thread *> mTraversalThreads;

  bool mCheckThreadSafety;
  bool mIsThreadSafe;
};

template<class T, class C>
class Resetable : public ResetableItf {
 public:
  // constructor and destructor// constructor and destructor
  Resetable(C *instance, void (C::*method)(T& t) const) : mInstance(*instance), mMethod(method) { }
  Resetable(C *instance, void (C::*method)(T& t) const, const T &object) : mInstance(*instance), mMethod(method) { }
  Resetable(C *instance, void (C::*method)(T& t) const, const T &object, bool checkThreadSafety) : ResetableItf(checkThreadSafety), mInstance(*instance), mMethod(method) { }
  virtual ~Resetable() { }

  // operations
  operator const T & () const;
  void recompute() const;

 protected:
  // protected attributes
  C &mInstance;
  void (C::*mMethod)(T& t) const;
  mutable T mObject;

  mutable FastMutex mIsRecomputing;
};

inline
void ResetableItf::reset() {
  // test and set to true
  if (!mIsReset.exchange(true)) {
    // restart jobs
    for (vector<ExecuteConnectorJob *>::const_iterator connectorJobIt = connectorJobs().begin() ;
         connectorJobIt != connectorJobs().end() ;
         ++connectorJobIt) {
      ExecuteConnectorJob &connectorJob = **connectorJobIt;
      connectorJob.restart();
    }

    // reset dependencices
    resetDependent();
  }
}

inline
void ResetableItf::resetDependent() {
  for (vector<ResetableItf *>::const_iterator resetableIt = mDependent.begin() ;
       resetableIt != mDependent.end() ;
       ++resetableIt) {
    ResetableItf &resetable = **resetableIt;

    // propagate reset to dependent objects
    resetable.reset();
  }
}

inline
void ResetableItf::dependsOn(ResetableItf &resetable) {
  // should not have been reset previously
  assert(!mShouldBeInitialized);

  // set dependency links in both directions
  resetable.mDependent.push_back(this);
  mDependencies.push_back(&resetable);
}

inline
bool ResetableItf::isDependentOf(ResetableItf &resetable) const {
  return find(resetable.mDependent.begin(),
              resetable.mDependent.end(),
              this)
         != resetable.mDependent.end();
}

template<class T, class C>
inline Resetable<T, C>::operator const T & () const {
  recompute();
  
  return mObject;
}

template<class T, class C>
inline void Resetable<T, C>::recompute() const {
  // wait for completion of other computation
  if (checkThreadSafety()) {
    if (!isThreadSafe()) {
      mIsRecomputing.lock();
    }
  }

  // recompute if needed (if reset)
  if (mIsReset.load()) {
    // call recompute method
    (mInstance.*mMethod)(mObject);
    mIsReset.store(false);
  }

  // set ready for other computation
  if (checkThreadSafety()) {
    if (!isThreadSafe()) {
      mIsRecomputing.unlock();
    }
  }
}

#endif // _BIP_Engine_Resetable_HPP_
