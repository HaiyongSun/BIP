#ifndef _BIP_Engine_StringTree_HPP_
#define _BIP_Engine_StringTree_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include <string>
#include <iostream>
#include <sstream>

/** \brief Represent a node in a tree of strings
 */
class StringTree {
 public:
  // constructor and destructor
  StringTree() { };
  StringTree(const string &value);
  StringTree(const StringTree &tree);
  virtual ~StringTree();

  // setters and getters
  void addChild(const StringTree &child) { mChilds.push_back(new StringTree(child)); }
  void addChild(const string &child) { addChild(StringTree(child)); }
  const vector<StringTree *> &childs() const { return mChilds; }
  const string &value() const { return mValue; }

  // operations
  string toString(string &headerHead, string &headerTail) const;
  string toString(string &header) const { return toString(header, header); }
  string toString() const { string empty; return toString(empty); }

 protected:
  // protected setters and getters
  vector<StringTree *> &childs() { return mChilds; }

  // protected attributes
  vector<StringTree *> mChilds;
  string mValue;

  // friend operations
  friend ostream& operator<<(ostream &o, const StringTree &tree);
};

#endif // _BIP_Engine_StringTree_HPP_
