/*
 * buttons.h
 *
 *  Created on: 30 nov 2021
 *      Author: semch
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "main.h"

typedef enum{UP,DOWN,UPHOLD,DOWNHOLD,NOTHING
}btn_ev;

btn_ev GetBtnEv(void);


#endif /* INC_BUTTONS_H_ */
