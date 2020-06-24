#ifndef _BIP_Engine_Explorer_HPP_
#define _BIP_Engine_Explorer_HPP_

#include "Scheduler.hpp"
#include "Compound.hpp"
#include "Engine.hpp"
#include <State.hpp>

class BipError;

/** \brief Compute all execution sequences of a model.
 */
class Explorer : public Scheduler {
 public:
  Explorer(Engine &engine, bool verbose = true, unsigned int limit = 0);
  virtual ~Explorer();

  virtual void run();

  bool verbose() const { return mVerbose; }
  unsigned int limit() const { return mLimit; }


 protected:
  unsigned int dfsExplore(vector<State> &states, vector<State> & deadlocks, vector<State> &erros, unsigned int size);

  void handleError(BipError &error);

  bool equals(char *state1, char *state2, size_t size);

  bool mVerbose;
  unsigned int mLimit;
};

#endif // _BIP_Engine_Explorer_HPP_
