#ifndef _BIP_Engine_Port_HPP_
#define _BIP_Engine_Port_HPP_

// inherited classes
#include <PortItf.hpp>
//#include <Resetable.hpp>

class Atom;
class PortValue;
class BipError;
class Connector;
class CompoundExportPort;
class ResetableItf;

class Port : public virtual PortItf {
 public:
  // constructors
  Port(const string &name, const ExportType &type);

  // destructor
  virtual ~Port();

  // specific
  virtual BipError &execute(PortValue &portValue) = 0;
  virtual ResetableItf &reset() = 0;
};

#endif // _BIP_Engine_Port_HPP_
