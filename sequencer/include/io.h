/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef IO_H
#define IO_H

#define LOOP_LOG_INTERVAL 100000

/*
 * Initialises the IO interface for the rocket.
 *
 * This turns on the power on indicator and sets the takeoff and parachute
 * deployed indicators to their default states.
 */
int init_io_interface(void);

/*
 * Turns on the takeoff indicator.
 *
 * This allows to know that the rocket as taken off (for testing and problem 
 * detection).
 */
int set_takeoff_signal(void);

/*
 * Turns on the parachute deployed indicator.
 *
 * This allows to know that the parachute should have been deployed.
 */
int set_parachute_deployed_signal(void);

/*
 * Displays msg to Serial output.
 *
 * If the same msg is displayed multiple times, it will only be displayed
 * every LOOP_LOG_INTERVAL call.
 * The same is meant in term of the pointer.
 */
void debug_log(const char *msg);

#endif /* IO_H */
