#ifndef _BIP_Engine_PortValue_HPP_
#define _BIP_Engine_PortValue_HPP_

// inherited classes
#include <PortValueItf.hpp>
#include <Port.hpp>

class InteractionValue;

class  PortValue : public PortValueItf {
 public:
  // constructors
  PortValue();

  // destructor
  virtual ~PortValue();

  virtual string toString() const { return "?"; };

  // specific
  InteractionValue &interaction() const { return *mInteraction; }
  bool hasInteraction() const { return mInteraction != NULL; }
  void setInteraction(InteractionValue &interaction) { mInteraction = &interaction; }
  
  Port &port() const { return *mPort; }
  bool hasPort() const { return mPort != NULL; }
  void setPort(Port &port) { mPort = &port; }

  friend ostream& operator<<(ostream &o, const PortValue &value);
  friend ostream& operator<<(ostream &o, const PortValue *value);

 private:
  // backward link to interaction or port values value
  InteractionValue *mInteraction;
  Port *mPort;
};

#endif // _BIP_Engine_PortValue_HPP_
