// Noms des auteurs : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
// Description du programme : La classe speaker sert à implémenter les différentes fonctionnalités du piezo.
// Identification Matérielle: - Broche B2 en mode sortie
//                            - Broche B3 en mode sortie
//                            Les broches B2 et B3 sont connecté respectivements aux bornes négatives et positives
//                            du piezo.

#define F_CPU 8000000
#include "speaker.hpp"

Speaker::Speaker()
{
    DDRB |= (1 << DDB3) | (1 << DDB1);
    OCR0A = 0;                              // pin b4
    TCCR0A |= (1 << COM0A0) | (1 << WGM01); // mode 2 p.103
    TCCR0B |= (1 << CS01);                  // prescalar 8 p.104
}

uint16_t Speaker::frequencyCalculator(uint8_t note)
{
    return (pow(2, ((note - 69) / 12))) * 440;
}

uint16_t Speaker::compareValueCalculator(uint16_t frequency)
{
    return 1 / (frequency / ((double)F_CPU / (2 * PRESCALAR))) - 1;
}

void Speaker::setSound(uint8_t note)
{
    if ((MINIMAL_NOTE > note) or (MAXIMAL_NOTE < note))
    {
        OCR0A = 0;
        return;
    }
    else
    {
        uint16_t frequency = frequencyCalculator(note);
        OCR0A = compareValueCalculator(frequency);
    }
}

void Speaker::setSoundCustom(uint8_t note)
{
    uint16_t frequency = frequencyCalculator(note);
    OCR0A = compareValueCalculator(frequency);
}

void Speaker::stopSound()
{
    OCR0A = 0;
    return;
}

void Speaker::waitMode()
{
    for (int i = 0; i < WAIT_MODE_SOUND_LOOP; i++)
    {
        setSound(ACUTE_SOUND);
        _delay_ms(SOUND_DELAY_MS);
        stopSound();
        _delay_ms(SOUND_DELAY_MS);
    }
}
