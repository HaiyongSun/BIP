#ifndef _BIP_Engine_Logger_HPP_
#define _BIP_Engine_Logger_HPP_

#include <bip-engineiface-config.hpp>

using namespace bipbasetypes;
using namespace biptypes;

#include <string>
#include <iostream>
#include <sstream>

#include "BipError.hpp"
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include "Connector.hpp"
#include "InteractionValue.hpp"
#include "Atom.hpp"
#include "AtomInternalPort.hpp"
#include "ReferenceEngine.hpp"

/** \brief Represent a node in a tree of strings
 */
class Logger {
 public:
  // constructor and destructor
  Logger(ostream &outoutStream, bool verbose, unsigned int limit);
  virtual ~Logger();
    
  // operations
  void log(const string &s);
  void log(const BipError &error);
  void log(const InteractionValue &interaction, const vector<InteractionValue *> &interactions);
  void log(const AtomInternalPort &port, const vector<AtomInternalPort *> &internals);
  void logDeadlock() { if (verbose()) { begin(); outputStream() << "state #" << mState << ": deadlock!"; end(); } }
      
 protected:
  // operations
  void begin() { while(mIsDisplaying.exchange(true)); outputStream() << "[BIP ENGINE]: "; }
  void newLine() { outputStream() << endl << "[BIP ENGINE]: "; }
  void end() { outputStream() << endl; mIsDisplaying.store(false); }
 
  // getters
  bool verbose() const { return mVerbose; }
  ostream &outputStream() { return mOutputStream; }
 
  ostream &mOutputStream;
  bool mVerbose;
  unsigned int mLimit;
public:
  atomic<unsigned int> mState;
  atomic<bool> mIsDisplaying;
 };
 
inline
void Logger::log(const string &s) {
  if (verbose()) {
    begin();
    outputStream() << s;    
    end();
  }
}
 
inline
void Logger::log(const BipError &error) {
  if (error.type() != NO_ERROR) {
    begin();
    
    outputStream() << "ERROR: ";

    if (error.type() == NON_DETERMINISTIC_PETRI_NET) {
      const NonDeterministicPetriNetError &errorNonDetPetriNet = dynamic_cast<const NonDeterministicPetriNetError &>(error);

      if (errorNonDetPetriNet.hasPort()) {
        outputStream() << "non-deterministic choice between transitions labelled by " << errorNonDetPetriNet.port().name();
      }
      else {
        outputStream() << "non-deterministic choice between internal transitions";
      }

      outputStream() << " in " << errorNonDetPetriNet.atom().name() << "!";
    }
    else if (error.type() == CYCLE_IN_PRIORITIES) {
      outputStream() << "cycle in priorities! (";

      const CycleInPrioritiesError &errorPriorities = dynamic_cast<const CycleInPrioritiesError &>(error);

      for (vector<const Interaction *>::const_iterator interactionIt = errorPriorities.cycle().begin() ;
           interactionIt != errorPriorities.cycle().end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        if (interactionIt != errorPriorities.cycle().begin()) {
          outputStream() << " < ";
        }

        outputStream() << interaction;
      }

      outputStream() << ")";
    }
    else if (error.type() == CYCLE_IN_ATOM_PRIORITIES) {
      outputStream() << "cycle in priorities! (";

      const CycleInAtomPrioritiesError &errorPriorities = dynamic_cast<const CycleInAtomPrioritiesError &>(error);

      for (vector<const AtomInternalPort *>::const_iterator portIt = errorPriorities.cycle().begin() ;
           portIt != errorPriorities.cycle().end() ;
           ++portIt) {
        const AtomInternalPort &port = **portIt;

        if (portIt != errorPriorities.cycle().begin()) {
          outputStream() << " < ";
        }

        outputStream() << port.name();
      }

      outputStream() << ")";
    }
    else if (error.type() == NON_ONE_SAFE_PETRI_NET) {
      const NonOneSafePetriNetError &errorNonOneSafe = dynamic_cast<const NonOneSafePetriNetError &>(error);

      outputStream() << "the Peri net of " << errorNonOneSafe.atom().name() << " is not 1-safe! (";
      if (errorNonOneSafe.hasPort()) {        
        outputStream() << "when executing a transition labelled by " << errorNonOneSafe.port().name();
      }
      else {
        outputStream() << "when executing an internal transition";
      }
      outputStream() << ")";
    }
    else {
      // unsupported type of error
      assert(false);
    }
    
    end();

    ErrorType returnedErrorType = error.type();

    delete &error;

    exit(returnedErrorType);
  }
}

inline
void Logger::log(const InteractionValue &interaction, const vector<InteractionValue *> &interactions) {
  if (verbose()) {
    begin();    
    outputStream() << "state #" << mState << ": ";
    
    outputStream() << interactions.size() << " interaction";
    if (interactions.size() > 1) outputStream() << "s";
    outputStream() << ":";
        
    unsigned int index = 0;

    for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
      const InteractionValue &possibleInteraction = *(interactions[i]);
      
      if (&interaction == &possibleInteraction) {
        index = i;
      }

      newLine();
      outputStream() << "  [" << i << "] " << possibleInteraction.connector().fullName() << ": " << possibleInteraction;
    }
    
    
    newLine();
    outputStream() << "-> choose [" << index << "] " << interaction.connector().fullName() << ": " << interaction;
    end();
  }

  unsigned int newState = ++mState;

  if (mLimit != 0) {
    if (newState == mLimit) {
      ReferenceEngine::jobs.stop();

      if (verbose()) {
        begin();
        outputStream() << "state #" << mState << ": stop (reached limit of " << mLimit << " interactions)";
        end();
      }
    }
  }
}

inline
void Logger::log(const AtomInternalPort &port, const vector<AtomInternalPort *> &internals) {
  if (verbose()) {
    begin();
    outputStream() << "state #" << mState << ": ";

    outputStream() << internals.size() << " internal port";
    if (internals.size() > 1) outputStream() << "s";
    outputStream() << ":";
        
    unsigned int index = 0;

    for (unsigned int i = 0 ; i < internals.size() ; ++i) {
      const AtomInternalPort &possibleInternal = *(internals[i]);
      
      if (&port == &possibleInternal) {
        index = i;
      }

      newLine();
      outputStream() << "  [" << i << "] " << possibleInternal.holder().fullName() << "." << possibleInternal.name();
    }
    
    
    newLine(); 
    outputStream() << "-> choose [" << index << "] " << port.holder().fullName() << "." << port.name()  ;

    end();
  }

  unsigned int newState = ++mState;

  if (mLimit != 0) {
    if (newState == mLimit) {
      ReferenceEngine::jobs.stop();

      if (verbose()) {
        begin();
        outputStream() << "state #" << mState << ": stop (reached limit of " << mLimit << " interactions)";
        end();
      }
    }
  }
}


#endif // _BIP_Engine_Logger_HPP_
