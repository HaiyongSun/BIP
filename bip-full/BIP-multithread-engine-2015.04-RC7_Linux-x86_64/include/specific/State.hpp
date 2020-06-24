#ifndef _BIP_Engine_State_HPP_
#define _BIP_Engine_State_HPP_

#include <string>

/** \brief Represent a state of a model
 */
class State {
 public:
  State(char *buffer, size_t size);
  State(const State &state);
  virtual ~State();

  const char *buffer() const { return mBuffer; }
  size_t size() const { return mSize; }

  bool operator==(const State &state) const;
  bool operator!=(const State &state) const { return !(*this == state); }
  bool operator<(const State &state) const;

  State &operator=(const State &state);

  class Hash {
   public:
    size_t operator()(const State &state) const { return state.hash(); }
  };

 protected:
  char *buffer() { return mBuffer; }

  size_t hash() const { if (mResetHash) recomputeHash(); return mHash; }
  void recomputeHash() const;

  char *mBuffer;
  size_t mSize;

  mutable bool mResetHash;
  mutable size_t mHash;
};

#endif // _BIP_Engine_State_HPP_
