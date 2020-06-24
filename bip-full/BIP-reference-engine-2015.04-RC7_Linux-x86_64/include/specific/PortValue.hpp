#ifndef _BIP_Engine_PortValue_HPP_
#define _BIP_Engine_PortValue_HPP_

// inherited classes
#include <PortValueItf.hpp>

class  PortValue : public PortValueItf {
 public:
  // constructors
  PortValue();

  // destructor
  virtual ~PortValue();

  virtual string toString() const { return "?"; };

  // specific
  friend ostream& operator<<(ostream &o, const PortValue &value);
  friend ostream& operator<<(ostream &o, const PortValue *value);
};

#endif // _BIP_Engine_PortValue_HPP_
