/**
 * @file ultrassonicSensorHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with the UltraSonic sensor HCSR04
 * @date 2026-09-21
 */

#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "gpioHandler.h"
#include "timerHandler.h"

/**
 * @brief Get the sensors free distance
 *
 * @param pinEmitter A pin to emit the signal to the ultrasonic sensor
 * @param pinReceiver A pin to receive the signal of the ultrasonic sensor
 * @return uint32_t The free distance in cm
 */
uint32_t getDistance(Pin* pinEmitter, Pin* pinReceiver);