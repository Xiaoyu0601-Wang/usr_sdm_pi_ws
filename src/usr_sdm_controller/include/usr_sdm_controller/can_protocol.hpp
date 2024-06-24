#ifndef CAN_PROTOCOL_H_
#define CAN_PROTOCOL_H_

#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdio>

#include <wiringPi.h>
#include <wiringPiSPI.h>

//#include "mcp2515.h"

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
    const int SPI_CHAN = 0;
    const int SPI_CS_PIN = 10;

    void interfaceSetup (int speed);
    void startCAN();
    void endCAN();
};

} //usrsdm
} //amp

#endif /* CAN_PROTOCOL_H_ */
