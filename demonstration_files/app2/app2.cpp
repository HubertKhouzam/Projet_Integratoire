#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Robot2/robot2.hpp"

volatile uint8_t timerCounter = NULL_TIMER_COUNTER;
volatile bool isIrPressed = false;
volatile bool isWhiteButtonPressed = false;
volatile bool startBlinkLed = false;

ISR(TIMER1_COMPA_vect)
{
    timerCounter++;
    // if(startBlinkLed){
    //     if(timerCounter % 2 == 0){
    //         PORTC &= ~(1 << PORTC2);
    //         PORTC |= (1 << PORTC3);
    //     }else{
    //         PORTB &= ~((1 << PORTC2) | (1 << PORTC3));
    //     }
    // }
}

ISR(INT0_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    isIrPressed = !isIrPressed;
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    isWhiteButtonPressed = !isWhiteButtonPressed;
    EIFR |= (1 << INTF1);
}

void executeScan(Robot2 &robot2)
{
    robot2.updateSensorValues();
    switch (robot2.getState())
    {
    case ScanRoutine::CALIBRATION_LINE:
        robot2.followLine(FORWARD);
        break;

    case ScanRoutine::CALIBRATION_TURN:
        // robot2.led_.setGreen();
        robot2.nav_.turn(Direction::RIGHT, 35);
        break;

    case ScanRoutine::FOLLOW_LINE:
        robot2.led_.setOff();
        robot2.followLine(FORWARD);
        break;

    case ScanRoutine::CORNER_OR_TAPE:
        robot2.advanceForTurn(FORWARD);
        break;

    case ScanRoutine::IDENTIFY_TAPE:
        break;

    case ScanRoutine::SCAN_TAPE:
        robot2.goBackToreadLine();
        break;

    case ScanRoutine::SIDE_LINE:
        robot2.followLine(FORWARD);
        break;

    case ScanRoutine::WAIT_MODE:
        robot2.led_.setRed();
        break;

    case ScanRoutine::TRANSMIT_IR:
        robot2.led_.setOff();
        _delay_ms(TWO_SECOND_DELAY);
        robot2.sendIR.sendArrayWithCRC(robot2.measurments, robot2.totalSideDistances);
        break;

    case ScanRoutine::TRANSMIT_RS232:
        // transmitRS232Mode();
        robot2.map.modifyAllLines(robot2.measurments, robot2.totalSideDistances);
        _delay_ms(5);
        robot2.map.read_map();
        break;
    }
}

