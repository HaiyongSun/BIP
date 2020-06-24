#ifndef _BIP_Engine_Connector_HPP_
#define _BIP_Engine_Connector_HPP_

// inherited classes
#include <ConnectorItf.hpp>
#include "ConnectorExportPort.hpp"
#include "QuotedPortReference.hpp"

class Connector : public ConnectorItf {
 public:
  // constructors
  Connector(const string &name);

  // destructor
  virtual ~Connector();

  // specific
  bool isTopLevel() const;
  vector<Connector *> subConnectors() const;
  vector<Connector *> allSubConnectors() const;
  void updatePortValues();
  vector<InteractionValue *> enabledInteractions() const;
  vector<InteractionValue *> maximalInteractions() const;
  void release(const vector<Interaction *> &interactions) const;
  void release(const vector<InteractionValue *> &interactions) const;
  string fullName() const;

 protected:
  // protected setters for references
  void addPort(QuotedPortReference &port) {
    mPorts.push_back(&port);
    port.setHolder(*this);
  }

  void setExportedPort(ConnectorExportPort &exportedPort) {
    mExportedPort = &exportedPort;
    exportedPort.setHolder(*this);
  }

  // specific
  void enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> partialValues, unsigned int nextPortIndex) const;
};

#endif // _BIP_Engine_Connector_HPP_
