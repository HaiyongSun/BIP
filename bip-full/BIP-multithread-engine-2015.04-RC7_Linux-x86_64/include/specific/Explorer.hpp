#ifndef _BIP_Engine_Explorer_HPP_
#define _BIP_Engine_Explorer_HPP_

#include "Compound.hpp"
#include "Engine.hpp"
#include <State.hpp>
#include <unordered_set>

class BipError;

/** \brief Compute all execution sequences of a model.
 */
class Explorer {
 public:
  Explorer(Engine &engine, bool verbose = true);
  virtual ~Explorer();

  void run();
  bool verbose() const { return mVerbose; }


  /** \return Engine which is used by the scheduler.
   */
  const Engine& engine() const { return mEngine; }

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

  /** \return Engine which is used by the scheduler.
   */
  Engine& engine() { return mEngine; }

  /** \brief Engine which is used by the scheduler for computing
   * interactions at a given state.
   */
  Engine &mEngine;

  bool mVerbose;
};

#endif // _BIP_Engine_Explorer_HPP_
