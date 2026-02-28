/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef ACTIONS_H
#define ACTIONS_H

#include "status.h"

int do_pre_flight_actions(flight_status_t &status);
int do_ready_actions(flight_status_t &status);
int do_flying_actions(flight_status_t &status);
int do_gliding_actions(flight_status_t &status);
int do_landed_actions(flight_status_t &status);

#endif /* ACTIONS_H */
