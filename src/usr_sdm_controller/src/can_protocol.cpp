#include "usr_sdm_controller/can_protocol.hpp"

//MCP2515 can0;
//struct can_frame rx;

namespace amp
{
namespace usrsdm
{

CANProtocol::CANProtocol()
{
	interfaceSetup(2);
}

CANProtocol::~CANProtocol() {}

void CANProtocol::interfaceSetup(int speed)
{
	wiringPiSetup();
	pinMode(SPI_CS_PIN, OUTPUT);

	if (wiringPiSPISetup(SPI_CHAN, speed) < 0)
	{
		fprintf(stderr, "Can't open the SPI bus: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void CANProtocol::startCAN()
{
	digitalWrite(SPI_CS_PIN, LOW);
    std::cout << "Start CAN Interface" << std::endl;
}

void CANProtocol::endCAN()
{
	digitalWrite(SPI_CS_PIN, HIGH);
    std::cout << "End CAN Interface" << std::endl;
}

} //usrsdm
} //amp

//int main() {
//    stdio_init_all();
//
//    //Initialize interface
//    can0.reset();
//    can0.setBitrate(CAN_1000KBPS, MCP_16MHZ);
//    can0.setNormalMode();
//
//    //Listen loop
//    while(true) {
//        if(can0.readMessage(&rx) == MCP2515::ERROR_OK) {
//            printf("New frame from ID: %10x\n", rx.can_id);
//        }
//    }
//
//    return 0;
//}
