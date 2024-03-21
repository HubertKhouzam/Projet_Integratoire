#define F_CPU 8000000
#include "map.h"

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

void Map::printLeadSpace(uint8_t number)
{
    for (int i = 0; i < number; i++)
    {
        com.writeSentenceUART(SPACE);
    }
}

void Map::printBlankMap()
{
    com.writeSentenceUART(ENTER);
    // Ligne 1
    com.writeSentenceUART(UNICODETABLETOPLEFT);
    for (int i = 0; i < 124; i++)
    {
        com.writeSentenceUART(UNICODETABLEHORIZONTAL);
    }
    com.writeSentenceUART(UNICODETABLETOPRIGHT);
    com.writeSentenceUART(ENTER);

    // Lignes 2-4
    for (int i = 0; i < 3; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(124);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }

    // Ligne 5
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXTOPLEFT);
    for (int i = 0; i < 26; i++)
    {
        com.writeSentenceUART(UNICODEBOXHORIZONTAL);
    }
    com.writeSentenceUART(UNICODEBOXTOPRIGHT);
    printLeadSpace(93);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Lignes 6-8
    for (int i = 0; i < 3; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(26);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(93);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }
    // Ligne 9
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(26);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(10);
    com.writeSentenceUART(UNICODETAPETOPLEFT);
    for (int i = 0; i < 78; i++)
    {
        com.writeSentenceUART(UNICODETAPEHORIZONTAL);
    }
    com.writeSentenceUART(UNICODETAPETOPRIGHT);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Ligne 10-12
    for (int i = 0; i < 4; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(26);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(10);
        com.writeSentenceUART(UNICODETAPEVERTICAL);
        printLeadSpace(78);
        com.writeSentenceUART(UNICODETAPEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }

    // Ligne 13
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(27);
    printLeadSpace(10);
    com.writeSentenceUART(UNICODETAPEVERTICAL);
    printLeadSpace(78);
    com.writeSentenceUART(UNICODETAPEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Ligne 14
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(25);
    printLeadSpace(10);
    com.writeSentenceUART(UNICODETAPEHORIZONTAL);
    com.writeSentenceUART(UNICODETAPEHORIZONTAL);
    com.writeSentenceUART(UNICODETAPET);

    printLeadSpace(78);
    com.writeSentenceUART(UNICODETAPEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Ligne 15
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(27);
    printLeadSpace(10);
    com.writeSentenceUART(UNICODETAPEVERTICAL);
    printLeadSpace(78);
    com.writeSentenceUART(UNICODETAPEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Ligne 16-18
    for (int i = 0; i < 4; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(26);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(10);
        com.writeSentenceUART(UNICODETAPEVERTICAL);
        printLeadSpace(78);
        com.writeSentenceUART(UNICODETAPEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }

    // Ligne 19
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(26);
    com.writeSentenceUART(UNICODEBOXVERTICAL);
    printLeadSpace(10);
    com.writeSentenceUART(UNICODETAPEBOTTOMLEFT);
    for (int i = 0; i < 78; i++)
    {
        com.writeSentenceUART(UNICODETAPEHORIZONTAL);
    }
    com.writeSentenceUART(UNICODETAPEBOTTOMRIGHT);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Lignes 20-22
    for (int i = 0; i < 3; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(3);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(26);
        com.writeSentenceUART(UNICODEBOXVERTICAL);
        printLeadSpace(93);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }

    // Ligne 23
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    printLeadSpace(3);
    com.writeSentenceUART(UNICODEBOXBOTTOMLEFT);
    for (int i = 0; i < 26; i++)
    {
        com.writeSentenceUART(UNICODEBOXHORIZONTAL);
    }
    com.writeSentenceUART(UNICODEBOXBOTTOMRIGHT);
    printLeadSpace(93);
    com.writeSentenceUART(UNICODETABLEVERTICAL);
    com.writeSentenceUART(ENTER);

    // Lignes 24-26
    for (int i = 0; i < 3; i++)
    {
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        printLeadSpace(124);
        com.writeSentenceUART(UNICODETABLEVERTICAL);
        com.writeSentenceUART(ENTER);
    }

    // Ligne 27
    com.writeSentenceUART(UNICODETABLEBOTTOMLEFT);
    for (int i = 0; i < 124; i++)
    {
        com.writeSentenceUART(UNICODETABLEHORIZONTAL);
    }
    com.writeSentenceUART(UNICODETABLEBOTTOMRIGHT);
    com.writeSentenceUART(ENTER);

    // ROBOT 1 UNIQUEMENT
    // Ligne 28

    com.writeSentenceUART("Produit par: atMegatron");
    com.writeSentenceUART(ENTER);

    com.writeSentenceUART(ENTER);
    com.writeSentenceUART("DONE");
}
