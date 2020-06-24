#ifndef _BIP_Engine_NonOneSafePetriNetErrorItf_HPP_
#define _BIP_Engine_NonOneSafePetriNetErrorItf_HPP_

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


class NonOneSafePetriNetErrorItf : public virtual BipErrorItf {
 public:
  // destructor
  virtual ~NonOneSafePetriNetErrorItf();

  // getters for references
  AtomInternalPort &port() const { return *mPort; }
  bool hasPort() const { return mPort != NULL; }
  Atom &atom() const { return mAtom; }

  // setters for references
  void setPort(AtomInternalPort &port) { mPort = &port; }
  void clearPort() { mPort = NULL; }

 protected:
  // protected constructors
  NonOneSafePetriNetErrorItf(Atom &atom);

  // references
  AtomInternalPort *mPort;
  Atom &mAtom;
};

#endif // _BIP_Engine_NonOneSafePetriNetErrorItf_HPP_
