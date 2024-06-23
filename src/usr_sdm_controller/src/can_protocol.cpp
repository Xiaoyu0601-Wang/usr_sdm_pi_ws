#include "usr_sdm_controller/can_protocol.hpp"

#include "mcp2515/mcp2515.h"

MCP2515 can0;
struct can_frame rx;

CANProtocol::CANProtocol()
{

}

CANProtocol::~CANProtocol() {}

void CANProtocol::interfaceSetup (int speed)
{
  if ((myFd = wiringPiSPISetup (SPI_CHAN, speed)) < 0)
  {
    fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
    exit (EXIT_FAILURE) ;
  }
}

int main() {
    stdio_init_all();

    //Initialize interface
    can0.reset();
    can0.setBitrate(CAN_1000KBPS, MCP_16MHZ);
    can0.setNormalMode();

    //Listen loop
    while(true) {
        if(can0.readMessage(&rx) == MCP2515::ERROR_OK) {
            printf("New frame from ID: %10x\n", rx.can_id);
        }
    }

    return 0;
}
