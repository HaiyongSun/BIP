#ifndef _BIP_Engine_Resetable_HPP_
#define _BIP_Engine_Resetable_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

/** \brief 
 */
class ResetableItf {
 public:
  // constructor and destructor
  ResetableItf() : mIsReset(false), mShouldBeInitialized(false) {
#ifndef NDEBUG
    if (mIsReset) mShouldBeInitialized = true;
#endif
  }
  virtual ~ResetableItf() { }

  // setters and getters
  void dependsOn(ResetableItf &resetable) {
    // should not have been reset previously
    assert(!mShouldBeInitialized);

    resetable.mDependent.push_back(this);
  }
  bool isDependentOf(ResetableItf &resetable) const;

  // operations
  void reset();

  // setters and getters
  void setIsReset(bool b) const {
#ifndef NDEBUG
    mShouldBeInitialized = true;
#endif
    mIsReset = b;
  }
  bool isReset() const { return mIsReset; }

 protected:
  // protected attributes
  vector<ResetableItf *> mDependent;
  mutable bool mIsReset;
  mutable bool mShouldBeInitialized;
};

inline bool ResetableItf::isDependentOf(ResetableItf &resetable) const {
  return find(resetable.mDependent.begin(),
              resetable.mDependent.end(),
              this)
         != resetable.mDependent.end();
}


template<class T, class C>
class Resetable : public ResetableItf {
 public:
  // constructor and destructor
  Resetable(C *instance, void (C::*method)(T& t) const) : mInstance(*instance), mMethod(method) { }
  Resetable(C *instance, void (C::*method)(T& t) const, const T &object) : mInstance(*instance), mMethod(method), mObject(object) { }
  virtual ~Resetable() { }

  // operations
  operator const T & () const;

 protected:
  // protected attributes
  C &mInstance;
  void (C::*mMethod)(T& t) const;
  mutable T mObject;
};

template<class T, class C>
Resetable<T, C>::operator const T & () const {
  if (isReset()) {
    // call recompute method
    (mInstance.*mMethod)(mObject);

    // mark as up-to-date
    setIsReset(false);
  }

  return mObject;
}

#endif // _BIP_Engine_Resetable_HPP_
