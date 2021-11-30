/*
 * config.h
 *
 *  Created on: 30 nov 2021
 *      Author: semch
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "battery.h"

typedef struct {
	battery_t conf[10];
	int 	  ID;
}config_t;

int SaveConfig(config_t conf);
int LoadConfig(int ID);

#endif /* INC_CONFIG_H_ */
