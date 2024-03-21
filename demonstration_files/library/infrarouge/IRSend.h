#pragma once
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 80000000
#include <util/crc16.h>
#include <avr/interrupt.h>
#include "../Led/Led.h"
#include "../MemoryAndComm/communication.h"
#include <string.h>

const uint8_t STOPBITARRAY = 100;

class IRSend

{
public:
    void init();
    void lightUp();
    void closeLed();
    void outputZero();
    void outputOne();
    void outputStart();
    void disableLed();
    void uint8ToArray(uint8_t value, uint8_t arr[8]);
    void sendArray(uint8_t arr[20]);
    void sendArrayTapeLength(uint8_t arr[2]);
    void sendValue(uint8_t value);
    void sendArrayWithCRC(uint8_t arr[18], uint8_t linesMesures[2]);

    void calculationCRC(uint8_t data);
    void printArrayBytes(uint8_t arr[18]);

    LED ledIRSend = LED(&DDRA, &PORTA, 5, 7);
    uint8_t transmissionValues_[18] = {0};

private:
    uint16_t crc_ = 0;
    uint8_t MAXLENGHTTRANSMISSION = 20;
    uint8_t BYTELENGTH = 8;
    Communication com;
};