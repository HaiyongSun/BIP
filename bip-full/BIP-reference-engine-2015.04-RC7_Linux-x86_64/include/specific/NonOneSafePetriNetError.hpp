#ifndef _BIP_Engine_NonOneSafePetriNetError_HPP_
#define _BIP_Engine_NonOneSafePetriNetError_HPP_

// inherited classes
#include <NonOneSafePetriNetErrorItf.hpp>
#include "BipError.hpp"

class NonOneSafePetriNetError : public virtual BipErrorItf, public BipError, public NonOneSafePetriNetErrorItf {
 public:
  // constructors
  NonOneSafePetriNetError(Atom &atom);

  // destructor
  virtual ~NonOneSafePetriNetError();
};

#endif // _BIP_Engine_NonOneSafePetriNetError_HPP_
