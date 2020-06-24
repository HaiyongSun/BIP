#ifndef _BIP_Engine_AtomInternalPortItf_HPP_
#define _BIP_Engine_AtomInternalPortItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class Atom;
class PortValue;


class AtomInternalPortItf {
 public:
  // destructor
  virtual ~AtomInternalPortItf();

  // operations
  virtual PortValue &portValue() const = 0;
  virtual bool hasPortValue() const = 0;
  virtual void setPortValue(PortValue &portValue) = 0;
  virtual void clearPortValue() = 0;

  // getters for attributes
  const string &name() const { return mName; }

  // opposites accessors
  Atom &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Atom &atom) { mHolder = &atom; }

 protected:
  // protected constructors
  AtomInternalPortItf(const string &name);

  // attributes
  const string mName;

  // opposites
  Atom *mHolder;
};

#endif // _BIP_Engine_AtomInternalPortItf_HPP_
