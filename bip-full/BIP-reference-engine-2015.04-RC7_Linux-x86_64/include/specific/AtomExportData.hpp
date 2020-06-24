#ifndef _BIP_Engine_AtomExportData_HPP_
#define _BIP_Engine_AtomExportData_HPP_

// inherited classes
#include <AtomExportDataItf.hpp>
#include "Data.hpp"

class AtomExportData : public virtual DataItf, public virtual Data, public AtomExportDataItf {
 public:
  // constructors
  AtomExportData(const string &name);

  // destructor
  virtual ~AtomExportData();
};

#endif // _BIP_Engine_AtomExportData_HPP_
