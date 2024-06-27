#ifndef CAN_PROTOCOL_H_
#define CAN_PROTOCOL_H_

#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdio>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "usr_sdm_controller/mcp_can_rpi.hpp"
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
    const int SPI_CHANNEL = 0;
    const uint8_t SPI_CS_PIN = 8;
    const uint8_t IntPIN = 25;
    const uint8_t CANSpeed = CAN_500KBPS;
    const uint8_t MCPClock = MCP_12MHZ;
    const uint8_t MCPMode = MCP_NORMAL;
    MCP_CAN CAN;

    void interfaceSetup (void);
//    void startCAN(void);
//    void endCAN(void);
};

} //usrsdm
} //amp

#endif /* CAN_PROTOCOL_H_ */
