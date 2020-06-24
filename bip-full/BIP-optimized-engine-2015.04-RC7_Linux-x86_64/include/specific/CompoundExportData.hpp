#ifndef _BIP_Engine_CompoundExportData_HPP_
#define _BIP_Engine_CompoundExportData_HPP_

// inherited classes
#include <CompoundExportDataItf.hpp>
#include "Data.hpp"

class CompoundExportData : public virtual DataItf, public virtual Data, public CompoundExportDataItf {
 public:
  // constructors
  CompoundExportData(Data &forwardData, const string &name);

  // destructor
  virtual ~CompoundExportData();
};

#endif // _BIP_Engine_CompoundExportData_HPP_
