#include <avr/io.h>

#ifndef CONSTANTE_R2_H
#define CONsTANTE_R2_H
// Bouton
// Navigation

// Robot1

// Robot2
enum class ScanRoutine
{
    CALIBRATION_LINE,
    CALIBRATION_TURN,
    FOLLOW_LINE,
    SIDE_LINE,
    CORNER_OR_TAPE,
    IDENTIFY_TAPE,
    SCAN_TAPE,
    WAIT_MODE,
    TRANSMIT_IR,
    TRANSMIT_RS232,
};

// Spécificité du robot
const double RIGHT_WHEEL_BOOST_R2 = 1.0;
const double LEFT_WHEEL_BOOST_R2 = 1.0;

// Constante pour Suivi de ligne
const uint8_t TURNING_SPEED_90 = 35;
const uint8_t HIGHT_ADJUST_SPEED = 38;
const uint8_t MID_ADJUST_SPEED = 40;
const uint8_t LIGHT_ADJUST_SPEED = 43;
const uint8_t BASIC_SPEED = 50;
const uint8_t MAX_FOWARD_FOLLOW_LINE = 60;
const uint8_t BACKWARD_ADJSUT_SPEED_70 = 60;
const uint8_t BACKWARD_ADJUST_SPEED_100 = 90;
const uint8_t TURN_SPEED_FINAL = 40;
const uint8_t BACKWARD_SPEED_FINAL = 45;

// Delay
const uint8_t DEBOUNCE_DELAY = 30;
const uint8_t HUNDRED_MS_DELAY = 100;
const uint16_t PASS_LINE_DELAY = 350;
const uint16_t ONE_SECOND_DELAY = 1000;
const uint16_t TWO_SECOND_DELAY = 2000;
const uint16_t NULL_SPEED_DELAY = 750;

// distances
const uint16_t SENSOR_TO_WHEELS_DISTANCE_MM = 85;
const uint16_t SENSOR_TO_CORNER_DISTANCE_MM = 241;
const uint16_t EIGHT_INCH_TAPE_MM = 216;
const uint16_t SIX_INCH_TAPE_MM = 165;

// Constante pour la classe
const uint8_t MAX_TAPE = 6;
const uint8_t MAX_MEASUREMENTS_TO_STORE = 3 * MAX_TAPE;
const uint8_t NULL_TIMER_COUNTER = 0;
#endif