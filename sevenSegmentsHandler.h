/**
 * @file sevenSegmentsHandler.h
 * @author Fabio Henrique and Guilherme Henriques
 * @brief Handle with Seven Segment Display
 * @date 2026-09-17
 */

#ifndef SEVEN_SEGMENTS_HANDLER_H
#define SEVEN_SEGMENTS_HANDLER_H
#include "gpioHandler.h"

/**
 * @brief Enum to set the numbers by the activation of the segments in display
 * @details Each number has some segments to turn on/off, this enum represents which segments needs to be on/off
 */
enum{
    ZERO = 0b1111110,
    ONE = 0b0110000,
    TWO = 0b1101101,
    THREE = 0b1111001,
    FOUR = 0b0110001,
    FIVE = 0b1011011,
    SIX = 0b1011111,
    SEVEN = 0b1000110,
    EIGHT = 0b1111111,
    NINE = 0b1111011,
    HEX_A = 0b1110111,
    HEX_B = 0b0011111,
    HEX_C = 0b1001110,
    HEX_D = 0b0111101,
    HEX_E = 0b1001111,
    HEX_F = 0b1000111,
};

/**
 * @brief Write a number in seven segments display
 * 
 * @param pins List of pins to be written
 * @param number Number to write
 */
void writeInDisplay(Pin* pins, uint8_t number);

/**
 * @brief Set some pins preconfigured in GPIO port C
 * 
 * @param pins List of pins to be configured
 */
void startDisplayPins(Pin *pins);

#endif