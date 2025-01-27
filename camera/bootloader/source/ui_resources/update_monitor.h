/*
 * Copyright 2023 NXP.
 * This software is owned or controlled by NXP and may only be used strictly in accordance with the
 * license terms that accompany it. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you
 * agree to comply with and are bound by, such license terms. If you do not agree to be bound by the
 * applicable license terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef UPDATE_MONITOR_H_
#define UPDATE_MONITOR_H_

#include "sln_update.h"

/**
 * @brief Handles the status events generated by update procedures
 *
 * @param stage
 * @param status
 */
void SLN_UpdateMonitor_Callback(updateStage stage, uint8_t status);

/**
 * @brief Handles the initialization of the monitor. Call this before any events are generated
 *
 */
void SLN_UpdateMonitor_Init();

#endif /* UPDATE_MONITOR_H_ */
