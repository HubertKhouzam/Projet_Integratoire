/*
Auteur       : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Description  : Implémentation de la classe qui à comme fonction de gérer toutes les méthodes qui utilisent à
               le protocle de communication RS232 ainsi que la définition de la méthode de débogage.

Branchements : 1 Branchement au total : - Sortie : Cavalier sur DbgEN

*/

#include <avr/io.h>
#include <string.h>
#include "communication.h"
#include "debug.h"

Communication::Communication(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (3 << UCSZ00);
};

void Communication::writeValueUART(uint8_t value)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = value;
};

void Communication::writeValueUART(uint16_t value)
{
    char buffer[40];
    sprintf(buffer, "%d", value);
    writeSentenceUART(buffer);
};

void Communication::writeSentenceUART(char *sentence)
{
    uint8_t sizeOfSentence = strlen(sentence);

    for (int i = 0; i < sizeOfSentence; i++)
    {
        writeValueUART((uint8_t)sentence[i]);
    }
};

uint8_t Communication::readValueUART()
{
    while (!(UCSR0A & (1 << RXC0)))
        ;

    return UDR0;
}

char *Communication::readSentenceUART(uint8_t sizeOfSentence)
{

    char *sentenceToRead = "";
    for (int i = 0; i < sizeOfSentence; i++)
    {
        sentenceToRead += readValueUART();
    }
    return sentenceToRead;
}

void Communication::debugPrint(char *sentence)
{
    Communication com = Communication();
    com.writeSentenceUART(sentence);
}