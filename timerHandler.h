/**
 * @file timerHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with temporization functions
 * @date 2026-09-21
 */
#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H


static uint8_t isInitiated = 0;
/**
 * @brief Initiate the timer configs
 */
void timerInit(void);

/**
 * @brief Miliseconds delay
 *
 * @param ms miliseconds to be delayed
 */
void delay(uint32_t ms);

/**
 * @brief Microseconds delay
 *
 * @param microSeconds microseconds to be delayed
 */
void microDelay(uint32_t microSeconds);