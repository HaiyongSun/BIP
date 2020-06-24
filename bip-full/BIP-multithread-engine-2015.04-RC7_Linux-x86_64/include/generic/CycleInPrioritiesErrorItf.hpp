#ifndef _BIP_Engine_CycleInPrioritiesErrorItf_HPP_
#define _BIP_Engine_CycleInPrioritiesErrorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "BipErrorItf.hpp"

// used classes
#include "BipError.hpp"

// referenced classes
class Interaction;


class CycleInPrioritiesErrorItf : public virtual BipErrorItf {
 public:
  // destructor
  virtual ~CycleInPrioritiesErrorItf();

  // getters for references
  vector<const Interaction *> &cycle() { return mCycle; }
  const vector<const Interaction *> &cycle() const { return mCycle; }
  bool hasCycle() const { return !mCycle.empty(); }

  // setters for references
  void addCycle(const Interaction &cycle) { mCycle.push_back(&cycle); }
  void clearCycle() { mCycle.clear(); }

 protected:
  // protected constructors
  CycleInPrioritiesErrorItf();

  // references
  vector<const Interaction *> mCycle;
};

#endif // _BIP_Engine_CycleInPrioritiesErrorItf_HPP_
