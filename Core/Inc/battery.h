/*
 * battery.h
 *
 *  Created on: 30 nov 2021
 *      Author: semch
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

typedef enum{CHARGE,DISCHARGE,NC
}mod_t;

typedef struct {
	uint16_t capacity;
	float	 U_min;
	float	 U_max;
	float 	 I_chrg;
	float 	 I_dis;
	bool	 Is_good;
	mod_t	 mode;
	int 	 delay_btw_chrg;
}battery_t;

int set_charge(void);
int set_discharge(void);
int set_Vmax(void);
int set_Vmin(void);
int set_Delay(void);

battery_t get_charge(void);
battery_t get_discharge(void);
battery_t get_Vmax(void);
battery_t get_Vmin(void);
battery_t get_Delay(void);

battery_t batt_on_charge;
battery_t butt_on_discharge; //Da mettere in battery.c


#endif /* INC_BATTERY_H_ */
