/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <Arduino.h>

#include "actions.h"
#include "io.h"
#include "status.h"

flight_status_t flight_status;

void setup()
{
	init_flight_status(flight_status);
	init_io_interface();
}

void loop()
{
	switch (flight_status.current_stage) {
		case PRE_FLIGHT:
			do_pre_flight_actions(flight_status);
			break;
		case READY:
			do_ready_actions(flight_status);
			break;
		case FLYING:
			do_flying_actions(flight_status);
			break;
		case GLIDING:
			do_gliding_actions(flight_status);
			break;
		case LANDED:
			do_landed_actions(flight_status);
			break;
	}
}
