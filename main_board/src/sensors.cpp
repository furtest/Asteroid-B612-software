/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <elapsedMillis.h>

#include "sensors.h"
#include "bno.h"
#include "status.h"

void get_new_sensor_data(sensors_data_t &data, const flight_status_t status)
{
	static elapsedMillis bno_time = 0;
	if(bno_time > BNO055_SAMPLERATE_DELAY_MS){
		bno_get_new_events(data.bno_data, status.bno);
	}
}
