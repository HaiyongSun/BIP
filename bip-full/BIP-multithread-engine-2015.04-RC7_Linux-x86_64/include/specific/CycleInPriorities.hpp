#ifndef _BIP_Engine_CycleInPriorities_HPP_
#define _BIP_Engine_CycleInPriorities_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include <Resetable.hpp>

class Priority;
class AtomExportData;
class Connector;
class Interaction;

class CycleInPriorities {
 public:
  // constructors
  CycleInPriorities(const vector<Priority *> &priorities);
  CycleInPriorities(const CycleInPriorities &cycle);

  // destructor
  virtual ~CycleInPriorities();

  void initialize() const;
  bool allGuardsTrue() const { return (bool) mAllGuardsTrue; }
  Resetable<bool, CycleInPriorities> &reset() const { return mAllGuardsTrue; }

  vector<const Interaction *> interactions() const;

  bool operator<(const CycleInPriorities &cycle) const { return mPriorities < cycle.mPriorities; }

  const vector<Priority *> &priorities() const { return mOrderedPriorities; }
  
 protected:
  Interaction &getLowInteraction(const Priority &priority, const Priority &lowerPriority) const;
  Interaction &getHighInteraction(const Priority &priority, const Priority &higherPriority) const;
  Interaction &getMatchingWildcard(const Connector &connector1, const Connector &connector2) const;
  Interaction &getMaximalInteraction(const Connector &connector) const; 
  set<AtomExportData *> allAtomData() const;
  void recomputeAllGuardsTrue(bool &b) const;

  vector<Priority *> mOrderedPriorities;
  set<Priority *> mPriorities;
  mutable Resetable<bool, CycleInPriorities> mAllGuardsTrue;
};

#endif // _BIP_Engine_CycleInPriorities_HPP_
