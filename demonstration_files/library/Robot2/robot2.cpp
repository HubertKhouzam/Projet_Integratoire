#include "robot2.hpp"

Robot2::Robot2()
{
    DDRA &= ~((1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3) | (1 << DDA4));
    this->timer_.init(Prescaler::P256, Mode::CTC);
    this->timer_.setCompareValueA(3125);
}

void Robot2::updateSensorValues()
{
    left = PINA & (1 << PA0);
    leftCenter = PINA & (1 << PA1);
    center = PINA & (1 << PA2);
    rightCenter = PINA & (1 << PA3);
    right = PINA & (1 << PA4);
}

ScanRoutine Robot2::getState() { return stateScan; }
void Robot2::setState(ScanRoutine newState) { stateScan = newState; }

void Robot2::followLine(uint8_t isBackward)
{
    updateSensorValues();
    this->nav_.setDirection(isBackward);
    if (leftCenter && center)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(LIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BASIC_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BACKWARD_ADJSUT_SPEED_70);
        }
    }
    else if (left && leftCenter)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BASIC_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BACKWARD_ADJUST_SPEED_100);
        }
    }
    else if (center && rightCenter)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(LIGHT_ADJUST_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BACKWARD_ADJSUT_SPEED_70);
        }
    }
    else if (rightCenter && right)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(HIGHT_ADJUST_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BACKWARD_ADJUST_SPEED_100);
        }
    }
    else if (left)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(NULL_SPEED);
            this->nav_.setSpeedRight(MAX_FOWARD_FOLLOW_LINE);
        }
        else
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(NULL_SPEED);
        }
    }
    else if (leftCenter)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(HIGHT_ADJUST_SPEED);
            this->nav_.setSpeedRight(BASIC_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(MID_ADJUST_SPEED);
            this->nav_.setSpeedRight(BASIC_SPEED);
        }
    }
    else if (center || (!left && !right && !center && !rightCenter && !leftCenter))
    {
        this->nav_.setSpeed(BASIC_SPEED);
    }
    else if (rightCenter)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(LIGHT_ADJUST_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(MID_ADJUST_SPEED);
        }
    }
    else if (right)
    {
        if (!isBackward)
        {
            this->nav_.setSpeedLeft(BASIC_SPEED);
            this->nav_.setSpeedRight(NULL_SPEED);
        }
        else
        {
            this->nav_.setSpeedLeft(NULL_SPEED);
            this->nav_.setSpeedRight(HIGHT_ADJUST_SPEED);
        }
    }
}

void Robot2::setSpeedRobotValue(uint8_t timerCounter)
{
    robotSpeed = SENSOR_TO_CORNER_DISTANCE_MM / timerCounter;
}

void Robot2::setAdvanceForTurnDelay()
{
    advanceForTurnDelayMs = SENSOR_TO_WHEELS_DISTANCE_MM / robotSpeed;
}

// TODO:assurer de définir la fréquence dans tout les documents qui utilise delay
void Robot2::advanceForTurn(uint8_t direction)
{
    this->nav_.setSpeed(NULL_SPEED);
    _delay_ms(750);
    this->nav_.boostAdvance(direction);
    for (int i = 0; i < (advanceForTurnDelayMs - 2); i++)
    {
        followLine(direction);
        _delay_ms(HUNDRED_MS_DELAY);
    }
    this->nav_.setSpeed(NULL_SPEED);
}

void Robot2::turn90ToCenter(Direction direction)
{
    this->nav_.boostTurn(direction);
    updateSensorValues();
    this->nav_.turn(direction, TURNING_SPEED_90);
    while (left || right || center || rightCenter || leftCenter)
    {
        updateSensorValues();
    }
    if (direction == Direction::RIGHT)
    {
        while (!right)
        {
            updateSensorValues();
        }
    }
    else
    {
        while (!leftCenter)
        {
            updateSensorValues();
        }
    }
    this->nav_.setSpeed(NULL_SPEED);
    this->nav_.setDirection(FORWARD);
}

void Robot2::goBackToreadLine()
{
    this->timer_.start();
    while (left || right || center || rightCenter || leftCenter)
    {
        followLine(FORWARD);
        updateSensorValues();
    }
    this->timer_.stop();
    advanceForTurn(BACKWARD);
    this->nav_.setSpeed(NULL_SPEED);
    _delay_ms(NULL_SPEED_DELAY);
    this->nav_.setDirection(FORWARD);
}

void Robot2::adjustCenter(Direction direction)
{
    _delay_ms(1000);
    updateSensorValues();
    if (left)
    {
        if (direction == Direction::LEFT)
        {
            nav_.boostTurn(Direction::LEFT);
        }
        else
        {
            nav_.boostTurn(Direction::LEFT);
        }
    }
    else if (right)
    {
        if (direction == Direction::LEFT)
        {
            nav_.boostTurn(Direction::RIGHT);
        }
        else
        {
            nav_.boostTurn(Direction::RIGHT);
        }
    }
    else if (!(left || right || center || rightCenter || leftCenter))
    {
        if (direction == Direction::LEFT)
        {
            nav_.boostTurn(Direction::RIGHT);
        }
        else
        {
            nav_.boostTurn(Direction::LEFT);
        }
    }
}

void Robot2::adjustToGrandFinale()
{
    nav_.setSpeed(NULL_SPEED);
    _delay_ms(NULL_SPEED_DELAY);
    nav_.boostAdvance(FORWARD);
    advanceForTurn(FORWARD);
    while (!left)
    {
        nav_.turn(Direction::LEFT, TURN_SPEED_FINAL);
        updateSensorValues();
    }
    nav_.setSpeed(NULL_SPEED);
    nav_.setDirection(BACKWARD);
    nav_.setSpeed(BACKWARD_SPEED_FINAL);
    _delay_ms(350);
    while (!(left || right || center || rightCenter || leftCenter))
    {
        updateSensorValues();
    }
    nav_.setSpeed(NULL_SPEED);
    _delay_ms(350);
    followLine(FORWARD);
    while (left || right || center || rightCenter || leftCenter)
    {
        followLine(FORWARD);
        updateSensorValues();
    }
    nav_.boostAdvance(BACKWARD);
    nav_.setSpeed(NULL_SPEED);
}
