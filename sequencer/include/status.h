/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef STATUS_H
#define STATUS_H

#include <pico/time.h>

#define PARACHUTE_DEPLOY_TIME_MS 50000

enum flight_stages { PRE_FLIGHT, READY, FLYING, GLIDING, LANDED };

typedef struct flight_status {
	enum flight_stages current_stage;
	absolute_time_t takeoff_time;
	absolute_time_t t1;
	absolute_time_t t2;
} flight_status_t;

void init_flight_status(flight_status_t &status);

static inline int get_parachute_deploy_time(void)
{
	return PARACHUTE_DEPLOY_TIME_MS;
}

static inline int get_t1(void)
{
	return make_timeout_time_ms(0.8 * get_parachute_deploy_time());
}

static inline int get_t2(void)
{
	return make_timeout_time_ms(1.2 * get_parachute_deploy_time());
}


#endif /* STATUS_H */
