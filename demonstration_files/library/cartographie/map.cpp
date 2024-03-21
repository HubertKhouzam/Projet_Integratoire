#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "map.h"

uint8_t sizeUnicode = 3;
uint8_t STOPBIT = 255;

uint8_t ASCIITAPECONTOURTOP[3] = {226, 149, 166};
uint8_t ASCIITAPECONTOURBOT[3] = {226, 149, 169};
uint8_t ASCIITAPEVERTICAL[3] = {226, 149, 145};
uint8_t ASCIIR1VERTICAL[3] = {124, 0, 0};
uint8_t ASCIIR1HORIZONTAL[3] = {226, 148, 128};
uint8_t ASCIIR1FRONTSLASH[3] = {226, 149, 177};
uint8_t ASCIIR1BACKSLASH[3] = {226, 149, 178};
uint8_t ASCIIR1WHEEL[3] = {234, 152, 136};

POSITION_R1 Map::evaluatePosition(bool isFacingCorner, BoxPosition pos)
{
    if (isFacingCorner && pos == BoxPosition::Right)
    {
        return POSITION_R1::DOWN_NOSE_DOWN;
    }
    if (isFacingCorner && pos == BoxPosition::Left)
    {
        return POSITION_R1::UP_NOSE_UP;
    }
    if (!isFacingCorner && pos == BoxPosition::Right)
    {
        return POSITION_R1::DOWN_NOSE_UP;
    }
    if (!isFacingCorner && pos == BoxPosition::Left)
    {
        return POSITION_R1::UP_NOSE_DOWN;
    }
}

void Map::setPosR1(POSITION_R1 position)
{
    if (position == POSITION_R1::UP_NOSE_UP || position == POSITION_R1::UP_NOSE_DOWN)
    {
        replaceInMemory(calculateMemory(6, 18), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(6, 19), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(6, 17), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(6, 20), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(7, 15), ASCIIR1FRONTSLASH);
        replaceInMemory(calculateMemory(7, 22), ASCIIR1BACKSLASH);
        replaceInMemory(calculateMemory(11, 15), ASCIIR1BACKSLASH);
        replaceInMemory(calculateMemory(11, 22), ASCIIR1FRONTSLASH);
        replaceInMemory(calculateMemory(12, 18), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(12, 19), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(12, 17), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(12, 20), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(9, 15), ASCIIR1VERTICAL);
        replaceInMemory(calculateMemory(9, 22), ASCIIR1VERTICAL);

        if (position == POSITION_R1::UP_NOSE_UP)
        {
            replaceInMemory(calculateMemory(8, 15), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(8, 22), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(10, 15), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(10, 22), ASCIIR1WHEEL);
        }
        else if (position == POSITION_R1::UP_NOSE_DOWN)
        {
            replaceInMemory(calculateMemory(8, 15), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(8, 22), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(10, 15), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(10, 22), ASCIIR1VERTICAL);
        }
    }
    else if (position == POSITION_R1::DOWN_NOSE_DOWN || position == POSITION_R1::DOWN_NOSE_UP)
    {
        replaceInMemory(calculateMemory(24, 18), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(24, 19), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(24, 17), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(24, 20), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(23, 15), ASCIIR1BACKSLASH);
        replaceInMemory(calculateMemory(23, 22), ASCIIR1FRONTSLASH);
        replaceInMemory(calculateMemory(19, 15), ASCIIR1FRONTSLASH);
        replaceInMemory(calculateMemory(19, 22), ASCIIR1BACKSLASH);
        replaceInMemory(calculateMemory(18, 18), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(18, 19), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(18, 17), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(18, 20), ASCIIR1HORIZONTAL);
        replaceInMemory(calculateMemory(21, 15), ASCIIR1VERTICAL);
        replaceInMemory(calculateMemory(21, 22), ASCIIR1VERTICAL);

        if (position == POSITION_R1::DOWN_NOSE_UP)
        {
            replaceInMemory(calculateMemory(20, 15), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(20, 22), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(22, 15), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(22, 22), ASCIIR1WHEEL);
        }
        else if (position == POSITION_R1::DOWN_NOSE_DOWN)
        {
            replaceInMemory(calculateMemory(20, 15), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(20, 22), ASCIIR1WHEEL);
            replaceInMemory(calculateMemory(22, 15), ASCIIR1VERTICAL);
            replaceInMemory(calculateMemory(22, 22), ASCIIR1VERTICAL);
        }
    }
}

