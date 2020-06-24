#ifndef _BIP_Engine_Connector_HPP_
#define _BIP_Engine_Connector_HPP_

// inherited classes
#include <ConnectorItf.hpp>
#include "ConnectorExportPort.hpp"
#include "QuotedPortReference.hpp"

#include "Resetable.hpp"
#include "Initializable.hpp"

class Connector : public ConnectorItf {
 public:
  // constructors
  Connector(const string &name);

  // destructor
  virtual ~Connector();

  // specific
  bool isTopLevel() const { return mIsTopLevel.value(); }
  const vector<Connector *> &subConnectors() const { return mSubConnectors.value(); }
  const vector<Connector *> &allSubConnectors() const { return mAllSubConnectors.value(); }
  
  Resetable<vector<InteractionValue *>, Connector> &enabledInteractions() const { return mEnabledInteractions; }
  Resetable<vector<InteractionValue *>, Connector> &maximalInteractions() const { return mMaximalInteractions; }
  Resetable<vector<InteractionValue *>, Connector> &locallyMaximalInteractions() const  { return mLocallyMaximalInteractions; }

  void release() const;
  void release(const vector<Interaction *> &interactions) const;
  void release(const vector<InteractionValue *> &interactions) const;

  Initializable<vector<Priority *>, Connector> &dominatingPriorities() const { return mDominatingPriorities; }
  Initializable<vector<Priority *>, Connector> &dominatedPriorities() const { return mDominatedPriorities; }
  
  string fullName() const;

  void initialize();

 protected:
  // update methods resetable objects
  void recomputeAllEnabledPorts(Interaction *&allEnabledPorts) const;
  void recomputeEnabledInteractions(vector<InteractionValue *> &enabledInteractions) const;
  void recomputeMaximalInteractions(vector<InteractionValue *> &maximalInteractions) const;
  void recomputeLocallyMaximalInteractions(vector<InteractionValue *> &locallyMaximalInteractions) const;

  // initialization methods for initializable objects
  void computeDominatingPriorities(vector<Priority *> &dominatingPriorities);
  void computeDominatedPriorities(vector<Priority *> &dominatedPriorities);
  void computeIsTopLevel(bool &isTopLevel);
  void computeSubConnectors(vector<Connector *> &subConnectors);
  void computeAllSubConnectors(vector<Connector *> &allSubConnectors);

  // protected setters for references
  void addPort(QuotedPortReference &quotedPort);
  void setExportedPort(ConnectorExportPort &exportedPort);

  // specific
  void enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> &partialValues, unsigned int nextPortIndex, bool keepLocallyMaximalOnly) const;
  void enumerateLocallyMaximalInteractionValues(vector<InteractionValue *> &allInteractions, Interaction &interaction, unsigned int mandatoryIndex) const;
  Interaction &allEnabledPorts() const { return *(Interaction *) mAllEnabledPorts; }

  void computeIsTopLevel() const;

  mutable Resetable<Interaction *, Connector> mAllEnabledPorts;

  mutable Resetable<vector<InteractionValue *>, Connector> mEnabledInteractions;
  mutable Resetable<vector<InteractionValue *>, Connector> mMaximalInteractions;
  mutable Resetable<vector<InteractionValue *>, Connector> mLocallyMaximalInteractions;

  mutable Initializable<vector<Priority *>, Connector> mDominatingPriorities;
  mutable Initializable<vector<Priority *>, Connector> mDominatedPriorities;
  mutable Initializable<bool, Connector> mIsTopLevel;
  mutable Initializable<vector<Connector *>, Connector> mSubConnectors;
  mutable Initializable<vector<Connector *>, Connector> mAllSubConnectors;
};

#endif // _BIP_Engine_Connector_HPP_
