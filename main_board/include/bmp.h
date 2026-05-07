/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BMP_H
#define BMP_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "status.h"

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   ((int8_t) 0)

/*
 * Initialise the bmp280.
 *
 * Performs all the initialisation.
 * Returns:
 * 	0 on success
 * 	non zero if failed to init
 *
 */
int bmp_init_sensor(flight_status_t &status);


void bmp_print_data(flight_status_t &status);

#endif /* BMP_H */
