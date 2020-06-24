#ifndef _BIP_Engine_Component_HPP_
#define _BIP_Engine_Component_HPP_

// inherited classes
#include <ComponentItf.hpp>

class InteractionValue;
class AtomInternalPort;
class BipError;

class Component : public virtual ComponentItf {
 public:
  // constructors
  Component(const string &name, const ComponentType &type);

  // destructor
  virtual ~Component();

  // specific operations
  BipError &updateUpperLevels();
  string fullName() const;
};

#endif // _BIP_Engine_Component_HPP_
