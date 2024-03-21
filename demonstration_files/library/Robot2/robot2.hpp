#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Led/Led.h"
#include "navigation/navigation.h"
#include "infrarouge/IRSend.h"
#include "Timer/Timer.h"
#include "ButtonInterrupt/ButtonInterrupt.hpp"
#include "Speaker/speaker.hpp"
#include "MemoryAndComm/communication.h"
#include "cartographie/map.h"
#include "Robot2/constanteR2.h"

class Robot2
{
public:
    Robot2();

    ScanRoutine getState();
    void setState(ScanRoutine newState);
    void setSpeedRobotValue(uint8_t timerCounter);
    void setAdvanceForTurnDelay();
    void updateSensorValues();
    void followLine(uint8_t isBackward);
    void advanceForTurn(uint8_t direction);
    void turn90ToCenter(Direction direction);
    void goBackToreadLine();
    void adjustToGrandFinale();
    void adjustCenter(Direction direction);

    Timer1 timer_;
    LED led_ = LED(&DDRC, &PORTC, PC2, PC3);
    Navigation nav_ = Navigation(RIGHT_WHEEL_BOOST_R2, LEFT_WHEEL_BOOST_R2);
    IRSend sendIR;
    ButtonInterrupt buttonIR_ = ButtonInterrupt(EdgeType::ANY, InterruptionType::INT0_);
    ButtonInterrupt buttonRS232_ = ButtonInterrupt(EdgeType::ANY, InterruptionType::INT1_);
    Speaker speaker_ = Speaker();
    Communication comm_ = Communication();
    Map map;

    // Varibales du suiveur de ligne
    uint8_t left;
    uint8_t leftCenter;
    uint8_t center;
    uint8_t rightCenter;
    uint8_t right;

    uint8_t delayForTurn90;
    uint8_t advanceForTurnDelayMs;
    uint8_t cornerCounter = 0;
    uint8_t measurments[MAX_MEASUREMENTS_TO_STORE] = {0};
    uint8_t totalSideDistances[2] = {0};
    uint8_t totalDistanceIndex = 0;
    uint8_t measurementPtr = 0;
    uint8_t robotSpeed;
    float sixInchTapeDelay = SIX_INCH_TAPE_MM / robotSpeed;
    float eightInchTapeDelay = EIGHT_INCH_TAPE_MM / robotSpeed;

private:
    ScanRoutine stateScan;
};