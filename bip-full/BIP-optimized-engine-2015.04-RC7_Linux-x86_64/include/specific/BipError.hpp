#ifndef _BIP_Engine_BipError_HPP_
#define _BIP_Engine_BipError_HPP_

// inherited classes
#include <BipErrorItf.hpp>

class BipError : public virtual BipErrorItf {
 public:
  // destructor
  virtual ~BipError();

  // specific
  static BipError NoError;

 protected:
  // constructors
  BipError(const ErrorType &type);
};

#endif // _BIP_Engine_BipError_HPP_
