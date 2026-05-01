/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef STATUS_H
#define STATUS_H

#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>

enum flight_stages { PRE_FLIGHT, READY, FLYING, GLIDING, LANDED };

typedef struct flight_status {
	enum flight_stages current_stage;
	Adafruit_BNO055 bno;
	Adafruit_BMP280 bmp;
} flight_status_t;

void init_flight_status(flight_status_t &status);

#endif /* STATUS_H */
