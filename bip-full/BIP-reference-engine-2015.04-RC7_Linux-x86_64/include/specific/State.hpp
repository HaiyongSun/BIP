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
  State &operator=(const State &state);

 protected:
  void setSize();

  char *mBuffer;
  size_t mSize;
};

#endif // _BIP_Engine_State_HPP_
