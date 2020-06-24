#ifndef _BIP_Engine_CompoundExportDataItf_HPP_
#define _BIP_Engine_CompoundExportDataItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "DataItf.hpp"

// used classes
#include "Data.hpp"

// referenced classes
class Compound;


class CompoundExportDataItf : public virtual DataItf {
 public:
  // destructor
  virtual ~CompoundExportDataItf();

  // getters for references
  Data &forwardData() const { return mForwardData; }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  CompoundExportDataItf(Data &forwardData, const string &name);

  // references
  Data &mForwardData;

  // opposites
  Compound *mHolder;
};

#endif // _BIP_Engine_CompoundExportDataItf_HPP_
