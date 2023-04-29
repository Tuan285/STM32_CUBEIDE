#ifndef __ONE_WIRE_H
#define __ONE_WIRE_H

#include "main.h"

void OneWire_Reset(void);
void OneWire_Write(uint8_t data);
uint8_t OneWire_Read(void);
#endif
