#ifndef _BIP_Engine_Data_HPP_
#define _BIP_Engine_Data_HPP_

// inherited classes
#include <DataItf.hpp>

class Data : public virtual DataItf {
 public:
  // constructors
  Data(const string &name, const ExportType &type);

  // destructor
  virtual ~Data();
};

#endif // _BIP_Engine_Data_HPP_
