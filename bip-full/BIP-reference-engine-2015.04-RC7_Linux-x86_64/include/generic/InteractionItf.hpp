#ifndef _BIP_Engine_InteractionItf_HPP_
#define _BIP_Engine_InteractionItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class Connector;
class Interaction;
class Port;


class InteractionItf {
 public:
  // destructor
  virtual ~InteractionItf();

  // operations
  virtual void recycle() = 0;
  virtual const vector<Port *> &ports() const = 0;
  virtual bool hasPorts() const = 0;
  virtual void addPort(Port &port) = 0;
  virtual void removePort(Port &port) = 0;
  virtual bool isDefined() const = 0;
  virtual bool operator<=(const Interaction &interaction) const = 0;
  virtual bool operator==(const Interaction &interaction) const = 0;
  virtual bool operator!=(const Interaction &interaction) const = 0;
  virtual bool operator<(const Interaction &interaction) const = 0;
  virtual bool nonEmptyIntersection(const Interaction &interaction) const = 0;

  // getters for references
  const Connector &connector() const { return mConnector; }

 protected:
  // protected constructors
  InteractionItf(const Connector &connector);

  // references
  const Connector &mConnector;
};

#endif // _BIP_Engine_InteractionItf_HPP_
