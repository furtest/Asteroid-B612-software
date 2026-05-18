/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef DATA_BNO_H
#define DATA_BNO_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define BNO055_DEFAULT_EEPROM_OFFSETS_WRITE (0)


/*
 * Contains the data retrieved from the bno055.
 */
typedef struct bno_data {
	sensors_event_t orientation;
	sensors_event_t ang_velocity;
	sensors_event_t linear_accel;
	sensors_event_t magnetometer;
	sensors_event_t accelerometer;
	sensors_event_t gravity;
	int8_t temperature;
} bno_data_t;

/*
 * Contains the calibration data and the offsets of the bno055.
 */
typedef struct bno_calibration {
	uint8_t system;					// Global calibration state
	uint8_t gyro;					// Calibration status of the gyro
	uint8_t accel;					// Calibration status of the accelerometer
	uint8_t mag;					// Calibration status of the magnetometer
	adafruit_bno055_offsets_t calibration_data;	// The offsets of the current calibration
} bno_calibration_t;

/*
 * Get a new set of events from the bno055.
 *
 * Events contain the data measured by the sensor.
 * Args:
 * 	- data : the struct that will be filled with the data
 * 	- bno : the bno to retrieve the data from
 * Returns:
 * 	The return value is not currently in use and should be discarded.
 */
int bno_get_new_events(bno_data_t &data, Adafruit_BNO055 bno);

/*
 * Get the calibration status of the sensor.
 *
 * This fills all the calibration status fields of @data
 * Args:
 * 	- data : the struct that will be filled with the data
 * 	- bno : the bno to retrieve the data from
 * Returns:
 * 	The return value is not currently in use and should be discarded.
 */
int bno_get_calibration(bno_calibration_t &data, Adafruit_BNO055 bno);

/*
 * Get the calibration offsets of the sensor.
 *
 * This fills the calibration_data field of @data.
 * This data can be used to try to use the offsets from the previous calibration and
 * avoid having to calibrate the sensor again.
 * Args:
 * 	- data : the struct that will be filled with the data
 * 	- bno : the bno to retrieve the data from
 * Returns:
 * 	The return value is not currently in use and should be discarded.
 */
int bno_get_offsets(bno_calibration_t &data, Adafruit_BNO055 bno);
int bno_save_offsets(Adafruit_BNO055 bno, int eeprom_addr = BNO055_DEFAULT_EEPROM_OFFSETS_WRITE);
int bno_restore_offsets(Adafruit_BNO055 bno, int eeprom_addr = BNO055_DEFAULT_EEPROM_OFFSETS_WRITE);

int bno_calibrate_sensor(Adafruit_BNO055 bno);

void bno_print_event(sensors_event_t &event);

#endif /* DATA_BNO_H */
