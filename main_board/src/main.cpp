/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Arduino.h>
#include <usb_serial.h>

#include "bmp.h"
#include "bno.h"
#include "core_pins.h"
#include "debug.h"
#include "status.h"

#define DEBUG_SERIAL Serial

flight_status_t flight_status;

void setup()
{
	Serial.begin(9600);
	DEBUG("Program start");
	init_flight_status(flight_status);

	bno_restore_offsets(flight_status.bno);

	bno_calibrate_sensor(flight_status.bno);
	//bno_save_offsets(flight_status.bno);
}

void loop()
{
	static int i = 0;
	bno_data_t bno_data;
	bno_get_new_events(bno_data, flight_status.bno);
	bno_print_event(bno_data.orientation);
	bno_print_event(bno_data.ang_velocity);
	bno_print_event(bno_data.linear_accel);
	bno_print_event(bno_data.magnetometer);
	bno_print_event(bno_data.accelerometer);
	bno_print_event(bno_data.gravity);
	bmp_print_data(flight_status);
	Serial.printf("loop %d\n", i++);
	delay(1000);
}
