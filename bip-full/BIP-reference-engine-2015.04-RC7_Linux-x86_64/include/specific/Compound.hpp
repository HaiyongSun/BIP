#ifndef _BIP_Engine_Compound_HPP_
#define _BIP_Engine_Compound_HPP_

// inherited classes
#include <CompoundItf.hpp>
#include "Component.hpp"
#include "CompoundExportPort.hpp"
#include "CompoundExportData.hpp"
#include "Connector.hpp"
#include "Priority.hpp"

class InteractionValue;
class AtomInternalPort;
class BipError;

class Compound : public virtual ComponentItf, public Component, public CompoundItf {
 public:
  // constructors
  Compound(const string &name);

  // destructor
  virtual ~Compound();

  // operations
  virtual BipError &execute(PortValue &portValue);
  virtual BipError &initialize();

  // specific
  BipError &execute(InteractionValue &interactionValue);
  BipError &update();
  BipError &recursiveUpdate();
  vector<InteractionValue *> interactions() const;
  virtual vector<AtomInternalPort *> internals() const;

  bool disableMaximalProgress() const { return mDisableMaximalProgress; }
  void setDisableMaximalProgress(bool disableMaximalProgress) { mDisableMaximalProgress = disableMaximalProgress; }
  void setDisableMaximalProgressForAllSubCompounds(bool disableMaximalProgress) ;

 protected:
  // protected setters for references
  void addComponent(Component &component) {
    mComponents[component.name()] = &component;
    component.setHolder(*this);
  }

  void addPort(CompoundExportPort &port) {
    mPorts[port.name()] = &port;
    port.setHolder(*this);
    Component::addPort(port);
  }

  void addPriority(Priority &priority) {
    mPriorities.push_back(&priority);
    priority.setHolder(*this);
  }

  void addConnector(Connector &connector) {
    mConnectors[connector.name()] = &connector;
    connector.setHolder(*this);
  }

  void addData(CompoundExportData &data) {
    mData[data.name()] = &data;
    data.setHolder(*this);
    Component::addData(data);
  }

  // specific
  BipError &detectCycleInPriorities() const;
  void updatePortValuesOfConnectors();
  void updatePortValuesOfExportedPorts();

  bool mDisableMaximalProgress;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_Compound_HPP_
