#ifndef _BIP_Engine_ReferenceEngine_HPP_
#define _BIP_Engine_ReferenceEngine_HPP_

#include "Engine.hpp"
#include "Compound.hpp"

#include <bip-engineiface-config.hpp>

class InteractionValue;
class AtomInternalPort;
class BipError;

/** \brief Direct implementation of the BIP semantics, without any
 * optimization.
 *
 * It can be used as a reference for testing other engines, or as a
 * starting point for understanding the BIP semantics.
 */
class ReferenceEngine : public Engine {
 public:
  ReferenceEngine(Compound &top);
  ReferenceEngine(Compound &top, bool disableMaximalProgress);
  virtual ~ReferenceEngine();

  virtual BipError& initialize();
  virtual BipError& execute(InteractionValue &interaction);
  virtual BipError& execute(AtomInternalPort &internal);
  virtual const vector<InteractionValue *> &interactions() const { return mInteractions; }
  virtual const vector<AtomInternalPort *> &internals() const { return mInternals; }

  virtual State getState() const;
  virtual void setState(const State &state);

  bool disableMaximalProgress() const { return mDisableMaximalProgress; }


 protected:
  /**
   * \brief Update interactions and internals w.r.t. to the current 
   * state of the system.
   */
  void update();

  /**
   * \brief Compute the set of interactions enabled at the current state.
   */
  void computeInteractions();

  /**
   * \brief Compute the set of internal pots enabled at the current state.
   */
  void computeInternals();

  /**
   * \brief Returns the set of interactions enabled at the current state.
   */
  vector<InteractionValue *> &interactions() { return mInteractions; }

  /**
   * \brief Returns the set of internal ports enabled at the current state.
   */
  vector<AtomInternalPort *> &internals() { return mInternals; }

  /**
   * \brief Set of interactions enabled at the current state.
   */
  vector<InteractionValue *> mInteractions;

  /**
   * \brief Set of internal ports enabled at the current state.
   */
  vector<AtomInternalPort *> mInternals;

  bool mDisableMaximalProgress;
};

#endif // _BIP_Engine_ReferenceEngine_HPP_
