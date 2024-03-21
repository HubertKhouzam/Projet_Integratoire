/*
Auteurs       : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
Collaboration : Olivier Thabet 2294559

Description  : Définition de la classe qui à comme fonction de gérer la récecption de l'information
par infrarouge

Branchements : 3 Branchements au total : - Sortie : Broche Vcc du capteur infrarouge sur Vcc
                                         - Sortie : Broche Gnd du capteur infrarouge sur Gnd
                                         - Sortie : Broche V0 du capteur infrarouge sur A1

Documentation capteur : https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/1028/PNA4602M_Rev_Nov_2011.pdf
*/

#pragma once
#include <avr/io.h>
#include "../MemoryAndComm/communication.h"
#include "../MemoryAndComm/can.h"

class IRRecieve
{
public:
    IRRecieve();
    uint8_t recieveData();
    void calculationCrc();
    void verifyStart();
    bool getStart();
    void recieveByte(uint8_t *array);
    void recieveTapeLength();
    void recieveTransmission();
    uint8_t convertByteToNum(uint8_t *byte);
    void setRecieveCRC();
    uint8_t convertByteToNum16(uint8_t *byte);

    uint8_t transmission_[18] = {0};
    uint8_t tapeLength_[2] = {0};
    uint16_t crcCalculated_ = 0;
    uint16_t crcRecieved_ = 0;

private:
    Communication com;
    bool recievedStart_ = false;
    volatile bool active_;
    int counter_ = 0;
    uint16_t MSNum_;
    uint16_t LSNum_;
};