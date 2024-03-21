#pragma once
#define F_CPU 8000000
#include "IRRecieve.h"
#include <avr/io.h>
#include <avr/crc16.h>
#include <string.h>
#include "Led/Led.h"
#include <math.h>

LED led(&DDRB, &PORTB, 0, 1);

IRRecieve::IRRecieve()
{
    DDRA &= ~(1 << DDA1);
}

void IRRecieve::calculationCrc()
{
    for (int i = 0; i < 18; i++)
    {
        crcCalculated_ += transmission_[i];
    }
}

bool IRRecieve::getStart()
{
    return recievedStart_;
}

void IRRecieve::verifyStart()
{
    LED led(&DDRB, &PORTB, 0, 1);
    active_ = !(PINA & (1 << PINA1));
    while (true)
    {

        if (active_)
        {
            break;
        }
        active_ = !(PINA & (1 << PINA1));
    }

    counter_ = 0;
    while (active_ || counter_ <= 4)
    {

        _delay_us(100);
        counter_ += 1;
        active_ = !(PINA & (1 << PINA1));
    }
    if (counter_ >= 20 && counter_ <= 28)
    {
        recievedStart_ = true;
    }
}

uint8_t IRRecieve::recieveData()
{

    active_ = !(PINA & (1 << PINA1));
    while (true)
    {
        if (active_)
        {
            break;
        }
        active_ = !(PINA & (1 << PINA1));
    }

    counter_ = 0;
    while (active_ || counter_ <= 4)
    {
        _delay_us(100);
        counter_ += 1;
        active_ = !(PINA & (1 << PINA1));
    }

    if (counter_ >= 4 && counter_ <= 9)
    {

        return 0;
    }
    else if (counter_ >= 10 && counter_ <= 16)
    {

        return 1;
    }
}

void IRRecieve::recieveByte(uint8_t *array)
{

    verifyStart();
    for (int i = 0; i < 8; i++)
    {
        uint8_t data = recieveData();
        array[i] = data;
        _delay_ms(0.6);
    }
}

uint8_t IRRecieve::convertByteToNum(uint8_t *byte)
{
    uint8_t nb = 0;
    for (int i = 7; i >= 0; i--)
    {
        nb += (byte[i] * (1 << (7 - i)));
    }
    return nb;
}

uint8_t IRRecieve::convertByteToNum16(uint8_t *byte)
{
    uint8_t nb = 0;
    for (int i = 15; i >= 8; i--)
    {
        nb += (byte[i] * (1 << (7 - i)));
    }
    return nb;
}

void IRRecieve::recieveTapeLength()
{
    for (int i = 0; i < 2; i++)
    {
        uint8_t byte[8];
        recieveByte(byte);

        tapeLength_[i] = convertByteToNum(byte);
    }
}

void IRRecieve::recieveTransmission()
{
    for (int i = 0; i < 20; i++)
    {
        uint8_t byte[8];
        recieveByte(byte);
        if (i < 18)
        {

            transmission_[i] = convertByteToNum(byte);
        }
        else if (i == 18)
        {

            MSNum_ = convertByteToNum(byte) * 100;
        }
        else if (i == 19)
        {

            LSNum_ = convertByteToNum(byte);
        }
    }
    recieveTapeLength();
    calculationCrc();
    setRecieveCRC();
}

void IRRecieve::setRecieveCRC()
{
    crcRecieved_ = LSNum_ + MSNum_;
}