#include "usr_sdm_controller/can_protocol.hpp"

//MCP2515 can0;
//struct can_frame rx;

namespace amp
{
namespace usrsdm
{

MCP_CAN::Ptr CAN;

void printCANMsg()
{
    uint8_t  len    = 0;
    uint8_t  buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint32_t canId  = 0;

    printf("CAN Interrupt Triggered\n");
    if (CAN_MSGAVAIL == CAN->checkReceive())  // check if data coming
    {
        // uint8_t MCP_CAN::readMsgBuf(uint32_t *id, uint8_t *len, uint8_t buf[])
        // Read data rellena canId, len y guarda los datos en buf
        CAN->readMsgBuf(&canId, &len, &buf[0]);

        canId = canId & 0x1FFFFFFF;

        printf("-----------------------------\n");
        printf("Received data from ID: %u | len:%d\n", canId, len);

        for (int i = 0; i < len; i++) // print the data
        {
            printf("(%d)", buf[i]);
            printf("\t");
        }
    }
}

CANProtocol::CANProtocol()
{
//	interfaceSetup();
	printf("CAN initialized.\n");
}

CANProtocol::~CANProtocol() {}

void CANProtocol::interfaceSetup(void)
{
	CAN.reset(new MCP_CAN);

	CAN->init_Para(SPI_CHANNEL, 2000000, IntPIN, SPI_CS_PIN);
	wiringPiSetup();

    int result = wiringPiSetupGpio();
    if (!result)
    {
        printf("Gpio started\n");
    }
    else
    {
        printf("Gpio startup fail\n");
    }
    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);

//	CAN->setupInterruptGpio();
//    CAN->setupSpi();
//    printf("GPIO Pins initialized & SPI started\n");
//
//    // Attach interrupt to read incoming messages
//    wiringPiISR(IntPIN, INT_EDGE_FALLING, printCANMsg);
//
//    /* Start CAN bus
//     * uint8_t begin(uint8_t idmodeset, uint8_t speedset, uint8_t clockset);
//     */
//
//    while (CAN_OK != CAN->begin(MCP_ANY, CANSpeed, MCPClock))
//    {
//        printf("CAN BUS Shield init fail\n");
//        printf("Trying to init CAN BUS Shield again\n\n");
//
//        struct timespec req;
//        req.tv_sec = 1;        // seconds
//        req.tv_nsec = 0; // nanoseconds
//        nanosleep(&req, nullptr);
//    }
//    printf("CAN BUS Shield init ok!\n");
//    CAN->setMode(MCPMode);
//
//    uint8_t  data[8] = { 3, 14, 15, 2, 1, 2, 3, 4 };
//    printf("\n\nMessage sent: %d\n", CAN->sendMsgBuf(5, 0, 8, data));
}

//void CANProtocol::startCAN()
//{
//	digitalWrite(SPI_CS_PIN, LOW);
//    std::cout << "Start CAN Interface" << std::endl;
//}
//
//void CANProtocol::endCAN()
//{
//	digitalWrite(SPI_CS_PIN, HIGH);
//    std::cout << "End CAN Interface" << std::endl;
//}

//void CANProtocol::printCANMsg(const MCP_CAN& can)
//void CANProtocol::printCANMsg()
//{
//    uint8_t  len    = 0;
//    uint8_t  buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
//    uint32_t canId  = 0;
//
////    auto check_receive = &CAN->checkReceive();
//
//    printf("CAN Interrupt Triggered\n");
//    if (CAN_MSGAVAIL == CAN->checkReceive())  // check if data coming
//    {
//        // uint8_t MCP_CAN::readMsgBuf(uint32_t *id, uint8_t *len, uint8_t buf[])
//        // Read data rellena canId, len y guarda los datos en buf
//        CAN->readMsgBuf(&canId, &len, &buf[0]);
//
//        canId = canId & 0x1FFFFFFF;
//
//        printf("-----------------------------\n");
//        printf("Received data from ID: %lu | len:%d\n", canId, len);
//
//        for (int i = 0; i < len; i++) // print the data
//        {
//            printf("(%d)", buf[i]);
//            printf("\t");
//        }
//    }
//}

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
