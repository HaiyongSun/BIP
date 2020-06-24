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

  // specific opertations
  void release();
  virtual bool isEnabled() const;
  bool isDominatedByPriorities() const;
  bool isDominatedLocally() const;
  vector<Priority *> dominatingPriorities() const;
  vector<Interaction *> dominators() const;
  BipError &detectCycleInPriorities() const;

  unsigned int index(const Port &port) const;
  bool contains(const Port &port) const { return index(port) != ports().size(); }

  bool isDominatedLocallyBy(const Interaction &interaction) const;

  friend ostream& operator<<(ostream &, const Interaction&);
  friend ostream& operator<<(ostream &, const Interaction*);

 protected:
  BipError &detectCycleInPriorities(const vector<const Interaction *> &path) const;
};

#endif // _BIP_Engine_Interaction_HPP_
