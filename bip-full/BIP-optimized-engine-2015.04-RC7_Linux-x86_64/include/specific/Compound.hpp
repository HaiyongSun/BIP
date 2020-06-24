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
class CycleInPriorities;

class Compound : public virtual ComponentItf, public Component, public CompoundItf {
 public:
  // constructors
  Compound(const string &name);

  // destructor
  virtual ~Compound();

  // specific
  virtual BipError &execute(PortValue &portValue);
  BipError &execute(InteractionValue &interactionValue);
  virtual BipError &initialize();
  BipError &update();
  void resetAll();
  BipError &recursiveUpdate();

  const vector<Connector *> &nonExportedConnectors() const { return mNonExportedConnectors.value(); }
  const vector<AtomInternalPort *> &nonExportedInternalPorts() const { return mNonExportedInternalPorts.value(); }

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
  void computeNonExportedConnectors(vector<Connector *> &nonExportedConnectors);
  void computeNonExportedInternalPorts(vector<AtomInternalPort *> &ports);
  void computeAllCyclesInPriorities(set<CycleInPriorities *> &cycles);

  void computeCycles() const;
  void allCyclesFrom(Priority &priority, set<CycleInPriorities> &cycles, vector<Priority *> &path);

  BipError &initializeAllAtoms();
  void initializeAllConnectorsPriorities();

  const set<CycleInPriorities *> &allCyclesInPriorities() const { return mAllCyclesInPriorities.value(); }

  mutable Initializable<vector<Connector *>, Compound> mNonExportedConnectors;
  mutable Initializable<vector<AtomInternalPort *>, Compound> mNonExportedInternalPorts;
  mutable Initializable<set<CycleInPriorities *>, Compound> mAllCyclesInPriorities;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_Compound_HPP_
