#ifndef _BIP_Engine_QuotedPortReferenceItf_HPP_
#define _BIP_Engine_QuotedPortReferenceItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class Connector;
class Port;


class QuotedPortReferenceItf {
 public:
  // destructor
  virtual ~QuotedPortReferenceItf();

  // getters for references
  Port &port() const { return mPort; }

  // getters for attributes
  const bool &trigger() const { return mTrigger; }

  // opposites accessors
  Connector &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Connector &connector) { mHolder = &connector; }

 protected:
  // protected constructors
  QuotedPortReferenceItf(Port &port, const bool &trigger);

  // attributes
  const bool mTrigger;

  // references
  Port &mPort;

  // opposites
  Connector *mHolder;
};

#endif // _BIP_Engine_QuotedPortReferenceItf_HPP_
