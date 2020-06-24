#ifndef _BIP_Engine_NonDeterministicPetriNetError_HPP_
#define _BIP_Engine_NonDeterministicPetriNetError_HPP_

// inherited classes
#include <NonDeterministicPetriNetErrorItf.hpp>
#include "BipError.hpp"

class NonDeterministicPetriNetError : public virtual BipErrorItf, public BipError, public NonDeterministicPetriNetErrorItf {
 public:
  // constructors
  NonDeterministicPetriNetError(Atom &atom);

  // destructor
  virtual ~NonDeterministicPetriNetError();
};

#endif // _BIP_Engine_NonDeterministicPetriNetError_HPP_
