#ifndef CAN_PROTOCOL_H_
#define CAN_PROTOCOL_H_

#include <iostream>
#include <memory>
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

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
  protected:
    const int SPI_CHANNEL = 0;
    const uint8_t SPI_CS_PIN = 8;
    const uint8_t SPI_INT_PIN = 25;
    const uint8_t CANSpeed = CAN_500KBPS;
    const uint8_t MCPClock = MCP_12MHZ;
    const uint8_t MCPMode = MCP_NORMAL;

    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
//    const uint8_t CAN_EXT = 1;

//  public:
//    MCP_CAN::Ptr CAN;

//    void startCAN(void);
//    void endCAN(void);

  public:
	CANProtocol();
    virtual ~CANProtocol();

//    static MCP_CAN CAN;

    void interfaceSetup(void);
//    static void printCANMsg(const MCP_CAN& can);
//    static void printCANMsg();

    typedef std::unique_ptr<CANProtocol> Ptr;
};

} //usrsdm
} //amp

#endif /* CAN_PROTOCOL_H_ */
