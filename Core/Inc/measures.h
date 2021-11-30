/*
 * measures.h
 *
 *  Created on: 30 nov 2021
 *      Author: semch
 */

#ifndef INC_MEASURES_H_
#define INC_MEASURES_H_

typedef struct{
	float curr_charge[];
	float curr_discharge[];
	float volt_charge[];
	float volt_discharge[];
	time_t time[];
}measure_t;

int GetMeasure(measure_t *meas);

#endif /* INC_MEASURES_H_ */
