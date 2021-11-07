/*
 * LCD.h
 *
 *  Created on: Nov 7, 2021
 *      Author: nicola
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f7xx_hal.h"


//UNCOMMENT THE LINE BELOW IF THE DISPLAY IS CONNECTED TO A SINGLE GPIO PORT!!
//#define SINGLE_GPIO_PORT


/*****************************************************************************************
 * PUBLIC CONSTANTS
 *****************************************************************************************/
#define DATA_SIZE 8   //add 4 bit option


/*****************************************************************************************
 * TYPES PORTING
 *****************************************************************************************/
#define LCD_PORT_TYPE GPIO_TypeDef*

#define LCD_PIN_TYPE uint16_t

/*****************************************************************************************
 * PUBLIC TYPES
 *****************************************************************************************/
typedef enum{
	LCD_4_BIT_MODE,
	LCD_8_BIT_MODE
}LCD_Mode_t;


#ifndef SINGLE_GPIO_PORT
	typedef struct{
		//LCD mode
		//LCD_Mode_t    Mode
		//register select GPIO
		LCD_PORT_TYPE RS_port;
		LCD_PIN_TYPE  RS_pin;

		//R/W GPIO
		LCD_PORT_TYPE RW_port;
		LCD_PIN_TYPE  RW_pin;

		//LCD enable GPIO
		LCD_PORT_TYPE CE_port;
		LCD_PIN_TYPE  CE_pin;

		//data bit
		LCD_PORT_TYPE Data_ports[DATA_SIZE];
		LCD_PIN_TYPE  Data_pins[DATA_SIZE];
	}LCD_t;

#else
	typedef struct{
		//LCD mode
		//LCD_Mode_t    Mode

		//LCD GPIO port
		LCD_PORT_TYPE LCD_port;

		//register select GPIO
		LCD_PIN_TYPE  RS_pin;

		//R/W GPIO
		LCD_PIN_TYPE  RW_pin;

		//LCD enable GPIO
		LCD_PIN_TYPE  CE_pin;

		//data bit
		LCD_PIN_TYPE  Data_pins[DATA_SIZE];
	}LCD_t;
#endif

/*****************************************************************************************
 * PUBLIC FUNCTIONS
 *****************************************************************************************/
	/**
	 * @brief
	 * @param
	 * @return
	 * @note
	 */
	#ifndef SINGLE_GPIO_PORT
		LCD_t LCD_create(LCD_PORT_TYPE RS_port,
					 LCD_PIN_TYPE  RS_pin,
					 LCD_PORT_TYPE RW_port,
					 LCD_PIN_TYPE  RW_pin,
					 LCD_PORT_TYPE CE_port,
					 LCD_PIN_TYPE  CE_pin,
					 LCD_PORT_TYPE Data_ports[DATA_SIZE],
					 LCD_PIN_TYPE  Data_pins[DATA_SIZE]);

	#else
		LCD_t LCD_create(LCD_PORT_TYPE LCD_port,
						 LCD_PIN_TYPE  RS_pin,
						 LCD_PIN_TYPE  RW_pin,
						 LCD_PIN_TYPE  CE_pin,
						 LCD_PIN_TYPE  Data_pins[DATA_SIZE]);
	#endif

	/**
	 * @brief
	 * @param
	 * retrun
	 */
	void LCD_init(LCD_t *lcd);


	void LCD_write_string(LCD_t *lcd, char * string);


	void LCD_set_cursor(LCD_t *lcd, uint8_t row, uint8_t col);


	void LCD_clear(LCD_t *lcd);


	void LCD_go_home(LCD_t *lcd);


	//void LCD_set_cursor_attr(LCD_t *lcd, uint8_t cursorType);

#endif /* INC_LCD_H_ */
