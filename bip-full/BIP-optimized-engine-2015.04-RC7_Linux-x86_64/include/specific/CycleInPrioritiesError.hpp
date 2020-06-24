#ifndef _BIP_Engine_CycleInPrioritiesError_HPP_
#define _BIP_Engine_CycleInPrioritiesError_HPP_

// inherited classes
#include <CycleInPrioritiesErrorItf.hpp>
#include "BipError.hpp"

class CycleInPrioritiesError : public virtual BipErrorItf, public BipError, public CycleInPrioritiesErrorItf {
 public:
  // constructors
  CycleInPrioritiesError();

  // destructor
  virtual ~CycleInPrioritiesError();
};

#endif // _BIP_Engine_CycleInPrioritiesError_HPP_
