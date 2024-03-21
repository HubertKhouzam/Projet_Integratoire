// Noms des auteurs : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
// Description du programme : La classe speaker sert à implémenter les différentes fonctionnalités du piezo.
// Identification Matérielle: - Broche B2 en mode sortie
//                            - Broche B3 en mode sortie
//                            Les broches B2 et B3 sont connecté respectivements aux bornes négatives et positives
//                            du piezo.

#include <avr/io.h>
#include <util/delay.h>
#include "constanteSPEAKER.h"

#pragma once
class Speaker
{
public:
    Speaker();
    uint16_t frequencyCalculator(uint8_t note);
    uint16_t compareValueCalculator(uint16_t frequency);
    void setSound(uint8_t note);
    void setSoundCustom(uint8_t note);
    void stopSound();
    void wakeUp();
    void waitMode();
};