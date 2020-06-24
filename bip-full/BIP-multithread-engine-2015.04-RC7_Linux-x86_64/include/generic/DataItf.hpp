#ifndef _BIP_Engine_DataItf_HPP_
#define _BIP_Engine_DataItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;


class DataItf {
 public:
  // destructor
  virtual ~DataItf();

  // getters for attributes
  const string &name() const { return mName; }
  const ExportType &type() const { return mType; }

 protected:
  // protected constructors
  DataItf(const string &name, const ExportType &type);

  // attributes
  const string mName;
  const ExportType mType;
};

#endif // _BIP_Engine_DataItf_HPP_
