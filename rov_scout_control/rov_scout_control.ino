/*
 Name:		rov_scout_control.ino
 Created:	04.12.2017 17:40:48
 Author:	zinjk
*/

#include "PS2X_lib.h"
#include "crc.h"


#define PS2_DAT        13  //14
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

#define EMPTY_COMMAND 0

#define GRAB 1
#define RELEASE 2

#define START_HIGH_BYTE 0xFE
#define START_LOW_BYTE 0xAE

#define START_HIGH_BYTE_COMMAND 0
#define START_LOW_BYTE_COMMAND 1
#define HORIZONTAL_MOTOR_Y_COMMAND 2
#define HORIZONTAL_MOTOR_X_COMMAND 3
#define VERTICAL_MOTOR_Y_COMMAND 4
#define VERTICAL_MOTOR_X_COMMAND 5
#define MANIPULATOR_COMMAND 6
#define CAMERA_COMMAND 7
#define CRC_COMMAND 8
#define COMMAND_BUFFER_SIZE 9



PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;

#define DEBUG

#ifdef DEBUG
#define DEBUG_PORT Serial
#include "debug_printer.h"
#endif

void setup() {

	Serial.begin(57600);
	Serial2.begin(115200);
	delay(300);

	error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
	type = ps2x.readType();
#ifdef DEBUG
	print_initial_debug_info(type, error);
#endif
}

void loop() {
	uint8_t buffer[COMMAND_BUFFER_SIZE] = { EMPTY_COMMAND };

	ps2x.read_gamepad(false, vibrate);

	buffer[START_HIGH_BYTE_COMMAND] = START_HIGH_BYTE;
	buffer[START_LOW_BYTE_COMMAND] = START_LOW_BYTE;
	buffer[HORIZONTAL_MOTOR_Y_COMMAND] = ps2x.Analog(PSS_LY);
	buffer[HORIZONTAL_MOTOR_X_COMMAND] = ps2x.Analog(PSS_LX);
	buffer[VERTICAL_MOTOR_Y_COMMAND] = ps2x.Analog(PSS_RY);
	buffer[VERTICAL_MOTOR_X_COMMAND] = ps2x.Analog(PSS_RX);

	if (ps2x.Button(PSB_L2)) {
		buffer[MANIPULATOR_COMMAND] = RELEASE;
	}
	if (ps2x.Button(PSB_R2)) {
		buffer[MANIPULATOR_COMMAND] = GRAB;
	}

	if (ps2x.Button(PSB_L1)) {
		buffer[CAMERA_COMMAND] = 1;
	}
	if (ps2x.Button(PSB_R1)) {
		buffer[CAMERA_COMMAND] = -1;
	}
 
	buffer[CRC_COMMAND] = crc::calculate_crc(buffer, COMMAND_BUFFER_SIZE - 1);

	if((buffer[HORIZONTAL_MOTOR_Y_COMMAND] + buffer[HORIZONTAL_MOTOR_X_COMMAND] +  
		buffer[VERTICAL_MOTOR_Y_COMMAND] + buffer[VERTICAL_MOTOR_X_COMMAND]) == (255 + 255 + 255 + 255)) {
		return;
	}
  
	Serial2.write(buffer, COMMAND_BUFFER_SIZE);
	delay(5);
 #ifdef DEBUG
   print_debug_info(buffer);
  #endif

}
