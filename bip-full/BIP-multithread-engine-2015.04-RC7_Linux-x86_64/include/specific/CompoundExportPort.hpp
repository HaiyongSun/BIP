#ifndef _BIP_Engine_CompoundExportPort_HPP_
#define _BIP_Engine_CompoundExportPort_HPP_

// inherited classes
#include <CompoundExportPortItf.hpp>
#include "Port.hpp"
#include "PortValue.hpp"
#include "Resetable.hpp"

class BipError;

class CompoundExportPort : public virtual PortItf, public virtual Port, public CompoundExportPortItf {
 public:
  // constructors
  CompoundExportPort(const string &name);

  // destructor
  virtual ~CompoundExportPort();

  // operations
  virtual const vector<PortValue *> &portValues() const { return mPortValues; }
  virtual bool hasPortValues() const { return !portValues().empty(); }

  // specific
  virtual BipError &execute(PortValue& portValue);
  bool hasPortValue(PortValue& portValue) const;
  virtual ResetableItf &reset() { return mPortValues; }

 protected:
  void addForwardPort(Port &forwardPort);
  
  
  void recomputePortValues(vector<PortValue *> &portValues) const;

  /**
   * \brief Associate a port to a port value.
   */
  void mapPortValue(PortValue &portValue, Port &port) {
    // if it's a final destination, map it!
    if (port.type() == ATOM_EXPORT ||
        port.type() == CONNECTOR_EXPORT) {
      portValue.setPort(port);
    }
  }
  
  mutable Resetable<vector<PortValue *>, CompoundExportPort> mPortValues;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_CompoundExportPort_HPP_
