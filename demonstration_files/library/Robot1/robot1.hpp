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
#include "Led/Led.h"
#include "MemoryAndComm/can.h"
#include "navigation/navigation.h"
#include "infrarouge/IRRecieve.h"
#include "Speaker/speaker.hpp"
#include "Timer/Timer.h"
#include "cartographie/map.h"
#include "ButtonInterrupt/ButtonInterrupt.hpp"
#include "MemoryAndComm/communication.h"
#include "cartographie/map.h"
#include "constanteR1.h"

// TODO: finir entete pour les deux fichiers
// TODO: update les include

class Robot1 : virtual public can, virtual public Navigation
{
public:
    // RobotUn(Register mode, Register port, Port pinGreen, Port pinRed) : LED(mode, port, pinGreen, pinRed){};
    Robot1()
    {
        timer_.init(Prescaler::P256, Mode::CTC);
        timer_.setCompareValueA(3125);
        nav_.setPwmConstants(0.9, 1);
    }
    uint8_t getSensorValue();
    void sensorCalibration();
    uint8_t computeAverage(uint8_t arr[]);
    void setTurningTime(volatile uint8_t &delayCounter);
    void setTurningDelay(volatile uint8_t delayCounter);
    uint8_t getDistance();
    void moveToMiddle();
    void findOpeningMidlle();
    void findOpeningTurningDelay();
    void turnToOpeningMiddle();
    void setBoxPosition();

    Speaker speaker_;
    Timer1 timer_;
    LED led_;
    ButtonInterrupt button_ = ButtonInterrupt(EdgeType::ANY, InterruptionType::INT0_);
    Navigation nav_ = Navigation(RIGHT_WHEEL_BOOST, LEFT_WHEEL_BOOST);
    IRRecieve receiveIR;
    Map map;
    BoxPosition position = BoxPosition::Right;
    bool facingWall = false;
    uint8_t turningTime;
    State robotState = State::WAIT_MODE;

private:
    const uint8_t ONE_BITSHIFT = 1;
    const uint8_t TWO_BITSHIFTS = 2;
    bool turnedTowardsWall = false;
    uint8_t sensorValues_[15];
    uint8_t wallDistance_ = 45;
    uint8_t openingMaximalDistance_ = 25;
    uint8_t closeRangeValue_;
    uint8_t farRangeValue_;
    double RIGHT_WHEEL_BOOST = 0.85;
    double LEFT_WHEEL_BOOST = 1.0;
    uint8_t turningDelay_;
};
