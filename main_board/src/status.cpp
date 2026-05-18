/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <WireIMXRT.h>

#include "bmp.h"
#include "debug.h"
#include "status.h"

void init_flight_status(flight_status_t &status)
{
	status.current_stage = PRE_FLIGHT;
	status.bno = Adafruit_BNO055(55, 0x28, &Wire);
	if(!status.bno.begin()){
		while (1) {
			DEBUG("BNO broken");
		}
	}
	bmp_init_sensor(status);
}
