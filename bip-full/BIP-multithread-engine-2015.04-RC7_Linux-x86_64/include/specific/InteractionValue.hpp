#ifndef _BIP_Engine_InteractionValue_HPP_
#define _BIP_Engine_InteractionValue_HPP_

// inherited classes
#include <InteractionValueItf.hpp>
#include "Interaction.hpp"

class BipError;
class Connector;
class AtomExportPort;

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
  bool isDominatedByPriorities() const { return interaction().isDominatedByPriorities(); }

  bool operator<=(const InteractionValue &interaction) const;
  bool operator==(const InteractionValue &interaction) const;
  bool operator!=(const InteractionValue &interaction) const { return ! (*this == interaction); }
  bool operator< (const InteractionValue &interaction) const { bool eq; bool ret = includedIn(interaction, eq); return ret && !eq; }
  bool operator> (const InteractionValue &interaction) const { return interaction < *this; }

  friend ostream& operator<<(ostream &, const InteractionValue&);
  friend ostream& operator<<(ostream &, const InteractionValue*);

 protected:
  bool includedIn(const InteractionValue &interaction, bool &eq) const;
};

#endif // _BIP_Engine_InteractionValue_HPP_
