#include <avr/io.h>

#ifndef CONSTANTE_NAV_H
#define CONsTANTE_NAV_H

enum class Direction
{
    LEFT,
    RIGHT
};
enum class BoxPosition
{
    Left,
    Right
};

const uint8_t FORWARD = 0;
const uint8_t BACKWARD = 1;

const uint8_t MINIMUM_PWM = 20;
const uint8_t MAXIMUM_PWM_RIGHT = 90;
const uint8_t MAXIMUM_PWM_LEFT = 95;
const uint8_t MAXIMUM_PWM_UINT8_T = 255;

const uint8_t NULL_SPEED = 0;
const uint8_t HUNDRED_SPEED = 100;
const uint8_t SEVENTY_FIVE_SPEED = 75;

const uint8_t DELAY_BOOST_ADVENCE_MS = 150;
const uint8_t DELAY_BOOST_TURN_MS = 250;
const uint8_t DELAY100_MS = 100;
const uint16_t DELAY800_MS = 800;
#endif