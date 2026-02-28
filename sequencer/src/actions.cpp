/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <pico/time.h>

#include "actions.h"
#include "hardware.h"
#include "io.h"
#include "status.h"

int do_pre_flight_actions(flight_status_t &status)
{
	status.current_stage = READY;
	return 0;
}

int do_ready_actions(flight_status_t &status)
{
	// If the jack is connected we have not taken off
	if(jack_connected()){
		return 0;
	}
	
	status.takeoff_time = get_absolute_time();
	status.t1 = get_t1();
	status.t2 = get_t2();
	status.current_stage = FLYING;

	set_takeoff_signal();
	return 0;
}

int do_flying_actions(flight_status_t &status)
{
	// If we are before t1 return because we do not want to deploy the parachute.
	if(status.t1 > get_absolute_time()){
		return 0;
	}
	
	// If we reach t2 or get the signal we deploy the parachute.
	if(status.t2 <= get_absolute_time() || deployment_signal_received()){
		deploy_parachute();
		status.current_stage = GLIDING;
	}
	return 0;
}

int do_gliding_actions(flight_status_t &status)
{
	return 0;
}

int do_landed_actions(flight_status_t &status)
{
	return 0;
}
