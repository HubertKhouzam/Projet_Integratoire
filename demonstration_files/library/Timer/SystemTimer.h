/*
Auteurs     : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Date        : 06 mars 2024

Description : Définition de la classe SystemTimer. Elle sert à compter en laissant passer du temps,
              et permet d'instancier des minuteries à usage unique
*/

#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include <avr/io.h>

/*On ne peut utiliser qu'un timer à la fois*/

class SystemTimer
{   
public:
    SystemTimer();
    void start();
    void stop();
    void reset();
    uint32_t hasElapsed();
    static void increment();

    static const uint16_t TIME_MS_FOR_ONE_COUNT = 100;
    static const uint16_t CYCLE_FOR_OCR1A = 3125; 
    

private:
    static void initialize();
    static uint16_t get();

    static volatile uint16_t counter_;
    static bool isInitialized_;

    uint16_t m_start;
    uint16_t m_stop;
    
};

#endif