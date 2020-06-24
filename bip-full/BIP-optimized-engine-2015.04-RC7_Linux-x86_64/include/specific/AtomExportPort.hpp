#ifndef _BIP_Engine_AtomExportPort_HPP_
#define _BIP_Engine_AtomExportPort_HPP_

// inherited classes
#include <AtomExportPortItf.hpp>
#include "Port.hpp"
#include "PortValue.hpp"

class BipError;

class AtomExportPort : public virtual PortItf, public virtual Port, public AtomExportPortItf {
 public:
  // constructors
  AtomExportPort(const string &name);

  // destructor
  virtual ~AtomExportPort();

  // specific
  virtual BipError &execute(PortValue &portValue);
  virtual ResetableItf &reset() { return mReset; }

 protected:
  void addInternalPort(AtomInternalPort &internalPort);

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);

  // specific
  ResetableItf mReset;
};

#endif // _BIP_Engine_AtomExportPort_HPP_
