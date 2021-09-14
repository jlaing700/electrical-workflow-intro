#include <SPI.h>
#define CAN_2515

/*
set up the SPI and CAN PIN
*/
#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else
// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif
#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif
#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

unsigned char yled = 0x01;
#define LED 8                                               //LED to pin 8

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);                      //Serial Monitor Baud Rate
    pinMode(LED, OUTPUT);                                   //set LED as output
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {              // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

void loop() {
    unsigned char len = 0;                                  //data length
    unsigned char buf[1];                                   //buffer array
    
    if (CAN_MSGAVAIL == CAN.checkReceive()) {               // check if data coming
        CAN.readMsgBuf(&len, buf);                          // read data and take data length

        unsigned long canId = CAN.getCanId();               //get CAN master ID

        SERIAL_PORT_MONITOR.println("-----------------------------");
        SERIAL_PORT_MONITOR.println("get data from ID: C1");
        SERIAL_PORT_MONITOR.println(canId, HEX);
        if(buf[0]) {                                        //if else based on buffer value
          digitalWrite(LED, LOW);                           //LED off
          delay(100);
        }else{
          SERIAL_PORT_MONITOR.println("LED ON");
          digitalWrite(LED, HIGH);                          //LED on
          delay(100);
        }
        for(int i = 0; i < len; i++){                       //prints current buffer value
          SERIAL_PORT_MONITOR.print(buf[i]);
          SERIAL_PORT_MONITOR.print("\t");
        }
        SERIAL_PORT_MONITOR.println();
    }