void updateScan(Robot2 &robot2)
{
    robot2.updateSensorValues();
    switch (robot2.getState())
    {

    case ScanRoutine::CALIBRATION_LINE:
        if (robot2.right && robot2.rightCenter && robot2.center)
        {
            robot2.timer_.stop();
            robot2.nav_.setSpeed(NULL_SPEED);
            robot2.setSpeedRobotValue(timerCounter);
            robot2.setAdvanceForTurnDelay();
            robot2.advanceForTurn(FORWARD);
            timerCounter = NULL_TIMER_COUNTER;
            robot2.timer_.start();
            robot2.setState(ScanRoutine::CALIBRATION_TURN);
            robot2.nav_.boostTurn(Direction::RIGHT);
        }
        break;

    case ScanRoutine::CALIBRATION_TURN:
        if (robot2.right)
        {
            robot2.nav_.setSpeed(NULL_SPEED);
            robot2.timer_.stop();
            _delay_ms(NULL_SPEED_DELAY);
            robot2.cornerCounter++;
            robot2.delayForTurn90 = timerCounter;
            robot2.totalSideDistances[robot2.totalDistanceIndex] += (robot2.advanceForTurnDelayMs);
            timerCounter = NULL_TIMER_COUNTER;
            robot2.timer_.start();
            robot2.setState(ScanRoutine::FOLLOW_LINE);
        }
        break;

    case ScanRoutine::FOLLOW_LINE:
        if ((robot2.center && robot2.right) || (robot2.leftCenter && robot2.rightCenter))
        {
            robot2.timer_.stop();
            robot2.nav_.setSpeed(NULL_SPEED);
            robot2.totalSideDistances[robot2.totalDistanceIndex] += (timerCounter);
            timerCounter = NULL_TIMER_COUNTER;
            robot2.setState(ScanRoutine::CORNER_OR_TAPE);
        }
        break;
    case ScanRoutine::CORNER_OR_TAPE:
        if (!robot2.left && !robot2.right && !robot2.center && !robot2.rightCenter && !robot2.leftCenter)
        {
            robot2.cornerCounter++;
            robot2.nav_.boostAdvance(FORWARD);
            robot2.setState(ScanRoutine::SIDE_LINE);
        }
        else
        {
            robot2.setState(ScanRoutine::IDENTIFY_TAPE);
            robot2.totalSideDistances[robot2.totalDistanceIndex] += (robot2.advanceForTurnDelayMs);
            timerCounter = NULL_TIMER_COUNTER;
            robot2.timer_.start();
        }
        robot2.turn90ToCenter(Direction::RIGHT);
        robot2.timer_.stop();
        robot2.nav_.setSpeed(NULL_SPEED);
        _delay_ms(600);
        break;

    case ScanRoutine::IDENTIFY_TAPE:
        robot2.measurments[robot2.measurementPtr++] = robot2.totalSideDistances[robot2.totalDistanceIndex];
        if ((timerCounter - 4) > robot2.delayForTurn90)
        {
            robot2.led_.setRed();
            _delay_ms(NULL_SPEED_DELAY);
            robot2.turn90ToCenter(Direction::RIGHT);
            robot2.nav_.setSpeed(NULL_SPEED);
            _delay_ms(ONE_SECOND_DELAY);
            robot2.measurments[robot2.measurementPtr++] = 0;
            robot2.measurments[robot2.measurementPtr++] = robot2.totalDistanceIndex;
            timerCounter = NULL_TIMER_COUNTER;
            robot2.timer_.start();
            robot2.nav_.boostAdvance(FORWARD);
            robot2.setState(ScanRoutine::FOLLOW_LINE);
            robot2.led_.setGreen();
        }
        else
        {
            timerCounter = NULL_TIMER_COUNTER;
            robot2.setState(ScanRoutine::SCAN_TAPE);
        }

        break;

    case ScanRoutine::SIDE_LINE:

        if (robot2.center && robot2.rightCenter && robot2.right)
        {
            robot2.cornerCounter++;
            robot2.advanceForTurn(FORWARD);
            _delay_ms(NULL_SPEED_DELAY);
            robot2.turn90ToCenter(Direction::RIGHT);
            _delay_ms(NULL_SPEED_DELAY);
            robot2.totalDistanceIndex++;
            robot2.totalSideDistances[robot2.totalDistanceIndex] += (robot2.advanceForTurnDelayMs);
            robot2.setState(ScanRoutine::FOLLOW_LINE);
            robot2.timer_.start();
        }
        else if (robot2.center && robot2.left)
        {
            robot2.adjustToGrandFinale();
            robot2.setState(ScanRoutine::WAIT_MODE);
            sei();
        }
        break;

    case ScanRoutine::SCAN_TAPE:
        if (timerCounter > 10)
        {
            robot2.led_.setRed();
            _delay_ms(1500);
            robot2.led_.setGreen();
            robot2.measurments[robot2.measurementPtr++] = 2;
            robot2.measurments[robot2.measurementPtr++] = robot2.totalDistanceIndex;
            robot2.turn90ToCenter(Direction::LEFT);
            _delay_ms(NULL_SPEED_DELAY);
            robot2.nav_.boostAdvance(FORWARD);
            robot2.setState(ScanRoutine::FOLLOW_LINE);
            robot2.timer_.start();
            timerCounter = NULL_TIMER_COUNTER;
        }
        else
        {
            timerCounter = NULL_TIMER_COUNTER;
            robot2.led_.setGreen();
            _delay_ms(ONE_SECOND_DELAY);
            robot2.measurments[robot2.measurementPtr++] = 1;
            robot2.measurments[robot2.measurementPtr++] = robot2.totalDistanceIndex;
            robot2.turn90ToCenter(Direction::LEFT);
            _delay_ms(NULL_SPEED_DELAY);
            robot2.timer_.start();
            robot2.setState(ScanRoutine::FOLLOW_LINE);
            robot2.nav_.boostAdvance(FORWARD);
        }
        robot2.nav_.boostAdvance(FORWARD);
        break;

    case ScanRoutine::WAIT_MODE:
        if (isIrPressed)
        {
            robot2.speaker_.waitMode();
            robot2.setState(ScanRoutine::TRANSMIT_IR);
        }

        else if (isWhiteButtonPressed)
        {
            robot2.setState(ScanRoutine::TRANSMIT_RS232);
        }

        break;

    case ScanRoutine::TRANSMIT_IR:
    case ScanRoutine::TRANSMIT_RS232:

        robot2.setState(ScanRoutine::WAIT_MODE);
        break;
    }
}

int main()
{
    Robot2 robot2 = Robot2();
    robot2.setState(ScanRoutine::CALIBRATION_LINE);
    robot2.timer_.start();
    robot2.nav_.boostAdvance(FORWARD);
    while (true)
    {
        executeScan(robot2);
        updateScan(robot2);
        // robot2.nav_.boostAdvance(FORWARD);
    }
}