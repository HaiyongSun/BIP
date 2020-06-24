#ifndef _BIP_Engine_ExecuteAtomJob_HPP_
#define _BIP_Engine_ExecuteAtomJob_HPP_

// inherited classes
#include <Job.hpp>
#include <BipError.hpp>
#include "PortValue.hpp"
#include "AtomInternalPort.hpp"
#include "ReadyQueue.hpp"

class Atom;
class PortValue;
class BipError;
class Logger;
class ExecuteConnectorJob;

class ExecuteAtomJob : public Job {
 public:
  // constructors
  ExecuteAtomJob(Atom &atom);

  // destructor
  virtual ~ExecuteAtomJob();

  // getters for references
  Atom &atom() const { return mAtom; }
  PortValue &portValue() const { return *mPortValue; }
  bool hasPortValue() const { return mPortValue != NULL; }
  AtomInternalPort &internalPort() const { return *mInternalPort; }
  bool hasInternalPort() const { return mInternalPort != NULL; }
  Logger &logger() { return *mLogger; }
  bool hasLogger() const { return mLogger != NULL; }

  GroupableFastMutex &lock() { return mReserved; }
  const vector<ExecuteConnectorJob *> &reservers() const { return mReservers; }

  // setters
  void setPortValue(PortValue &portValue);
  void clearPortValue() { mPortValue = NULL; }
  void setInternalPort(AtomInternalPort &internalPort);
  void clearInternalPort() { mInternalPort = NULL; }
  void setLogger(Logger &logger) { mLogger = &logger; }
  void clearLogger() { mLogger = NULL; }

  void addReserver(ExecuteConnectorJob &connectorJob);

  // operations
  void initialize();

 protected:
  // operations
  virtual void realJob();

  BipError &initializeJob();
  BipError &portValueJob();
  BipError &internalPortJob();

  Atom &mAtom;
  PortValue *mPortValue;
  AtomInternalPort *mInternalPort;
  Logger *mLogger;

  vector<AtomInternalPort *> mNonExportedPorts;

  // reservation mechanisms
  GroupableFastMutex mReserved;
  vector<ExecuteConnectorJob *> mReservers;
};

#endif // _BIP_Engine_ExecuteAtomJob_HPP_
