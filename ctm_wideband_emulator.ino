//Celebrate the Maker @ 2023
//M.Meszaros 
//HALTECH WIDEBAND EMULATOR 

#include <mcp_can.h>  // library for MCP2515 ic
#include <SPI.h>      // library for SPI communication (MCP2515 uses SPI)
#include "Timer.h"

Timer t;

#define CAN0_ID 0x2B1  // WB1=0x2B1	WB2A=0x2B0	WB2B=0x2B4	Wb2C=0x2B6	WB2D=0x2B6		These are Haltech's own wideband box IDs

#define CAN0_INT 2  // Set INT to pin 2
MCP_CAN CAN0(9);    // set CS pin to 9


void setup() {
  // start serial port an send a message with delay for starting
  Serial.begin(115200);
  Serial.println("Haltech Wideband Emulator - setup");

  // initialize Canbus with 1000kbit/8mhz 
  if (CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Init OK!");
  else Serial.println("MCP2515 ERROR");

  // Set operation mode to normal so the MCP2515 sends acks to received data.
  CAN0.setMode(MCP_NORMAL);

  pinMode(CAN0_INT, INPUT);        // set INT pin to be an input
  digitalWrite(CAN0_INT, HIGH);    // set INT pin high to enable internal pullup

  delay(100);
  t.every(50, CAN0_Broadcast);    //Start CAN Broadcast which matches Haltech broadcast rate 20Hz (every 50millisec the CAN0_SendWB function runs)
}


void loop() {

  t.update(); //Update the timer
  
}


void CAN0_Broadcast(){
	
  byte widebandInfo[7];  // declare an array for 7 bytes used for wideband information
  int wb1Status = 0;                                      // 0=Normal operation	1=Low Battery Voltage (< 9V)	2=High Battery Voltage (> 18V)	3=Sensor Short Circuit	4=Sensor Open Circuit	5=Sensor Cold
  int wb2Status = 0;                                      //In case of 2 sensors attached, codes are the same as above
  float lambda1 = 1.0;
  float lambda2 = 1.5;
  if (wb1Status == 0) {                                  //check WB1 status. If normal operation "0" then send parsed lambda value otherwise send 0.
    lambda1 = lambda1 * 1024;                            //0-1 byte   	32767=Free Air, otherwise y=x/1024
  } else lambda1 = 0;

  if (wb2Status == 0) {
    lambda2 = lambda2 * 1024;                            //2-3 byte		32767=Free Air, otherwise y=x/1024
  } else lambda2 = 0;
	
  byte wb1Resistor = 130;                                //4 byte		Ohm value.							Currently I don't know what Haltech ECU does with this value.
  byte wb2Resistor = 130;                                //5 byte		Ohm value.							Currently I don't know what Haltech ECU does with this value.
  byte status = (byte)((wb2Status << 4) | wb1Status);    //6 byte
  byte batteryV = 140;                                   //7 byte		V value. y = x*20/255 				Currently I don't know what Haltech ECU does with this value.
  
  //Prepare the can package.
  widebandInfo[0] = (byte)((lambda1 >> 8) & 0xFF);
  widebandInfo[1] = (byte)(lambda1 & 0xFF);
  widebandInfo[2] = (byte)((lambda2 >> 8) & 0xFF);
  widebandInfo[3] = (byte)(lambda2 & 0xFF);
  widebandInfo[4] = wb1Resistor;
  widebandInfo[5] = wb2Resistor;
  widebandInfo[6] = status;
  widebandInfo[7] = batteryV;
  CAN0.sendMsgBuf(CAN0_ID, 0, 7, widebandInfo);          // send the 3 byte data buffer at adres 18D
	
}
