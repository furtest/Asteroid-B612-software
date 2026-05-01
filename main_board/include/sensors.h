/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SENSORS_H
#define SENSORS_H

#include "bno.h"

typedef struct sensors_data{
	bno_data_t bno_data;
} sensors_data_t;

void get_new_sensor_data(sensors_data_t &data);

#endif
