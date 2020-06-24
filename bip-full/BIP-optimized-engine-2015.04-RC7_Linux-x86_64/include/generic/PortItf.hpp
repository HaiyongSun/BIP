#ifndef _BIP_Engine_PortItf_HPP_
#define _BIP_Engine_PortItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class PortValue;


class PortItf {
 public:
  // destructor
  virtual ~PortItf();

  // operations
  virtual const vector<PortValue *> &portValues() const = 0;
  virtual bool hasPortValues() const = 0;

  // getters for attributes
  const string &name() const { return mName; }
  const ExportType &type() const { return mType; }

 protected:
  // protected constructors
  PortItf(const string &name, const ExportType &type);

  // attributes
  const string mName;
  const ExportType mType;
};

#endif // _BIP_Engine_PortItf_HPP_
