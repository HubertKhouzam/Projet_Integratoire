/*
Auteur       : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Description  : Définition de la classe qui à comme fonction de gérer toutes les méthodes qui
               utilisent le protocle de communication RS232.

Branchements : 1 Branchement au total : - Sortie : Cavalier sur DbgEN

*/
#pragma once
#include <avr/io.h>
#include <util/delay.h>

class Communication
{
public:
    Communication();

    void writeValueUART(uint8_t value);
    void writeValueUART(uint16_t value);

    void writeSentenceUART(char *sentence);

    uint8_t readValueUART();
    char *readSentenceUART(uint8_t sizeOfSentence);
    void debugPrint(char *sentence);
};
