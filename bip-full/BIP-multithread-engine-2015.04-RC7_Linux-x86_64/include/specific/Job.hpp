#ifndef _BIP_Engine_Job_HPP_
#define _BIP_Engine_Job_HPP_

// inherited classes
#include "BipError.hpp"
#include "FastMutex.hpp"
#include "ReadyQueue.hpp"

class ResetableItf;
class Thread;

class Job {
 public:
  // constructors
  Job(ReadyQueue<Job> &readyQueue, bool highPriority = false);

  // destructor
  virtual ~Job();

  // getters
  bool isRestarted() const { return mIsRestarted; }

  // operations
  void after(Job &job);
  bool isAfter(Job &job);
  void exclude(Job &job);
  bool isExcluding(Job &job) { return find(job.mMutuallyExclusive.begin(), job.mMutuallyExclusive.end(), this) != job.mMutuallyExclusive.end(); }
  void dependsOn(ResetableItf &resetable);

  void execute();

  void restart();

  void preventEnqueuing() { mPreventEnqueuing.fetch_add(1); }
  void unpreventEnqueuing();

  const ReadyQueue<Job> &readyQueue() const { return mReadyQueue; }
  const vector<Thread *> &threads() const { return mReadyQueue.threads(); }

 protected:
  // protected operations
  virtual void realJob() = 0;

  void protect();
  void unprotect();

  void enqueue();

  // protected getters
  ReadyQueue<Job> &mReadyQueue;
  bool mHighPriority;

  atomic<bool> mIsRestarted;
  atomic<bool> mIsEnqueued;
  atomic<unsigned int> mPreventEnqueuing;

  // /!\ dependent jobs should be sorted by mIndex increasing
  // to avoid deadlock when reserving jobs
  vector<Job *> mMutuallyExclusive;
  vector<Job *> mBackMutuallyExclusive;
  vector<Job *> mAfter;
  vector<Job *> mBefore;
  bool mNeedProtection;

  // locking mechanisms
  FastBlockableMutex mMutualExclusion;
};

inline void Job::restart() {
  if (!mIsRestarted.exchange(true)) {
    for (vector<Job *>::const_iterator jobIt = mBefore.begin() ;
         jobIt != mBefore.end() ;
         ++jobIt) {
      Job &job = **jobIt;

      job.preventEnqueuing();
    }

    // restarted jobs require enqueuing at some point
#ifdef NDEBUG
    mIsEnqueued.store(false);
#else
    bool oldIsEnqueued = mIsEnqueued.exchange(false);
#endif

    assert(oldIsEnqueued == true);

    // enqueue if no before job has been restarted
    if (mPreventEnqueuing.load() == 0) {
      enqueue();
    }
  }
}

inline void Job::unpreventEnqueuing() {
  unsigned int oldPreventEnqueuing = mPreventEnqueuing.fetch_sub(1);

  assert(oldPreventEnqueuing > 0);

  if (oldPreventEnqueuing - 1 == 0) {
    enqueue();
  }
}

inline void Job::protect() {
  for (vector<Job *>::const_iterator jobIt = mBackMutuallyExclusive.begin() ;
       jobIt != mBackMutuallyExclusive.end() ;
       ++jobIt) {
    Job &job = **jobIt;

    job.mMutualExclusion.block();
  }

  mMutualExclusion.lock();
}

inline void Job::unprotect() {
  for (vector<Job *>::const_iterator jobIt = mBackMutuallyExclusive.begin() ;
       jobIt != mBackMutuallyExclusive.end() ;
       ++jobIt) {
    Job &job = **jobIt;

    job.mMutualExclusion.unblock();
  }

  mMutualExclusion.unlock();
}

#endif // _BIP_Engine_Job_HPP_
