#ifndef __DS18B20_H
#define __DS18B20_H
#include "main.h"
#include "onewire.h"
// Dinh nghia do phan giai su dung
#define DS18B20_9BIT_RES 0  // Do phan giai 9bit
#define DS18B20_10BIT_RES 1 // Do phan giai 10bit
#define DS18B20_11BIT_RES 2 // Do phan giai 11bit
#define DS18B20_12BIT_RES 3 // Do phan giai 12bit

// Dinh nghia cac lenh ROM
#define DS1820_CMD_SEARCHROM     0xF0   // Tim so luong DS18B20 tren bus va gia tri 64 bit ROM cua cac DS18B20   
#define DS1820_CMD_READROM       0x33   // Doc gia tri 8 Byte ma khac tren ROM DS18B20
#define DS1820_CMD_MATCHROM      0x55   // Chon DS18B20 can giao tiep, gui truoc 64 Bit ROM DS18B20 can chon
#define DS1820_CMD_SKIPROM       0xCC   // Truy cap thang den bo nho cua DS18B20
#define DS1820_CMD_ALARMSEARCH   0xEC   // Tim DS18B20 co co bao dong duoc bat

// Dinh nghia cac lenh chuc nang
#define DS1820_CMD_CONVERTTEMP   0x44   // Khoi dong qua trinh do va chuyen doi gia tri nhiet do thanh so nhi phan
#define DS1820_CMD_WRITESCRPAD   0x4E   // Ghi gia tri vao 3 thanh ghi: TH, TL, Configuration register (Ghi tu MSB->LSB)
#define DS1820_CMD_READSCRPAD    0xBE   // Doc noi dung bo nho DS18B20: doc tu Byte0 -> Byte9, doc tu MSB->LSB
#define DS1820_CMD_COPYSCRPAD    0x48   // Copy gia tri 3 thanh ghi TH, TL, Config vao bo nho EEPROM
#define DS1820_CMD_RECALLEE      0xB8

float ds18b20_read(void); 
#endif
