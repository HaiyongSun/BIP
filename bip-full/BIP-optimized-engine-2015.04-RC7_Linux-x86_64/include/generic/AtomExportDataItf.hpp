#ifndef _BIP_Engine_AtomExportDataItf_HPP_
#define _BIP_Engine_AtomExportDataItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "DataItf.hpp"

// used classes
#include "Data.hpp"

// referenced classes
class Atom;

class Component;

class AtomExportDataItf : public virtual DataItf {
 public:
  // destructor
  virtual ~AtomExportDataItf();

  // operations
  virtual bool isReset() const = 0;

  // opposites accessors
  Atom &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Atom &atom) { mHolder = &atom; }

 protected:
  // protected constructors
  AtomExportDataItf(const string &name);

  // opposites
  Atom *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_AtomExportDataItf_HPP_
