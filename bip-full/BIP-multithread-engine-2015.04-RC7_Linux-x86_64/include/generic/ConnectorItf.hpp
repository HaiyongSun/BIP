#ifndef _BIP_Engine_ConnectorItf_HPP_
#define _BIP_Engine_ConnectorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// used classes
#include "ConnectorExportPort.hpp"

// referenced classes
class Compound;
class Interaction;
class InteractionValue;
class Port;
class PortValue;
class QuotedPortReference;

class Component;

class ConnectorItf {
 public:
  // destructor
  virtual ~ConnectorItf();

  // operations
  virtual PortValue &up(const InteractionValue &interaction) const = 0;
  virtual void down(InteractionValue &interaction, PortValue &portValue) const = 0;
  virtual Interaction &createInteraction() const = 0;
  virtual Interaction &createInteraction(const vector<Port *> &ports) const = 0;
  virtual InteractionValue &createInteractionValue(const Interaction &interaction, const vector<PortValue *> &values) const = 0;
  virtual void down(InteractionValue &interaction) const = 0;
  virtual bool guard(const InteractionValue &interaction) const = 0;
  virtual void releaseInteraction(Interaction &interaction) const = 0;
  virtual void releaseInteractionValue(InteractionValue &interactionValue) const = 0;
  virtual const vector<Interaction *> &interactions() const = 0;
  virtual bool canUpOnlyMaximalInteractions() const = 0;

  // getters for references
  const vector<QuotedPortReference *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  ConnectorExportPort &exportedPort() const { return *mExportedPort; }
  bool hasExportedPort() const { return mExportedPort != NULL; }

  // getters for attributes
  const string &name() const { return mName; }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  ConnectorItf(const string &name);

  // protected getters for references
  vector<QuotedPortReference *> &ports() { return mPorts; }
  ConnectorExportPort &exportedPort() { return *mExportedPort; }

  // protected setters for references
  virtual void addPort(QuotedPortReference &port) = 0;
  virtual void setExportedPort(ConnectorExportPort &exportedPort) = 0;

  // attributes
  const string mName;

  // references
  vector<QuotedPortReference *> mPorts;
  ConnectorExportPort *mExportedPort;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_ConnectorItf_HPP_
