#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "MemoryAndComm/communication.h"
#include "MemoryAndComm/memoire_24.h"
#include "mapConstants.h"
#include "navigation/navigation.h"
#include "Led/Led.h"

class Map

{
public:
    int posToCol(uint8_t pos, uint8_t orientation);
    int orientationToLine(int orientation);
    int calculateMemory(int line, int col);
    POSITION_R1 evaluatePosition(bool isFacingCorner, BoxPosition pos);
    void replaceInMemory(uint16_t address, uint8_t *unicode);
    void setPosR1(POSITION_R1 position);
    void modifyMapLine(int position, int longueur, int orientation);
    void read_map();
    void printLeadSpace(uint8_t number);
    void printBlankMap();
    void upload_map();
    void modifyAllLines(uint8_t mesurements[], uint8_t linesMesures[2]);

private:
    Communication com;
    Memoire24CXXX mem;
    LED led = LED(&DDRC, &PORTC, PC2, PC3);
    int TAPELENGTHUP = 100;
    int TAPELENGTHDOWN = 100;
};