#ifndef _BIP_Engine_Port_HPP_
#define _BIP_Engine_Port_HPP_

// inherited classes
#include <PortItf.hpp>

class PortValue;
class BipError;

class Port : public virtual PortItf {
 public:
  // constructors
  Port(const string &name, const ExportType &type);

  // destructor
  virtual ~Port();
};

#endif // _BIP_Engine_Port_HPP_
