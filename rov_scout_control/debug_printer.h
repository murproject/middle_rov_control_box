//
// Created by zinjk on 04.10.2017.
//

#ifndef OVERWATER_FIRMWARE_DEBUG_PRINTER_H
#define OVERWATER_FIRMWARE_DEBUG_PRINTER_H
#include <Arduino.h>

void print_initial_debug_info(uint8_t type, int error) {
    if(error == 0){
        DEBUG_PORT.print("Found Controller, configured successful ");
        DEBUG_PORT.print("pressures = ");
        if (pressures)
            DEBUG_PORT.println("true ");
        else
            DEBUG_PORT.println("false");
        DEBUG_PORT.print("rumble = ");
        if (rumble)
            DEBUG_PORT.println("true)");
        else
            DEBUG_PORT.println("false");
        DEBUG_PORT.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        DEBUG_PORT.println("holding L1 or R1 will print out the analog stick values.");
        DEBUG_PORT.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }
    else if(error == 1)
        DEBUG_PORT.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if(error == 2)
        DEBUG_PORT.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        DEBUG_PORT.println("Controller refusing to enter Pressures mode, may not support it. ");
    switch(type) {
        case 0:
            DEBUG_PORT.print("Unknown Controller type found ");
            break;
        case 1:
            DEBUG_PORT.print("DualShock Controller found ");
            break;
        case 2:
            DEBUG_PORT.print("GuitarHero Controller found ");
            break;
        case 3:
            DEBUG_PORT.print("Wireless Sony DualShock Controller found ");
            break;
    }
}


void print_debug_info(uint8_t *data) {
    DEBUG_PORT.print("HORIZONTAL\tVALUE:");
    DEBUG_PORT.print(data[2], DEC); DEBUG_PORT.print(", ");
    DEBUG_PORT.println(data[3], DEC);

    DEBUG_PORT.print("VERTICAL\tVALUE:");
    DEBUG_PORT.print(data[4], DEC); DEBUG_PORT.print(", ");
    DEBUG_PORT.println(data[5], DEC);

    DEBUG_PORT.print("MANIPULATOR\tVALUE:");
    DEBUG_PORT.println(data[6], DEC);
    DEBUG_PORT.println("----------------");

    DEBUG_PORT.print("CRC\tVALUE:");
    DEBUG_PORT.println(data[7], DEC);
    DEBUG_PORT.println("----------------");

}
#endif //OVERWATER_FIRMWARE_DEBUG_PRINTER_H
