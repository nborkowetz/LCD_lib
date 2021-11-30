/*
 * communication.h
 *
 *  Created on: 30 nov 2021
 *      Author: semch
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#include "battery.h"

typedef struct {
	battery_t batt_on_charge;
	battery_t batt_on_discharge;
	measure_t meas[];
}data_t;

int SendToPc(data_t *data);
int SendDebugMsg(char *msg);

#endif /* INC_COMMUNICATION_H_ */
