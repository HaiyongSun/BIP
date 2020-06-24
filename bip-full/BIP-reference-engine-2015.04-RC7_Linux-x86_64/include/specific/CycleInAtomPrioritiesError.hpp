#ifndef _BIP_Engine_CycleInAtomPrioritiesError_HPP_
#define _BIP_Engine_CycleInAtomPrioritiesError_HPP_

// inherited classes
#include <CycleInAtomPrioritiesErrorItf.hpp>
#include "BipError.hpp"

class CycleInAtomPrioritiesError : public virtual BipErrorItf, public BipError, public CycleInAtomPrioritiesErrorItf {
 public:
  // constructors
  CycleInAtomPrioritiesError();

  // destructor
  virtual ~CycleInAtomPrioritiesError();
};

#endif // _BIP_Engine_CycleInAtomPrioritiesError_HPP_
