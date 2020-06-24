#ifndef _BIP_Engine_CycleInAtomPrioritiesErrorItf_HPP_
#define _BIP_Engine_CycleInAtomPrioritiesErrorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "BipErrorItf.hpp"

// used classes
#include "BipError.hpp"

// referenced classes
class AtomInternalPort;


class CycleInAtomPrioritiesErrorItf : public virtual BipErrorItf {
 public:
  // destructor
  virtual ~CycleInAtomPrioritiesErrorItf();

  // getters for references
  vector<const AtomInternalPort *> &cycle() { return mCycle; }
  const vector<const AtomInternalPort *> &cycle() const { return mCycle; }
  bool hasCycle() const { return !mCycle.empty(); }

  // setters for references
  void addCycle(const AtomInternalPort &cycle) { mCycle.push_back(&cycle); }
  void clearCycle() { mCycle.clear(); }

 protected:
  // protected constructors
  CycleInAtomPrioritiesErrorItf();

  // references
  vector<const AtomInternalPort *> mCycle;
};

#endif // _BIP_Engine_CycleInAtomPrioritiesErrorItf_HPP_
