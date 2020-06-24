#ifndef _BIP_Engine_CompoundItf_HPP_
#define _BIP_Engine_CompoundItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "ComponentItf.hpp"

// used classes
#include "Component.hpp"
#include "CompoundExportData.hpp"
#include "CompoundExportPort.hpp"
#include "Connector.hpp"
#include "Priority.hpp"

class Component;

class CompoundItf : public virtual ComponentItf {
 public:
  // destructor
  virtual ~CompoundItf();

  // getters for references
  const map<string, Component *> &components() const { return mComponents; }
  bool hasComponents() const { return !mComponents.empty(); }
  const map<string, CompoundExportPort *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  const vector<Priority *> &priorities() const { return mPriorities; }
  bool hasPriorities() const { return !mPriorities.empty(); }
  const map<string, Connector *> &connectors() const { return mConnectors; }
  bool hasConnectors() const { return !mConnectors.empty(); }
  const map<string, CompoundExportData *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

 protected:
  // protected constructors
  CompoundItf(const string &name);

  // protected getters for references
  map<string, Component *> &components() { return mComponents; }
  map<string, CompoundExportPort *> &ports() { return mPorts; }
  vector<Priority *> &priorities() { return mPriorities; }
  map<string, Connector *> &connectors() { return mConnectors; }
  map<string, CompoundExportData *> &data() { return mData; }

  // protected setters for references
  virtual void addComponent(Component &component) = 0;
  virtual void addPort(CompoundExportPort &port) = 0;
  virtual void addPriority(Priority &priority) = 0;
  virtual void addConnector(Connector &connector) = 0;
  virtual void addData(CompoundExportData &data) = 0;

  // references
  map<string, Component *> mComponents;
  map<string, CompoundExportPort *> mPorts;
  vector<Priority *> mPriorities;
  map<string, Connector *> mConnectors;
  map<string, CompoundExportData *> mData;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_CompoundItf_HPP_
