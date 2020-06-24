#ifndef _BIP_Engine_Explorer_HPP_
#define _BIP_Engine_Explorer_HPP_

#include "Scheduler.hpp"
#include "Compound.hpp"
#include "Engine.hpp"
#include <State.hpp>
#include <unordered_set>

class BipError;

/** \brief Compute all execution sequences of a model.
 */
class Explorer : public Scheduler {
 public:
  Explorer(Engine &engine, bool verbose = true);
  virtual ~Explorer();

  virtual void run();

  bool verbose() const { return mVerbose; }


 protected:
  unsigned int dfsExplore();

  void handleError(BipError &error);

  unordered_set<State, State::Hash> &states() { return mStates; }
  vector<State> &deadlocks() { return mDeadlocks; }
  vector<State> &errors() { return mErrors; }

  unordered_set<State, State::Hash> mStates;
  //set<State> states;
  //vector<State> states;
  vector<State> mDeadlocks;
  vector<State> mErrors;

  bool mVerbose;
};

#endif // _BIP_Engine_Explorer_HPP_
