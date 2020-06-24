#ifndef _BIP_Engine_ExecuteConnectorJob_HPP_
#define _BIP_Engine_ExecuteConnectorJob_HPP_

// inherited classes
#include <Job.hpp>
#include <BipError.hpp>
#include "ReadyQueue.hpp"

class Connector;
class Logger;
class ExecuteAtomJob;

class ExecuteConnectorJob : public Job {
 public:
  // constructors
  ExecuteConnectorJob(Connector &connector);

  // destructor
  virtual ~ExecuteConnectorJob();

  // getters for references
  Connector &connector() const { return mConnector; }
  Logger &logger() { return *mLogger; }
  bool hasLogger() const { return mLogger != NULL; }
  
  // setters
  void setLogger(Logger &logger) { mLogger = &logger; }
  void clearLogger() { mLogger = NULL; }

  // operations
  void initialize();
  void initializeGroup() { mReserveGroup.initialize(); }
  BipError &detectCycleInPriorities() const;

 protected:
  // operations
  virtual void realJob();

  bool tryToReserveAtoms() { return mReserveGroup.tryToLock(); }
  void unreserveNonRestartedAtoms();

  Connector &mConnector;
  Logger *mLogger;

  // reservation mechanisms
  FastMutexGroup mReserveGroup;
  vector<ExecuteAtomJob *> mAllAtomJobs;
};

#endif // _BIP_Engine_ExecuteConnectorJob_HPP_
