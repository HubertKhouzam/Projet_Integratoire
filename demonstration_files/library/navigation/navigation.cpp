// Noms de l'auteur : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam
// Description du programme : La classe Navigation a été élaborée pour superviser les déplacements du robot.
//                            Elle tire parti du module de modulation de largeur d'impulsion (PWM) associé au
//                            Timer2 du microcontrôleur ATMEGA32 afin de réguler la vitesse des moteurs du robot,
//                            permettant ainsi le contrôle de sa direction et de ses mouvements. Cette classe propose
//                            des méthodes permettant de définir la vitesse générale du robot, la vitesse du moteur
//                            droit, la vitesse du moteur gauche, d'établir des mouvements spécifiques en
//                            fonction d'angles préétablis et la direction de mouvement du robot.
// Identification Matérielle: - Broche C6 en mode sortie
//                            - Broche C7 en mode sortie
//                            - Broche D6 en mode sortie
//                            - Broche D7 en mode sortie
//                            La broche C6 est connecté à la broche D du moteur gauche.
//                            La broche C7 est connecté à la broche D du moteur droit.
//                            La broche D6 est connecté à la broche E du moteur gauche.
//                            La broche D7 est connecté à la broche E du moteur droit.

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "navigation.h"
#include <string.h>

Navigation::Navigation(double rightWheelConstant, double leftWheelConstant)
{
    RIGHT_PWM_AMPLIFICATOR = rightWheelConstant;
    LEFT_PWM_AMPLIFICATOR = leftWheelConstant;
    DDRC |= (1 << DDC6) | (1 << DDC7);
    DDRD |= (1 << DDD6) | (1 << DDD7);
    OCR2A = 0;
    OCR2B = 0;
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B |= (1 << CS20);
}

uint8_t Navigation::getPwm()
{
    return ((OCR2A * HUNDRED_SPEED) / MAXIMUM_PWM_UINT8_T);
}

void Navigation::setPwmConstants(double constRight, double constLeft)
{
    RIGHT_PWM_AMPLIFICATOR = constRight;
    LEFT_PWM_AMPLIFICATOR = constLeft;
}

void Navigation::setSpeed(uint8_t pwm)
{
    int newPwm = pwm;
    if ((pwm <= MINIMUM_PWM) && (pwm > 0))
    {
        OCR2A = (MAXIMUM_PWM_RIGHT * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
        OCR2B = (MAXIMUM_PWM_LEFT * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
        _delay_ms(DELAY100_MS);
        newPwm = MINIMUM_PWM;
    }
    OCR2A = (RIGHT_PWM_AMPLIFICATOR * newPwm * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
    OCR2B = (LEFT_PWM_AMPLIFICATOR * newPwm * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
}

void Navigation::setSpeedRight(uint8_t pwm)
{
    int newPwm = pwm;
    if ((pwm <= MINIMUM_PWM) && (pwm > 0))
    {
        OCR2A = (MAXIMUM_PWM_RIGHT * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
        _delay_ms(DELAY800_MS);
    }
    OCR2A = (newPwm * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
}

void Navigation::setSpeedLeft(uint8_t pwm)
{
    int newPwm = pwm;
    if ((pwm <= MINIMUM_PWM) && (pwm > 0))
    {
        OCR2B = (MAXIMUM_PWM_LEFT * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
        _delay_ms(DELAY800_MS);
        newPwm = MINIMUM_PWM;
    }
    OCR2B = (LEFT_PWM_AMPLIFICATOR*newPwm * MAXIMUM_PWM_UINT8_T) / HUNDRED_SPEED;
}

void Navigation::setDirection(uint8_t directionAngle)
{

    switch (directionAngle)
    {
    case 1:
        PORTC |= (1 << DDC6) | (1 << DDC7);
        break;

    case 0:
        PORTC &= ~(1 << DDC6) & ~(1 << DDC7);
        break;
    }
}

void Navigation::boostAdvance(uint8_t advanceDirection){
    setDirection(advanceDirection);
    setSpeed(HUNDRED_SPEED);
    _delay_ms(DELAY_BOOST_ADVENCE_MS);

}
void Navigation::boostTurn(Direction direction)
{
    if (direction == Direction::RIGHT){
        PORTC |= (1 << DDC7);
    }
    else if (direction == Direction::LEFT){
        PORTC |= (1 << DDC6);
    }
    setSpeed(SEVENTY_FIVE_SPEED);
    _delay_ms(DELAY_BOOST_TURN_MS);
    
}

void Navigation::turn(Direction direction, uint8_t pwm)
{
    if (direction == Direction::LEFT)
    {
        PORTC |= (1 << DDC6);
    }
    else
    {
        PORTC |= (1 << DDC7);
    }
    setSpeed(pwm);
}
