#ifndef _BIP_Engine_PortValueItf_HPP_
#define _BIP_Engine_PortValueItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;


class PortValueItf {
 public:
  // destructor
  virtual ~PortValueItf();

  // operations
  virtual string toString() const = 0;

 protected:
  // protected constructors
  PortValueItf();
};

#endif // _BIP_Engine_PortValueItf_HPP_
