#ifndef _BIP_Engine_ConnectorExportPort_HPP_
#define _BIP_Engine_ConnectorExportPort_HPP_

// inherited classes
#include <ConnectorExportPortItf.hpp>
#include "Port.hpp"
#include <InteractionValue.hpp>
#include <PortValue.hpp>
#include <Resetable.hpp>

class BipError;

class ConnectorExportPort : public virtual PortItf, public virtual Port, public ConnectorExportPortItf {
 public:
  // constructors
  ConnectorExportPort(const string &name);

  // destructor
  virtual ~ConnectorExportPort();

  // operations
  virtual const vector<PortValue *> &portValues() const { return mPortValues; }
  virtual bool hasPortValues() const { return !portValues().empty(); }

  // specific
  virtual BipError &execute(PortValue& portValue);
  void updatePortValues() const;

  virtual ResetableItf &reset() { return mPortValues; }
  Resetable<vector<PortValue *>, ConnectorExportPort> &maximalPortValues() const { return mMaximalPortValues; }

  bool hasMaximalPortValues() const {
    const vector<PortValue *> &portValues = maximalPortValues();
    return !portValues.empty();
  }

 protected:
  void recomputePortValues(vector<PortValue *> &portValues) const;
  void recomputeMaximalPortValues(vector<PortValue *> &portValues) const;
  
  mutable Resetable<vector<PortValue *>, ConnectorExportPort> mPortValues;
  mutable Resetable<vector<PortValue *>, ConnectorExportPort> mMaximalPortValues;

  /**
   * \brief Associate an interaction value to a port value.
   */
  void mapPortValue(PortValue &portValue, InteractionValue &interactionValue) {
    portValue.setInteraction(interactionValue);
  }
};

#endif // _BIP_Engine_ConnectorExportPort_HPP_
