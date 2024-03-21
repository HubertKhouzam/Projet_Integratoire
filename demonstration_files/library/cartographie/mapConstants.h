#pragma once
#include <avr/io.h>

enum class LineType : uint8_t
{
    UP = 0,
    DOWN = 1,
};

enum class POSITION_R1
{
    UP_NOSE_UP,
    UP_NOSE_DOWN,
    DOWN_NOSE_UP,
    DOWN_NOSE_DOWN,
};

// Table
char *UNICODETABLEHORIZONTAL = u8"\u2500";
char *UNICODETABLETOPLEFT = u8"\u250C";
char *UNICODETABLETOPRIGHT = u8"\u2510";
char *UNICODETABLEBOTTOMLEFT = u8"\u2514";
char *UNICODETABLEBOTTOMRIGHT = u8"\u2518";
char *UNICODETABLEVERTICAL = u8"\u2502";

// Boite
char *UNICODEBOXHORIZONTAL = u8"\u2501";
char *UNICODEBOXTOPLEFT = u8"\u250F";
char *UNICODEBOXTOPRIGHT = u8"\u2513";
char *UNICODEBOXBOTTOMLEFT = u8"\u2517";
char *UNICODEBOXBOTTOMRIGHT = u8"\u251B";
char *UNICODEBOXVERTICAL = u8"\u2503";

// Trajet robot 2
char *UNICODETAPEHORIZONTAL = u8"\u2550";
char *UNICODETAPETOPLEFT = u8"\u2554";
char *UNICODETAPETOPRIGHT = u8"\u2557";
char *UNICODETAPEBOTTOMRIGHT = u8"\u255D";
char *UNICODETAPEBOTTOMLEFT = u8"\u255A";
char *UNICODETAPEVERTICAL = u8"\u2551";
char *UNICODETAPET = u8"\u2563";
char *SPACE = " ";
char *ENTER = "\n";

const uint8_t DELAY_WRITE_MS = 5;
uint8_t sizeUnicode = 3;
uint8_t STOPBIT = 255;

const int MAPLENGTH = 127;
const int TAPELENGTHUNICODE = 80;
const int FIRSTHALFLENGTH = 42;
const int UNICODESIZE = 3;
const int BOXLENGTH = 26;
uint8_t ASCIITAPECONTOURTOP[3] = {226, 149, 166};
uint8_t ASCIITAPECONTOURBOT[3] = {226, 149, 169};
uint8_t ASCIITAPEVERTICAL[3] = {226, 149, 145};
uint8_t ASCIIR1VERTICAL[3] = {124, 0, 0};
uint8_t ASCIIR1HORIZONTAL[3] = {226, 148, 128};
uint8_t ASCIIR1FRONTSLASH[3] = {226, 149, 177};
uint8_t ASCIIR1BACKSLASH[3] = {226, 149, 178};
uint8_t ASCIIR1WHEEL[3] = {234, 152, 136};
