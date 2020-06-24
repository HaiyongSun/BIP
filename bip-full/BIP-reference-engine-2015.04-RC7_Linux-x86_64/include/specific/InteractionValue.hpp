#ifndef _BIP_Engine_InteractionValue_HPP_
#define _BIP_Engine_InteractionValue_HPP_

// inherited classes
#include <InteractionValueItf.hpp>
#include "Interaction.hpp"

class BipError;

class InteractionValue : public InteractionValueItf {
 public:
  // constructors
  InteractionValue();

  // destructor
  virtual ~InteractionValue();

  // specific
  const Connector &connector() const { return interaction().connector(); }
  const vector<Port *> &ports() const { return interaction().ports(); }
  BipError &execute();

  bool isAllDefined() const;
  bool isEnabled() const;
  bool isDominated() const;
  bool isDominatedLocally() const;
  bool isDominatedLocallyBy(const InteractionValue &interaction) const;
  bool isDominatedByPriorities() const { return interaction().isDominatedByPriorities(); }

  bool operator==(const InteractionValue &interaction) const { return *this <= interaction && interaction <= *this; }
  bool operator!=(const InteractionValue &interaction) const { return ! (*this == interaction); }

 protected:
  bool operator<=(const InteractionValue &interaction) const;
  bool operator< (const InteractionValue &interaction) const { return *this <= interaction && *this != interaction; }

  friend ostream& operator<<(ostream &, const InteractionValue&);
  friend ostream& operator<<(ostream &, const InteractionValue*);
};

#endif // _BIP_Engine_InteractionValue_HPP_
