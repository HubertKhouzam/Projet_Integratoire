// Noms de l'auteur : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
// Description du programme : La classe Navigation a été élaborée pour superviser les déplacements du robot.
//                            Elle tire parti du module de modulation de largeur d'impulsion (PWM) associé au
//                            Timer2 du microcontrôleur ATMEGA32 afin de réguler la vitesse des moteurs du robot,
//                            permettant ainsi le contrôle de sa direction et de ses mouvements. Cette classe propose
//                            des méthodes permettant de définir la vitesse générale du robot, la vitesse du moteur
//                            droit, la vitesse du moteur gauche, d'établir des mouvements spécifiques en
//                            fonction d'angles préétablis et la direction de mouvement du robot.
// Identification Matérielle: - Broche D4 en mode sortie
//                            - Broche D5 en mode sortie
//                            - Broche D6 en mode sortie
//                            - Broche D7 en mode sortie
//                            La broche D4 est connecté à la broche D du moteur gauche.
//                            La broche D5 est connecté à la broche D du moteur droit.
//                            La broche D6 est connecté à la broche E du moteur gauche.
//                            La broche D7 est connecté à la broche E du moteur droit.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

// #include "../libR1/MemoryAndComm/can.h"
// #include "../libR1/Speaker/features.cpp"
// #include "../libR1/MemoryAndComm/communication.h"
#include "robot1.hpp"

// TODO: finir entete pour les deux fichiers

// TODO: opérations arithméthiques
// TODO: led/button interrupt/ timer
// TODO: calibration des tournants

uint8_t Robot1::getSensorValue()
{
    can distSencor;
    uint8_t sensorValue = 0;
    while (sensorValue == 0)
    {
        sensorValue = (distSencor.lecture(0) >> TWO_BITSHIFTS);
    }
    return sensorValue;
}

void Robot1::sensorCalibration()
{
    uint8_t buffer = 0;
    Communication comm;
    while (true)
    {
        uint8_t frontWallDistance = getDistance();
        comm.writeValueUART(frontWallDistance);
        comm.writeValueUART(buffer);
        comm.writeValueUART(buffer);
        comm.writeValueUART(buffer);
    }
}
uint8_t Robot1::computeAverage(uint8_t arr[])
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 14 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements
                uint8_t temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    uint16_t sum = 0;
    for (int i = 5; i < 10; i++)
    {
        sum += arr[i];
    }

    uint16_t somme = sum;
    uint8_t distance = 0;
    for (uint8_t i = 0; 5 * i <= sum; i++)
    {
        somme -= 5;
        distance = i;
    }
    return distance;
}

void Robot1::setTurningTime(volatile uint8_t &delayCounter)
{
    turningTime = delayCounter;
    delayCounter = 0;
    timer_.start();
}
void Robot1::setTurningDelay(volatile uint8_t delayCounter)
{
    turningDelay_ = delayCounter;
}

uint8_t Robot1::getDistance()
{
    for (int i = 0; i < 15; i++)
    {
        sensorValues_[i] = getSensorValue();
    }
    uint8_t distance = computeAverage(sensorValues_);
    return distance;
}

void Robot1::moveToMiddle()
{
    speaker_.wakeUp();
    bool notArrived = true;
    nav_.setDirection(0);
    nav_.setSpeed(70);
    closeRangeValue_ = wallDistance_ + 1;
    farRangeValue_ = wallDistance_ - 1;
    uint8_t frontWallDistance = getSensorValue();
    if (frontWallDistance > wallDistance_)
    {
        nav_.setDirection(1);
        nav_.boostAdvance(1);
        nav_.setSpeed(45);
        wallDistance_ += 2;
        facingWall = true;
    }
    else
    {
        nav_.boostAdvance(0);
    }
    while (notArrived)
    {
        if ((frontWallDistance < closeRangeValue_ + 8) && (frontWallDistance > farRangeValue_ - 8))
            nav_.setSpeed(40);
        while ((frontWallDistance < closeRangeValue_) && (frontWallDistance > farRangeValue_))
        {
            notArrived = false;
            break;
        }
        frontWallDistance = getDistance();
    }

    nav_.setSpeed(0);
    _delay_ms(700);
    timer_.start();
}

void Robot1::findOpeningMidlle()
{
    nav_.setDirection(0);
    nav_.boostTurn(Direction::RIGHT);
    nav_.turn(Direction::RIGHT, 40);
    while (wallDistance_ > openingMaximalDistance_)
    {
        wallDistance_ = getDistance();
    }
    timer_.stop();
}

void Robot1::findOpeningTurningDelay()
{
    led_.setRed();
    wallDistance_ = getDistance();
    while (wallDistance_ < openingMaximalDistance_)
    {
        wallDistance_ = getDistance();
    }
    nav_.setSpeed(0);
    timer_.stop();
}

void Robot1::turnToOpeningMiddle()
{
    led_.setGreen();
    nav_.setDirection(0);
    nav_.boostTurn(Direction::LEFT);
    _delay_ms(400);
    nav_.turn(Direction::LEFT, 40);
    for (uint8_t i = 0; i < (turningDelay_); i++)
    {
        _delay_ms(100);
    }
    nav_.setSpeed(0);
    _delay_ms(750);
}

void Robot1::setBoxPosition()
{
    if (((facingWall == false) && (turningTime > 20)) || ((facingWall == true) && (turningTime < 20)))
    {
        position = BoxPosition::Left;
    }
    sei();
}

// void Robot1::irMode()
// {
//     led_.setOff();
//     //ir receive...
// }
// void Robot1::rs232Mode()
// {
//     led_.setGreen();

// }
