#ifndef _BIP_Engine_CompoundExportPortItf_HPP_
#define _BIP_Engine_CompoundExportPortItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "PortItf.hpp"

// used classes
#include "Port.hpp"

// referenced classes
class Compound;

class Component;

class CompoundExportPortItf : public virtual PortItf {
 public:
  // destructor
  virtual ~CompoundExportPortItf();

  // getters for references
  const vector<Port *> &forwardPorts() const { return mForwardPorts; }
  bool hasForwardPorts() const { return !mForwardPorts.empty(); }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  CompoundExportPortItf(const string &name);

  // protected getters for references
  vector<Port *> &forwardPorts() { return mForwardPorts; }

  // protected setters for references
  void addForwardPort(Port &forwardPort) { mForwardPorts.push_back(&forwardPort); }

  // references
  vector<Port *> mForwardPorts;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_CompoundExportPortItf_HPP_
