#ifndef _BIP_Engine_CompoundExportPort_HPP_
#define _BIP_Engine_CompoundExportPort_HPP_

// inherited classes
#include <CompoundExportPortItf.hpp>
#include "Port.hpp"
#include "PortValue.hpp"

class BipError;

class CompoundExportPort : public virtual PortItf, public virtual Port, public CompoundExportPortItf {
 public:
  // constructors
  CompoundExportPort(const string &name);

  // destructor
  virtual ~CompoundExportPort();

  // operations
  virtual const vector<PortValue *> &portValues() const { return mPortValues; }
  virtual bool hasPortValues() const { return !mPortValues.empty(); }

  // specific
  BipError &execute(PortValue& portValue);
  void updatePortValues();

  bool hasPortValue(PortValue& portValue) const;

  vector<PortValue *> &portValues() { return mPortValues; }
  void addPortValue(PortValue &portValue) { mPortValues.push_back(&portValue); }
  void clearPortValues() { mPortValues.clear(); }

 protected:
  vector<PortValue *> mPortValues;

  /**
   * \brief Mapped port values to port.
   */
  const map<PortValue *, Port *> &mappedPortValues() const { return mMappedPortValues; }

  /**
   * \brief Mapped port values to port.
   */
  map<PortValue *, Port *> &mappedPortValues() { return mMappedPortValues; }

  /**
   * \brief Associate a port to a port value.
   */
  void mapPortValue(PortValue &portValue, Port &port) { mMappedPortValues[&portValue] = &port; }

  /**
   * \brief Clear association of ports to port values.
   */
  void clearMappedPortValues() { mMappedPortValues.clear(); }

  /**
   * \brief Associate between each port value exposed by ports their corresponding forward ports.
   */
  map<PortValue *, Port *> mMappedPortValues;
};

#endif // _BIP_Engine_CompoundExportPort_HPP_
