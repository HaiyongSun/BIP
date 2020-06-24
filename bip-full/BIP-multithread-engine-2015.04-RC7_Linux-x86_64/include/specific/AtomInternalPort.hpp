#ifndef _BIP_Engine_AtomInternalPort_HPP_
#define _BIP_Engine_AtomInternalPort_HPP_

// inherited classes
#include <AtomInternalPortItf.hpp>

class AtomExportPort;

class AtomInternalPort : public AtomInternalPortItf {
 public:
  // constructors
  AtomInternalPort(const string &name);

  // destructor
  virtual ~AtomInternalPort();

  // specific
  bool isExported() const { if (!mInitializedIsExported) recomputeIsExported(); return mIsExported; }

  void addConnectedPort(AtomExportPort &port) { mConnectedPorts.push_back(&port); }

 protected:
  void recomputeIsExported() const;

  const vector<AtomExportPort *> &connectedPorts() const { return mConnectedPorts; }

  vector<AtomExportPort *> mConnectedPorts;

  mutable bool mIsExported;
  mutable bool mInitializedIsExported;
};

#endif // _BIP_Engine_AtomInternalPort_HPP_
