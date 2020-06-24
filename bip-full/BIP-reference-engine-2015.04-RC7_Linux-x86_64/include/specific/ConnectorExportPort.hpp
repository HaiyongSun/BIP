#ifndef _BIP_Engine_ConnectorExportPort_HPP_
#define _BIP_Engine_ConnectorExportPort_HPP_

// inherited classes
#include <ConnectorExportPortItf.hpp>
#include "Port.hpp"
#include <InteractionValue.hpp>

class BipError;

class ConnectorExportPort : public virtual PortItf, public virtual Port, public ConnectorExportPortItf {
 public:
  // constructors
  ConnectorExportPort(const string &name);

  // destructor
  virtual ~ConnectorExportPort();

  // operations
  virtual const vector<PortValue *> &portValues() const { return mPortValues; }
  virtual bool hasPortValues() const { return !mPortValues.empty(); }

  // specific
  BipError &execute(PortValue& portValue);
  void updatePortValues();
  InteractionValue& interaction(PortValue &portValue) const;

  vector<PortValue *> &portValues() { return mPortValues; }
  void addPortValue(PortValue &portValue) { mPortValues.push_back(&portValue); }
  void clearPortValues() { mPortValues.clear(); }

  vector<PortValue *> &maximalPortValues() { return mMaximalPortValues; }
  const vector<PortValue *> &maximalPortValues() const { return mMaximalPortValues; }
  bool hasMaximalPortValues() const { return !mMaximalPortValues.empty(); }
  void addMaximalPortValue(PortValue &portValue) { mMaximalPortValues.push_back(&portValue); }
  void clearMaximalPortValues() { mMaximalPortValues.clear(); }


 protected:
  vector<PortValue *> mPortValues;
  vector<PortValue *> mMaximalPortValues;

  /**
   * \brief Mapped port values to interaction values.
   */
  const map<PortValue *, InteractionValue *> &mappedPortValues() const { return mMappedPortValues; }

  /**
   * \brief Mapped port values to interaction values.
   */
  map<PortValue *, InteractionValue *> &mappedPortValues() { return mMappedPortValues; }

  /**
   * \brief Associate an interaction value to a port value.
   */
  void mapPortValue(PortValue &portValue, InteractionValue &interactionValue) { mMappedPortValues[&portValue] = &interactionValue; }

  /**
   * \brief Clear association of interaction values to port values.
   */
  void clearMappedPortValues();

  /**
   * \brief Association between each port value exposed by ports their corresponding interaction values.
   */
  map<PortValue *, InteractionValue *> mMappedPortValues;
};

#endif // _BIP_Engine_ConnectorExportPort_HPP_
