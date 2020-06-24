#ifndef _BIP_Engine_PriorityItf_HPP_
#define _BIP_Engine_PriorityItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// used classes
#include "Data.hpp"

// referenced classes
class Compound;
class Interaction;

class Component;

class PriorityItf {
 public:
  // destructor
  virtual ~PriorityItf();

  // operations
  virtual bool guard() const = 0;

  // getters for references
  Interaction &low() const { return *mLow; }
  bool hasLow() const { return mLow != NULL; }
  Interaction &high() const { return *mHigh; }
  bool hasHigh() const { return mHigh != NULL; }
  const vector<Data *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  PriorityItf(Interaction *low, Interaction *high);

  // protected getters for references
  vector<Data *> &data() { return mData; }

  // protected setters for references
  void addData(Data &data) { mData.push_back(&data); }

  // references
  Interaction *const mLow;
  Interaction *const mHigh;
  vector<Data *> mData;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_PriorityItf_HPP_
