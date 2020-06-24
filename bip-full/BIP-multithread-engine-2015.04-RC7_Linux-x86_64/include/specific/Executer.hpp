#ifndef _BIP_Engine_Executer_HPP_
#define _BIP_Engine_Executer_HPP_

#include "Compound.hpp"
#include "Engine.hpp"
#include "StringTree.hpp"

class BipError;
class Atom;
class Component;
class Connector;
class Compound;
class Port;
class ConnectorPort;
class ComponentPort;
class AtomInternalPort;
class AtomExportPort;
class Logger;

/** \brief Compute execution sequences in which interactions
 * are chosen randomly.
 */
class Executer {
 public:
  Executer(Engine &engine, Logger &logger, bool randomSeed = true, unsigned int seed = 0);
  virtual ~Executer();

  void run();
  bool debug() const { return mDebug; }
  bool interactive() const { return mInteractive; }
  bool randomSeed() const { return mRandomSeed; }
  unsigned int seed() const { return mSeed; }
  unsigned int limit() const { return mLimit; }

  /** \return Engine which is used by the scheduler.
   */
  const Engine& engine() const { return mEngine; }

 protected:
  void handleError(BipError &error);
  void print();
  StringTree print(const ConnectorExportPort &port);
  StringTree print(const CompoundExportPort &port);
  StringTree print(const AtomInternalPort &port);
  StringTree print(const AtomExportPort &port);
  StringTree print(const InteractionValue &port);
  StringTree print(const Connector &connector);
  StringTree print(const Atom &atom);
  StringTree print(const Compound &compound);
  StringTree print(const Component &component);

  Logger &logger() { return mLogger; }

  /** \return Engine which is used by the scheduler.
   */
  Engine& engine() { return mEngine; }

  /** \brief Engine which is used by the scheduler for computing
   * interactions at a given state.
   */
  Engine &mEngine;

  Logger &mLogger;
  bool mDebug;
  bool mInteractive;
  bool mRandomSeed;
  unsigned int mSeed;
  unsigned int mLimit;
};

#endif // _BIP_Engine_Executer_HPP_
