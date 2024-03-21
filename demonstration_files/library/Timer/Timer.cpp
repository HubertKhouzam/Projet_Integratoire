/*
Auteurs     : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Date        : 06 mars 2024

Description : Implémentation de la classe Timer
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

void Timer1::init(Prescaler prescaler, Mode mode)
{
    m_mode = mode;
    m_prescaler = prescaler;
}

void Timer1::setMode(Mode mode)
{
    m_mode = mode;
    TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
    TCCR1B &= ~((1 << WGM12) | (1 << WGM13));

    switch (mode)
    {
    case Mode::NORMAL:
        break;

    case Mode::CTC:
        TCCR1B |= (1 << WGM12);
        break;
    }
}

void Timer1::setPrescaler(Prescaler prescaler)
{
    m_prescaler = prescaler;

    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));

    switch (prescaler)
    {
    case Prescaler::P1:
        TCCR1B |= (1 << CS10);
        break;

    case Prescaler::P8:
        TCCR1B |= (1 << CS11);
        break;

    case Prescaler::P64:
        TCCR1B |= (1 << CS10) | (1 << CS11);
        break;

    case Prescaler::P256:
        TCCR1B |= (1 << CS12);
        break;

    case Prescaler::P1024:
        TCCR1B |= (1 << CS10) | (1 << CS12);
        break;

    case Prescaler::NONE:
        break;
    }
}

void Timer1::setCompareValueA(uint16_t compareValue)
{
    OCR1A = compareValue;
    TIMSK1 |= (1 << OCIE1A);
}

void Timer1::setCompareValueB(uint16_t compareValue)
{
    OCR1B = compareValue;
    TIMSK1 |= (1 << OCIE1B);
}
//TODO: pt erreur initialise deux valeurs de comparaisons
void Timer1::setCompareValueOff()
{
    TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));
}


//TODO: pt erreur ne réinitialise pas les interruptions
void Timer1::start()
{
    cli();
    sei();
    setMode(m_mode);
    setPrescaler(m_prescaler);

}

void Timer1::stop()
{
    cli();
}