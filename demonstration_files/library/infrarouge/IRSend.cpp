/*
Auteurs       : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
Collaboration : Olivier Thabet 2294559

Description  : Définition de la classe qui à comme fonction de gérer la transmission de l'information
par infrarouge

Branchements : 2 Branchements au total : - Sortie : Broche Vcc de la LED infrarouge sur D4
                                         - Sortie : Broche Gnd de la LED infrarouge sur D5
 */

#define F_CPU 8000000
#include "IRSend.h"
#include <avr/io.h>
#include <string.h>

void IRSend::init()
{

    DDRD |= (1 << DDD4) | (1 << DDD5);
    TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << WGM13) | (1 << CS10);
    OCR1A = 100;
    OCR1B = 50;
}

void IRSend::lightUp()
{

    TCCR1B |= (1 << CS10);
}

void IRSend::closeLed()
{
    TCCR1B &= ~(1 << CS10);
}

void IRSend::outputZero()
{

    lightUp();
    _delay_ms(0.6);
    closeLed();
    _delay_ms(1.2);
}

void IRSend::outputOne()
{
    lightUp();
    _delay_ms(1.2);
    closeLed();
    _delay_ms(0.6);
}
void IRSend::outputStart()
{
    init();
    _delay_ms(2.4);
    closeLed();
    _delay_ms(0.6);
}

void IRSend::disableLed()
{
    DDRD &= ~((1 << DDD4) | (1 << DDD5));
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 0;
    OCR1B = 0;
}
void IRSend::uint8ToArray(uint8_t value, uint8_t arr[8])
{
    for (int i = 0; i < BYTELENGTH; ++i)
    {
        arr[7 - i] = (value >> i) & 1;
    }
}

void IRSend::sendArray(uint8_t arr[20])
{
    uint8_t byteArray[BYTELENGTH];

    for (int i = 0; i < 20; i++)
    {
        uint8ToArray(arr[i], byteArray);
        outputStart();
        for (int i = 0; i < BYTELENGTH; i++)
        {
            if (byteArray[i] == 1)
            {
                outputOne();
            }

            else if (byteArray[i] == 0)
            {
                outputZero();
            }
        }
    }
}

void IRSend::sendArrayTapeLength(uint8_t arr[2])
{
    uint8_t byteArray[BYTELENGTH];

    for (int i = 0; i < 2; i++)
    {
        uint8ToArray(arr[i], byteArray);
        outputStart();
        for (int i = 0; i < BYTELENGTH; i++)
        {
            if (byteArray[i] == 1)
            {
                outputOne();
            }

            else if (byteArray[i] == 0)
            {
                outputZero();
            }
        }
    }
}

void IRSend::sendValue(uint8_t value)
{
    uint8_t byteArray[BYTELENGTH];
    init();

    uint8ToArray(value, byteArray);
    outputStart();
    for (int i = 0; i < BYTELENGTH; i++)
    {
        if (byteArray[i] == 1)
        {
            outputOne();
        }

        else if (byteArray[i] == 0)
        {
            outputZero();
        }
    }
}

void IRSend::sendArrayWithCRC(uint8_t arr[18], uint8_t linesMesures[2])
{
    init();

    for (int i = 0; i < 18; i++)
    {
        calculationCRC(arr[i]);
    }
    uint8_t weakCRC = crc_ % 100;
    uint8_t strongCRC = crc_ / 100;
    uint8_t crcArray[20];
    for (int i = 0; i < MAXLENGHTTRANSMISSION; i++)
    {
        crcArray[i] = arr[i];
    }
    crcArray[18] = strongCRC;
    crcArray[19] = weakCRC;
    sendArray(crcArray);
    sendArrayTapeLength(linesMesures);
    disableLed();
}

void IRSend::calculationCRC(uint8_t data)
{
    crc_ += data;
}

void IRSend::printArrayBytes(uint8_t arr[18])
{

    uint8_t arrByte[8];
    for (int i = 0; i < 18; i++)
    {
        uint8ToArray(arr[i], arrByte);
        for (int i = 0; i < 8; i++)
        {
            com.writeValueUART(arrByte[i]);
        }
    }
}
