#ifndef _BIP_Engine_Initializable_HPP_
#define _BIP_Engine_Initializable_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

/** \brief 
 */
class InitializableItf {
 public:
  // constructor and destructor
  InitializableItf(bool initialized = false) : mIsInitialized(initialized) { }
  virtual ~InitializableItf() { }

  // setters and getters
  void dependsOn(InitializableItf &initializable) { mDependencies.push_back(&initializable); }

  // operations
  void initialize();

 protected:
  // operations
  virtual void compute() = 0;

  bool isInitialized() const { return mIsInitialized; }
  void initialized() { mIsInitialized = true; }

  // protected attributes
  vector<InitializableItf *> mDependencies;
  mutable bool mIsInitialized;
};

template<class T, class C>
class Initializable : public InitializableItf {
 public:
  // constructor and destructor
  Initializable(C *instance, void (C::*method)(T& t)) : mInstance(*instance), mMethod(method) { }
  Initializable(bool initialized, C *instance, void (C::*method)(T& t)) : InitializableItf(initialized), mInstance(*instance), mMethod(method) { }
  virtual ~Initializable() { }

  // setters and getters
  const T &value() const { assert(isInitialized()); return mObject; }

 protected:
  // operations
  virtual void compute() { (mInstance.*mMethod)(mObject); }

  // protected attributes
  C &mInstance;
  void (C::*mMethod)(T& t);
  T mObject;
};

#endif // _BIP_Engine_Initializable_HPP_
