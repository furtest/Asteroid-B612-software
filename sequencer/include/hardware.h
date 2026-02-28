/*
 * Copyright (C) 2026 CLES-FACIL
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef HARDWARE_H
#define HARDWARE_H

/*
 * Returns true if the jack cable is connected.
 *
 * The jack cable is used to indicated takeoff.
 */
bool jack_connected(void);

/*
 * Checks if the parachute deployment signal has been received.
 */
bool deployment_signal_received(void);

/*
 * Deploys the parachute.
 */
int deploy_parachute(void);


#endif /* HARDWARE_H */
