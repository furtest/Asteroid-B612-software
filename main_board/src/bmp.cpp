/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <Adafruit_BMP280.h>
#include <Arduino.h>
#include <WireIMXRT.h>

#include "bmp.h"
#include "debug.h"
#include "status.h"

int bmp_init_sensor(flight_status_t &status)
{
	status.bmp = Adafruit_BMP280(&Wire1);

	unsigned bmp_stat;
	bmp_stat = status.bmp.begin();
	if (!bmp_stat) {
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
					"try a different address!"));
		Serial.print("SensorID was: 0x"); Serial.println(status.bmp.sensorID(),16);
		Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
		Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
		Serial.print("        ID of 0x60 represents a BME 280.\n");
		Serial.print("        ID of 0x61 represents a BME 680.\n");
		while (1) delay(10);
	}

	DEBUG("bmp setup");

	status.bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,	/* Continuous sampling */
			Adafruit_BMP280::SAMPLING_X2,     	/* Temp. oversampling */
			Adafruit_BMP280::SAMPLING_X16,    	/* Pressure oversampling */
			Adafruit_BMP280::FILTER_X16,      	/* Filtering. */
			Adafruit_BMP280::STANDBY_MS_1		/* Standby time. */
	);
	return 0;
}

void bmp_print_data(flight_status_t &status){
	Serial.print(F("Temperature = "));
	Serial.print(status.bmp.readTemperature());
	Serial.println(" *C");

	Serial.print(F("Pressure = "));
	Serial.print(status.bmp.readPressure());
	Serial.println(" Pa");

	Serial.print(F("Approx altitude = "));
	Serial.print(status.bmp.readAltitude(1023.6)); /* Adjusted to local forecast! */
	Serial.println(" m");

	Serial.println();
}
