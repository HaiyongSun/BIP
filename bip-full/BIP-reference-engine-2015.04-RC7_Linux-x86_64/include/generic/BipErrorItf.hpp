#ifndef _BIP_Engine_BipErrorItf_HPP_
#define _BIP_Engine_BipErrorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;


class BipErrorItf {
 public:
  // destructor
  virtual ~BipErrorItf();

  // getters for attributes
  const ErrorType &type() const { return mType; }

 protected:
  // protected constructors
  BipErrorItf(const ErrorType &type);

  // attributes
  const ErrorType mType;
};

#endif // _BIP_Engine_BipErrorItf_HPP_
