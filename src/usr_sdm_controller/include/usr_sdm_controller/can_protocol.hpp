#ifndef CAN_PROTOCOL_H_
#define CAN_PROTOCOL_H_

namespace amp
{
namespace usrsdm
{

class CANProtocol
{
  public:
	CANProtocol();
    virtual ~CANProtocol();

  protected:
    void interfaceSetup (int speed);
}

} //usrsdm
} //amp

#endif /* CAN_PROTOCOL_H_ */
