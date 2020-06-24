#ifndef _BIP_Engine_InteractionValueItf_HPP_
#define _BIP_Engine_InteractionValueItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class Interaction;
class PortValue;


class InteractionValueItf {
 public:
  // destructor
  virtual ~InteractionValueItf();

  // operations
  virtual const Interaction &interaction() const = 0;
  virtual const vector<PortValue *> &portValues() const = 0;
  virtual bool hasPortValues() const = 0;

 protected:
  // protected constructors
  InteractionValueItf();
};

#endif // _BIP_Engine_InteractionValueItf_HPP_
