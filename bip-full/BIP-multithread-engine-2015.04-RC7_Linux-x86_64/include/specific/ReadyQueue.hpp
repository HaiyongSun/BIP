#ifndef _BIP_Engine_ReadyQueue_HPP_
#define _BIP_Engine_ReadyQueue_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include <sys/time.h>
#include <time.h>

class Thread;

/** \brief Thread-safe implementation of a ready queue.
 *
 * 
 */
template<class T>
class ReadyQueue {
 public:
  // constructors
  ReadyQueue(unsigned int capacity) : mCapacity(0), mIsStopped(false), mPopIndex(0), mPushIndex(0), mInactive(false) {
    // round capacity to a power of 2
    mCapacity = 1;

    while (capacity != 0) {
      capacity >>= 1;
      mCapacity <<= 1;
    }

    // mask for keeping only relevant bits
    mCapacityMask = mCapacity - 1;

    // update the total number of queues
    ++mNbQueues;

    // allocate places
    mArray = new atomic<T *>[mCapacity];
    mWaiters = new atomic<unsigned int>[mCapacity];
    mMutex = new mutex[mCapacity];
    mConditionVariable = new condition_variable[mCapacity];

    // initialize places to empty (i.e. NULL)
    for (unsigned int i = 0 ; i < mCapacity ; ++i) {
      mArray[i].store(NULL);
      mWaiters[i].store(0);
    }
  }

  // destructor
  virtual ~ReadyQueue();

  // getters / setters
  bool empty() const;
  void stop();

  T *waitAndPop();
  void push(T &t);
  void push_front(T &t);

  void addThread(Thread &thrd) { mThreads.push_back(&thrd); }
  const vector<Thread *> &threads() const { return mThreads; }

  static bool noActivity() { return mNbInactiveQueues.load() == mNbQueues; }
  static void waitForNoActivity();

 protected:
  static void checkActivity();

  void setActive() { if (mInactive.exchange(false)) { mNbInactiveQueues.fetch_sub(1); } }
  void setInactive() { if (!mInactive.exchange(true)) { mNbInactiveQueues.fetch_add(1); } checkActivity(); }

  // capacity
  unsigned int mCapacity;
  unsigned int mCapacityMask;

  // status: active or not
  atomic<bool> mIsStopped;

  // indexes for pop and push
  atomic<unsigned int> mPopIndex;
  atomic<unsigned int> mPushIndex;

  // synchronization variables
  atomic<unsigned int> *mWaiters;
  mutex *mMutex;
  condition_variable *mConditionVariable;

  // content of the queue
  atomic<T *> *mArray;
  
  // number of potential waiters for pop
  vector<Thread *> mThreads;

  //
  atomic<bool> mInactive;

  static unsigned int mNbQueues;
  static atomic<unsigned int> mNbInactiveQueues;
  static mutex mGlobalMutex;
  static condition_variable mGlobalConditionVariable;
};

template<class T>
inline ReadyQueue<T>::~ReadyQueue() {
}

template<class T>
inline bool ReadyQueue<T>::empty() const {
  // order is critical to avoid spurious empty() == true
  unsigned int popIndex = mPopIndex.load();
  unsigned int pushIndex = mPushIndex.load();

  // empty if pressure = nb of threads
  return popIndex == pushIndex + mThreads.size();
}

template<class T>
inline void ReadyQueue<T>::stop() {
  // mark inactive to prevent from further push
  mIsStopped.store(true);

  // purge the queue
  for (unsigned int i = 0 ; i < mCapacity ; ++i) {
    mArray[i].store(NULL);
    unique_lock<mutex> lock(mMutex[i]);
    mConditionVariable[i].notify_all();
  }

  // inform inactivity
  setInactive();
}

template<class T>
inline T *ReadyQueue<T>::waitAndPop() {
  T *ret = NULL;

  // first try
  unsigned int popIndex = mPopIndex.fetch_add(1);
  unsigned int myIndex = popIndex;

  // implements circular indexing
  if (myIndex >= mCapacity) {
    myIndex &= mCapacityMask;
  }

  ret = mArray[myIndex].exchange(NULL);

  while (ret == NULL && mPushIndex.load() > popIndex && !mIsStopped.load()) {
    ret = mArray[myIndex].exchange(NULL);
  }

  // wait notify/mechanism
  if (ret == NULL && !mIsStopped.load()) {
    mWaiters[myIndex].fetch_add(1);

    unique_lock<mutex> lock(mMutex[myIndex]);

    // retry
    ret = mArray[myIndex].exchange(NULL);

    while (ret == NULL && !mIsStopped.load()) {
      // check for inactivity
      if (empty()) {
        setInactive();
      }

      // wait for new values
      mConditionVariable[myIndex].wait(lock);

      // retry
      ret = mArray[myIndex].exchange(NULL);
    }

    mWaiters[myIndex].fetch_sub(1);
  }

  if (mIsStopped.load()) ret = NULL;

  return ret;
}

template<class T>
inline void ReadyQueue<T>::push(T &t) {
  if (!mIsStopped.load()) {
    // compute the correct index for pushing
    unsigned int myIndex = mPushIndex.fetch_add(1);

    // implements circular indexing
    if (myIndex >= mCapacity) {
      myIndex &= mCapacityMask;

      if (mPopIndex >= mCapacity) {
        // order is critical to avoid spurious empty() == true
        mPopIndex.fetch_and(mCapacityMask);
        mPushIndex.fetch_and(mCapacityMask);
      }
    }

    // perform the push in the queue
    T *nullValue = NULL;

    while (!((mArray[myIndex]).compare_exchange_weak(nullValue, &t)) && !mIsStopped.load()) {
      nullValue = NULL;
    }

    // notify waiting threads
    if (mWaiters[myIndex].load() > 0 && mArray[myIndex].load() != NULL) {
      unique_lock<mutex> lock(mMutex[myIndex]);
      mConditionVariable[myIndex].notify_one();
      setActive();
    }
  }
}

template<class T>
inline void ReadyQueue<T>::push_front(T &t) {
  push(t);
}

template<class T>
inline void ReadyQueue<T>::waitForNoActivity() {
  unique_lock<mutex> lock(mGlobalMutex);

  while (!noActivity()) {
    mGlobalConditionVariable.wait(lock);
  }
}

template<class T>
inline void ReadyQueue<T>::checkActivity() {
  if (noActivity()) {
    unique_lock<mutex> lock(mGlobalMutex);
    mGlobalConditionVariable.notify_all();
  }
}

template<class T>
unsigned int ReadyQueue<T>::mNbQueues(0);

template<class T>
atomic<unsigned int> ReadyQueue<T>::mNbInactiveQueues(0);

template<class T>
mutex ReadyQueue<T>::mGlobalMutex;

template<class T>
condition_variable ReadyQueue<T>::mGlobalConditionVariable;


#endif // _BIP_Engine_ReadyQueue_HPP_
