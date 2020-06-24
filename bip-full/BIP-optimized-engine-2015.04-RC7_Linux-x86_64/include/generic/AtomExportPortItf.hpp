#ifndef _BIP_Engine_AtomExportPortItf_HPP_
#define _BIP_Engine_AtomExportPortItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "PortItf.hpp"

// used classes
#include "Port.hpp"

// referenced classes
class Atom;
class AtomInternalPort;

class Component;

class AtomExportPortItf : public virtual PortItf {
 public:
  // destructor
  virtual ~AtomExportPortItf();

  // operations
  virtual bool isReset() const = 0;

  // getters for references
  const vector<AtomInternalPort *> &internalPorts() const { return mInternalPorts; }
  bool hasInternalPorts() const { return !mInternalPorts.empty(); }

  // opposites accessors
  Atom &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Atom &atom) { mHolder = &atom; }

 protected:
  // protected constructors
  AtomExportPortItf(const string &name);

  // protected getters for references
  vector<AtomInternalPort *> &internalPorts() { return mInternalPorts; }

  // protected setters for references
  void addInternalPort(AtomInternalPort &internalPort) { mInternalPorts.push_back(&internalPort); }

  // references
  vector<AtomInternalPort *> mInternalPorts;

  // opposites
  Atom *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_AtomExportPortItf_HPP_
