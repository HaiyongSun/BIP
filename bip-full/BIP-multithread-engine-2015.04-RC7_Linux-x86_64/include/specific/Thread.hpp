#ifndef _BIP_Engine_Thread_HPP_
#define _BIP_Engine_Thread_HPP_

// inherited classes
#include "Atom.hpp"
#include "AtomInternalPort.hpp"
#include "PortValue.hpp"

class Job;
template<class T> class ReadyQueue;

class Thread {
 public:
  // constructors
  Thread(ReadyQueue<Job> &jobs);

  // destructor
  virtual ~Thread();

  // operations
  void start();
  void join() { mThread->join(); }

  // getter / setters
  ReadyQueue<Job> &jobs() { return mJobs; }
  bool hasJob() const { return mJob != NULL; }
  Job &job() const { return *mJob; }
  Job *jobPtr() const { return mJob; }

 protected:
  // protected operations
  void execute();

  // protected getter / setters
  void setJob(Job &job) { mJob = &job; }

  ReadyQueue<Job> &mJobs;
  thread *mThread;
  Job *mJob;
};

#endif // _BIP_Engine_Thread_HPP_
