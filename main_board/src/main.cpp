/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Arduino.h>
#include <usb_serial.h>

#include "bno.h"
#include "debug.h"
#include "status.h"

flight_status_t flight_status;

void setup()
{	
	Serial.begin(9600);
	DEBUG("Program start");
	init_flight_status(flight_status);
	bno_calibrate_sensor(flight_status.bno);
}

void loop()
{
}