int Map::posToCol(uint8_t pos, uint8_t orientation)
{
    if (orientation == 0)
    {
        return (float(pos) / float(TAPELENGTHUP)) * TAPELENGTHUNICODE + FIRSTHALFLENGTH;
    }
    else
    {
        return 122 - ((float(pos) / float(TAPELENGTHDOWN)) * TAPELENGTHUNICODE);
    }
}

int Map::orientationToLine(int orientation)
{
    int line;
    if (LineType(orientation) == LineType::UP)
    {
        line = 9;
    }
    else
    {
        line = 21;
    }
    return line;
}

int Map::calculateMemory(int line, int col)
{

    return ((line - 1) * MAPLENGTH + (col - 1)) * UNICODESIZE;
}

void Map::replaceInMemory(uint16_t address, uint8_t *unicode)
{
    for (int i = 0; i < 3; i++)
    {
        mem.ecriture(address++, unicode[i]);
        _delay_ms(5);
    }
}

void Map::modifyMapLine(int position, int longueur, int orientation)
{
    uint8_t line = orientationToLine(orientation);
    uint8_t col = posToCol(position, orientation);
    uint16_t address = calculateMemory(line, col);
    if ((LineType)orientation == LineType::UP)
    {
        replaceInMemory(address, ASCIITAPECONTOURTOP);
        replaceInMemory(address + ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        replaceInMemory(address + 2 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        if (longueur >= 1)
        {
            replaceInMemory(address + 3 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        }
        if (longueur >= 2)
        {
            replaceInMemory(address + 4 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        }
    }
    else if (LineType(orientation) == LineType::DOWN)
    {
        replaceInMemory(address, ASCIITAPECONTOURBOT);
        replaceInMemory(address - ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        replaceInMemory(address - 2 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        if (longueur >= 1)
        {
            replaceInMemory(address - 3 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        }
        if (longueur >= 2)
        {
            replaceInMemory(address - 4 * ((MAPLENGTH)*UNICODESIZE), ASCIITAPEVERTICAL);
        }
    }
}

void Map::read_map()
{
    bool isLedON = false;
    uint8_t countLed = 0;
    uint16_t adresse = 0;
    uint8_t count = 0;

    while (count < 3)
    {
        uint8_t tempInstruction;
        mem.lecture(adresse++, &tempInstruction);
        if (tempInstruction == 0xFF)
        {
            count++;
        }
        else if (tempInstruction != 0)
        {
            com.writeValueUART(tempInstruction);
        }
        _delay_ms(5);
        countLed++;
        isLedON = ((countLed % 20) == 0) ? !isLedON : isLedON;
        if (isLedON)
        {
            led.setGreen();
        }
        else
        {
            led.setOff();
        }
    }
}

void Map::upload_map()
{
    uint8_t count = 0;
    uint16_t adresse = 0;

    while (count < 3)

    {
        uint8_t tempInstruction = com.readValueUART();
        mem.ecriture(adresse++, tempInstruction);
        _delay_ms(DELAY_WRITE_MS);
        if (tempInstruction == STOPBIT)
        {
            count++;
        }
    }
}

void Map::modifyAllLines(uint8_t mesurements[18], uint8_t lineMesures[2])
{
    TAPELENGTHUP = lineMesures[0];
    TAPELENGTHDOWN = lineMesures[1];
    for (int i = 0; i < 18; i += 3)
    {
        uint8_t pos = mesurements[i];
        uint8_t length = mesurements[i + 1];
        uint8_t orientation = mesurements[i + 2];
        if (pos > 0)
        {

            modifyMapLine(pos, length, orientation);
        }
        else
        {
            break;
        }
    }
}
