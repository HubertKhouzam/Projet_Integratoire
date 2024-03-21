/*
Auteurs     : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Date        : 06 mars 2024

Description : Définition de la classe Timer. Elle sert à paramétrer le Timer 1 et
              sa valeur de comparaison sur OCR1A
*/

#include <avr/io.h>

#ifndef TIMER_H
#define TIMER_H

enum class Mode
{
        NORMAL,
        CTC,
};

enum class Prescaler
{
        P1,
        P8,
        P64,
        P256,
        P1024,
        NONE
};

class Timer1
{
public:
        void init(Prescaler prescaler = Prescaler::P256, Mode mode = Mode::CTC);

        void setMode(Mode mode);

        void setPrescaler(Prescaler prescaler);

        void setCompareValueA(uint16_t compareValue);

        void setCompareValueB(uint16_t compareValue);

        void setCompareValueOff();

        void start();

        void stop();

private:
        Prescaler m_prescaler;
        Mode m_mode;
};

#endif