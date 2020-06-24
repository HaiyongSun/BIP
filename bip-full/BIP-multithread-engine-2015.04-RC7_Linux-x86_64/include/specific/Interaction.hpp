#ifndef _BIP_Engine_Interaction_HPP_
#define _BIP_Engine_Interaction_HPP_

// inherited classes
#include <InteractionItf.hpp>

class Priority;
class BipError;

class Interaction : public InteractionItf {
 public:
  // constructors
  Interaction(const Connector &connector);

  // destructor
  virtual ~Interaction();

  // operations
  virtual void recycle() {}

  // specific operations
  bool isEnabled() const;
  bool isMaximal() const;
  bool isLocallyMaximalOrDominated() const;
  bool isDominatedByPriorities() const;
  bool isDominatedLocally() const;

  unsigned int index(const Port &port) const;
  bool contains(const Port &port) const { return index(port) != ports().size(); }

  friend ostream& operator<<(ostream &, const Interaction&);
  friend ostream& operator<<(ostream &, const Interaction*);
};

#endif // _BIP_Engine_Interaction_HPP_
