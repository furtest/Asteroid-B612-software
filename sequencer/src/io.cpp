/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <Arduino.h>
#include <stdlib.h>

#include "io.h"

int init_io_interface(void)
{
	return 0;
}

int set_takeoff_signal(void)
{
	return 0;
}

int set_parachute_deployed_signal(void)
{
	return 0;
}

void debug_log(const char *msg)
{
	static const char *message = NULL;
	static int count = 0;

	if(message != msg){
		count = 0;
		message = msg;
		Serial.println(message);
	}

	count++;
	if(count > LOOP_LOG_INTERVAL){
		Serial.println(message);
		count = 0;
	}
}
