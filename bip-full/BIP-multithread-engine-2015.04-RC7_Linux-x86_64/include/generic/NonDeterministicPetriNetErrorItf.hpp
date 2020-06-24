#ifndef _BIP_Engine_NonDeterministicPetriNetErrorItf_HPP_
#define _BIP_Engine_NonDeterministicPetriNetErrorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "BipErrorItf.hpp"

// used classes
#include "BipError.hpp"

// referenced classes
class Atom;
class AtomInternalPort;


class NonDeterministicPetriNetErrorItf : public virtual BipErrorItf {
 public:
  // destructor
  virtual ~NonDeterministicPetriNetErrorItf();

  // getters for references
  Atom &atom() const { return mAtom; }
  AtomInternalPort &port() const { return *mPort; }
  bool hasPort() const { return mPort != NULL; }

  // setters for references
  void setPort(AtomInternalPort &port) { mPort = &port; }
  void clearPort() { mPort = NULL; }

 protected:
  // protected constructors
  NonDeterministicPetriNetErrorItf(Atom &atom);

  // references
  Atom &mAtom;
  AtomInternalPort *mPort;
};

#endif // _BIP_Engine_NonDeterministicPetriNetErrorItf_HPP_
