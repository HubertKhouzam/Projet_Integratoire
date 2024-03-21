/*
Auteurs     : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Date        : 06 mars 2024

Description : Implémentation de la classe SystemTimer
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SystemTimer.h"
#include "Timer.h"

volatile uint16_t SystemTimer::counter_ = 0;
bool SystemTimer::isInitialized_ = false;

SystemTimer::SystemTimer(){
    if (!isInitialized_)
    {
        initialize();
    }
}

void SystemTimer::initialize()
{
    Timer1 timer;
    timer.init();
    timer.setCompareValueA(CYCLE_FOR_OCR1A);
    timer.start();
    isInitialized_ = true;
}

/*À utiliser dans le ISR*/
void SystemTimer::increment() { counter_++; }

uint16_t SystemTimer::get(){ return counter_; }

void SystemTimer::start(){
    reset(); 
}
void SystemTimer::stop(){ 
    m_stop = get();
}
void SystemTimer::reset(){ 
    m_start = get(); 
}

uint32_t SystemTimer::hasElapsed()
{
    return (m_stop - m_start) * TIME_MS_FOR_ONE_COUNT;
}


