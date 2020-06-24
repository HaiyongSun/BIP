#ifndef _BIP_Engine_AtomInternalPort_HPP_
#define _BIP_Engine_AtomInternalPort_HPP_

// inherited classes
#include <AtomInternalPortItf.hpp>

class AtomInternalPort : public AtomInternalPortItf {
 public:
  // constructors
  AtomInternalPort(const string &name);

  // destructor
  virtual ~AtomInternalPort();

  // specific
  bool isExported() const;
};

#endif // _BIP_Engine_AtomInternalPort_HPP_
