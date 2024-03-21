#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Robot1/robot1.hpp"

volatile uint8_t delayCounter = 0;
volatile bool isButtonPressed = false;
ISR(TIMER1_COMPA_vect)
{
    delayCounter++;
}
ISR(INT0_vect)
{
    isButtonPressed = !isButtonPressed;
    EIFR |= (1 << INTF0);
}

uint8_t one = 1;
uint8_t zero = 0;

void executeWaitMode(Robot1 &robot1)
{
    switch (robot1.robotState)
    {
    case State::WAIT_MODE:
        robot1.led_.setRed();
        while (!isButtonPressed)
        {
        }
        // isButtonPressed = !isButtonPressed;
        robot1.speaker_.waitMode();
        robot1.robotState = State::IR_MODE;
        break;
    case State::IR_MODE:
        robot1.led_.setOff();
        robot1.receiveIR.recieveTransmission();
        if (robot1.receiveIR.crcCalculated_ == robot1.receiveIR.crcRecieved_)
        {
            robot1.robotState = State::RS232_MODE;
        }
        else
        {
            robot1.speaker_.setSound(BASS_SOUND);
            _delay_ms(1000);
            robot1.speaker_.stopSound();
            robot1.robotState = State::WAIT_MODE;
        }
        break;
    case State::RS232_MODE:
        robot1.led_.setGreen();
        while (!isButtonPressed)
        {
        }
        robot1.map.setPosR1(robot1.map.evaluatePosition(robot1.facingWall, robot1.position));
        robot1.map.modifyAllLines(robot1.receiveIR.transmission_, robot1.receiveIR.tapeLength_);
        _delay_ms(5);
        robot1.map.read_map();
        // isButtonPressed = !isButtonPressed;
        break;
    }
}

int main()
{
    Robot1 sensor;

    sensor.moveToMiddle();
    sensor.findOpeningMidlle();
    sensor.setTurningTime(delayCounter);
    sensor.findOpeningTurningDelay();
    sensor.setTurningDelay(delayCounter);
    sensor.turnToOpeningMiddle();
    sensor.setBoxPosition();
    while (true)
    {
        executeWaitMode(sensor);
    }
    return 0;
}