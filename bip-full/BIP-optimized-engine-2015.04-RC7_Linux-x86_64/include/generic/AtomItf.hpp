#ifndef _BIP_Engine_AtomItf_HPP_
#define _BIP_Engine_AtomItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "ComponentItf.hpp"

// used classes
#include "AtomExportData.hpp"
#include "AtomExportPort.hpp"
#include "AtomInternalPort.hpp"
#include "Component.hpp"

// referenced classes
class BipError;
class PortValue;

class Component;

class AtomItf : public virtual ComponentItf {
 public:
  // destructor
  virtual ~AtomItf();

  // operations
  virtual BipError &initialize() = 0;
  virtual BipError &execute(PortValue &portValue) = 0;
  virtual string toString() const = 0;

  // getters for references
  const map<string, AtomInternalPort *> &internalPorts() const { return mInternalPorts; }
  bool hasInternalPorts() const { return !mInternalPorts.empty(); }
  const map<string, AtomExportPort *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  const map<string, AtomExportData *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

 protected:
  // protected constructors
  AtomItf(const string &name);

  // protected getters for references
  map<string, AtomInternalPort *> &internalPorts() { return mInternalPorts; }
  map<string, AtomExportPort *> &ports() { return mPorts; }
  map<string, AtomExportData *> &data() { return mData; }

  // protected setters for references
  virtual void addInternalPort(AtomInternalPort &internalPort) = 0;
  virtual void addPort(AtomExportPort &port) = 0;
  virtual void addData(AtomExportData &data) = 0;

  // references
  map<string, AtomInternalPort *> mInternalPorts;
  map<string, AtomExportPort *> mPorts;
  map<string, AtomExportData *> mData;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_AtomItf_HPP_
