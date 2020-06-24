#ifndef _BIP_Engine_ConnectorExportPortItf_HPP_
#define _BIP_Engine_ConnectorExportPortItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "PortItf.hpp"

// used classes
#include "Port.hpp"

// referenced classes
class Connector;


class ConnectorExportPortItf : public virtual PortItf {
 public:
  // destructor
  virtual ~ConnectorExportPortItf();

  // opposites accessors
  Connector &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Connector &connector) { mHolder = &connector; }

 protected:
  // protected constructors
  ConnectorExportPortItf(const string &name);

  // opposites
  Connector *mHolder;
};

#endif // _BIP_Engine_ConnectorExportPortItf_HPP_
