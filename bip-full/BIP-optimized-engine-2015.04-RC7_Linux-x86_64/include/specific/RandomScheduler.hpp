#ifndef _BIP_Engine_RandomScheduler_HPP_
#define _BIP_Engine_RandomScheduler_HPP_

#include "Scheduler.hpp"
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

/** \brief Compute execution sequences in which interactions
 * are chosen randomly.
 */
class RandomScheduler : public Scheduler {
 public:
  RandomScheduler(Engine &engine, bool verbose = true, bool debug = false, bool interactive = false, bool randomSeed = true, unsigned int seed = 0, unsigned int limit = 0);
  virtual ~RandomScheduler();

  virtual void run();

  bool verbose() const { return mVerbose; }
  bool debug() const { return mDebug; }
  bool interactive() const { return mInteractive; }
  bool randomSeed() const { return mRandomSeed; }
  unsigned int seed() const { return mSeed; }
  unsigned int limit() const { return mLimit; }


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

  bool mVerbose;
  bool mDebug;
  bool mInteractive;
  bool mRandomSeed;
  unsigned int mSeed;
  unsigned int mLimit;
};

#endif // _BIP_Engine_RandomScheduler_HPP_
