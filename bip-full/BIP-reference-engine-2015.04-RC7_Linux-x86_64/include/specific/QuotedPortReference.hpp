#ifndef _BIP_Engine_QuotedPortReference_HPP_
#define _BIP_Engine_QuotedPortReference_HPP_

// inherited classes
#include <QuotedPortReferenceItf.hpp>

class QuotedPortReference : public QuotedPortReferenceItf {
 public:
  // constructors
  QuotedPortReference(Port &port, const bool &trigger);

  // destructor
  virtual ~QuotedPortReference();
};

#endif // _BIP_Engine_QuotedPortReference_HPP_
