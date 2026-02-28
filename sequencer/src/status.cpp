/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "status.h"

void init_flight_status(flight_status_t &status)
{
	status.current_stage = PRE_FLIGHT;
}
