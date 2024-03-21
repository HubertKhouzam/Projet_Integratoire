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
#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include "constanteNav.h"

class Navigation
{
public:
    Navigation(double rightWheelConstant = 1, double leftWheelConstant = 1);
    uint8_t getPwm();
    void setPwmConstants(double constRight, double constLeft);
    void setSpeed(uint8_t pwm);
    void setSpeedRight(uint8_t pwm);
    void setSpeedLeft(uint8_t pwm);
    void setDirection(uint8_t directionAngle);
    void boostAdvance(uint8_t advanceDirection);
    void boostTurn(Direction direction);
    void turn(Direction direction, uint8_t pwm);

private:
    double LEFT_PWM_AMPLIFICATOR;
    double RIGHT_PWM_AMPLIFICATOR;
};