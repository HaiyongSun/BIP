#ifndef _BIP_Engine_Priority_HPP_
#define _BIP_Engine_Priority_HPP_

// inherited classes
#include <PriorityItf.hpp>

class BipError;

class Priority : public PriorityItf {
 public:
  // constructors
  Priority(Interaction *low, Interaction *high);

  // destructor
  virtual ~Priority();

  // specific
  bool appliesLow(const Interaction &interaction) const;
  bool appliesHigh(const Interaction &interaction) const;
  vector<Interaction *> lowInteractions() const;
  vector<Interaction *> highInteractions() const;

  BipError &detectCycle() const;
};

#endif // _BIP_Engine_Priority_HPP_
