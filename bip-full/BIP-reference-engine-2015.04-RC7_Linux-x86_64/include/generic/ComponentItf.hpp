#ifndef _BIP_Engine_ComponentItf_HPP_
#define _BIP_Engine_ComponentItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// used classes
#include "Data.hpp"
#include "Port.hpp"

// referenced classes
class BipError;
class Compound;
class PortValue;

class Component;

class ComponentItf {
 public:
  // destructor
  virtual ~ComponentItf();

  // operations
  virtual BipError &execute(PortValue &portValue) = 0;
  virtual BipError &initialize() = 0;

  // getters for references
  const map<string, Port *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  const map<string, Data *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

  // getters for attributes
  const string &name() const { return mName; }
  const ComponentType &type() const { return mType; }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  ComponentItf(const string &name, const ComponentType &type);

  // protected getters for references
  map<string, Port *> &ports() { return mPorts; }
  map<string, Data *> &data() { return mData; }

  // protected setters for references
  void addPort(Port &port) { mPorts[port.name()] = &port; }
  void addData(Data &data) { mData[data.name()] = &data; }

  // attributes
  const string mName;
  const ComponentType mType;

  // references
  map<string, Port *> mPorts;
  map<string, Data *> mData;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_ComponentItf_HPP_
