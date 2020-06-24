#ifndef _BIP_Engine_Engine_HPP_
#define _BIP_Engine_Engine_HPP_

#include <Compound.hpp>
#include <State.hpp>

#include <bip-engineiface-config.hpp>

class InteractionValue;
class AtomInternalPort;
class BipError;

/** \brief Provides the basic interface for executing a model.
 *
 * It can initialize the system, execute an interaction or an internal port,
 * and compute the set of interactions and internal ports enabled at the
 * current state of the system.
 */
class Engine {
 public:
  Engine(Compound &top);
  virtual ~Engine();

  inline const Compound& top() const { return mTop; }

  /** 
   * \brief Initialize the engine.
   *
   * This step should include the initialization of the components
   * which includes calls to initialize() methods of atoms and
   * update of the port values of all ports of the system.
   */
  virtual BipError &initialize() = 0;

  /** 
   * \brief Execute an interaction.
   *
   * The chosen interaction should be enabled at the current state of mTop,
   * i.e. should be in the set returned by interactions().
   *
   * \param interaction The chosen interaction.
   */
  virtual BipError &execute(InteractionValue& interaction) = 0;

  /** 
   * \brief Execute a internal port.
   *
   * This internal port should be enabled at the current state of mTop,
   * i.e. should be in the set returned by internals().
   *
   * \param internal The chosen atom internal port.
   */
  virtual BipError &execute(AtomInternalPort& internal) = 0;

  /** 
   * \brief Returns the set of interactions enabled at current state.
   */
  virtual const vector<InteractionValue *> &interactions() const = 0;

  /** 
   * \brief Returns the set of internal ports enabled at current state.
   */
  virtual const vector<AtomInternalPort *> &internals() const = 0;

  /** 
   * \brief Returns the current state of the model.
   */
  virtual State getState() const = 0;

  /** 
   * \brief Set the current state of the model.
   */
  virtual void setState(const State &state) = 0;


 protected:
  inline Compound& top() { return mTop; }

  Compound &mTop;
};

#endif // _BIP_Engine_Engine_HPP_
