#ifndef MYSERIALBT_HPP
#define MYSERIALBT_HPP

#include <BluetoothSerial.h>
#include "myGraphics.hpp"

extern uint8_t atomlite1_address[6];

extern BluetoothSerial SerialBT;
extern void bluetoothMasterBegin(uint8_t *address);
#endif