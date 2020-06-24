#ifndef _BIP_Engine_Scheduler_HPP_
#define _BIP_Engine_Scheduler_HPP_

#include "Compound.hpp"
#include "Engine.hpp"

/** \brief Compute a sequence of interactions.
 *
 * A scheduler implements a specific scheduling policy, e.g.
 * random, interactive, exhaustive, etc.
 */
class Scheduler {
 public:
  Scheduler(Engine &engine);
  virtual ~Scheduler();

  /** \brief Implements the behavior of the scheduler.
   */
  virtual void run() = 0;

  /** \return Engine which is used by the scheduler.
   */
  const Engine& engine() const { return mEngine; }

 protected:

  /** \return Engine which is used by the scheduler.
   */
  Engine& engine() { return mEngine; }

  /** \brief Engine which is used by the scheduler for computing
   * interactions at a given state.
   */
  Engine &mEngine;
};

#endif // _BIP_Engine_Scheduler_HPP_
