#ifndef _BIP_Engine_Priority_HPP_
#define _BIP_Engine_Priority_HPP_

// inherited classes
#include <PriorityItf.hpp>
#include <Resetable.hpp>
#include <Initializable.hpp>

class BipError;
class CycleInPriorities;

class Priority : public PriorityItf {
 public:
  // constructors
  Priority(Interaction *low, Interaction *high);

  // destructor
  virtual ~Priority();

  // specific
  bool appliesLow(const Interaction &interaction) const;
  bool appliesHigh(const Interaction &interaction) const;
  Initializable<vector<Priority *>, Priority> &dominatingPriorities() const { return mDominatingPriorities; }
  Initializable<vector<Priority *>, Priority> &dominatedPriorities() const { return mDominatedPriorities; }

  BipError &detectCycle() const;

  bool changed() const { return guard() != mPreviousGuard; }
  void updatePreviousGuard() const { mPreviousGuard = guard(); }

  Resetable<bool, Priority> &active() const { return mActive; }

  void initialize();

  const vector<const CycleInPriorities *> &cycles() const { return mCycles; }
  vector<const CycleInPriorities *> &cycles() { return mCycles; }

 protected:
  void computeDominatingPriorities(vector<Priority *> &priorities);
  void computeDominatedPriorities(vector<Priority *> &priorities);
  void recomputeActive(bool &active) const;

  mutable Initializable<vector<Priority *>, Priority> mDominatingPriorities;
  mutable Initializable<vector<Priority *>, Priority> mDominatedPriorities;

  mutable bool mPreviousGuard;
  mutable Resetable<bool, Priority> mActive;

  vector<const CycleInPriorities *> mCycles;
};

#endif // _BIP_Engine_Priority_HPP_
