/*
 * LCD.c
 *
 *  Created on: 9 nov 2021
 *      Author: nicola
 */

#include "LCD.h"
#include <string.h>

/*****************************************************************************************
 * PRIVATE CONSTANTS
 *****************************************************************************************/
#define WAKE_UP_CMD                  0x30

#define MODE_8_BIT_2_LINES_CMD       0x38
#define MODE_8_BIT_1_LINE_CMD        0x30
#define MODE_4_BIT_2_LINES_CMD       0x28
#define MODE_4_BIT_1_LINE_CMD        0x20

#define SET_CURSOR_HOME_CMD          0x10

#define DISPLAY_ON_CURSOR_ON_CMD     0x0c
#define DISPLAY_OFF_CMD              0x08
#define DISPLAY_ON_CURSOR_OFF_CMD    0x0c
#define DISPLAY_ON_CURSOR_BLINK_CMD  0x0f

#define ENTRY_MODE_SET_CMD           0x06
#define DISPLAY_CLEAR_CMD            0x01

/*****************************************************************************************
 * PRIVATE MACROS
 *****************************************************************************************/



/*****************************************************************************************
 * PRIVATE FUCTIONS
 *****************************************************************************************/

void static inline LCD_Write_en(LCD_t *lcd, uint8_t val){
	#ifndef SINGLE_GPIO_PORT
		HAL_GPIO_WritePin(lcd->CE_port, lcd->CE_pin, val);
	#else
		HAL_GPIO_WritePin(lcd->LCD_port, lcd->CE_pin, val);
	#endif
}

void static inline LCD_Write_rw(LCD_t *lcd, uint8_t val){
	#ifndef SINGLE_GPIO_PORT
		HAL_GPIO_WritePin(lcd->RW_port, lcd->RW_pin, val);
	#else
		HAL_GPIO_WritePin(lcd->LCD_port, lcd->RW_pin, val);
	#endif
}

void static inline LCD_Write_rs(LCD_t *lcd, uint8_t val){
	#ifndef SINGLE_GPIO_PORT
		HAL_GPIO_WritePin(lcd->RS_port, lcd->RS_pin, val);
	#else
		HAL_GPIO_WritePin(lcd->LCD_port, lcd->RS_pin, val);
	#endif
}

void static LCD_Send_Command(LCD_t *lcd, char command){
	#ifndef SINGLE_GPIO_PORT
		for(int i = 0; i < LCD_DATA_SIZE; i++){
			HAL_GPIO_WritePin(lcd->Data_ports[i], lcd->Data_pins[i], command & (1 << i));
		}
	#else
		for(int i = 0; i < LCD_DATA_SIZE; i++){
			HAL_GPIO_WritePin(lcd->LCD_port, lcd->Data_pins[i], command & (1 << i));
		}
	#endif

	LCD_Write_rs(lcd, 0);
	LCD_Write_rw(lcd, 0);
	LCD_Write_en(lcd, 1);

	DELAY(1);

	LCD_Write_en(lcd, 0);
}

/*****************************************************************************************
 * PUBLIC FUCTIONS
 *****************************************************************************************/
#ifndef SINGLE_GPIO_PORT
	LCD_t LCD_create(LCD_PORT_TYPE RS_port,
				 	 LCD_PIN_TYPE  RS_pin,
					 LCD_PORT_TYPE RW_port,
					 LCD_PIN_TYPE  RW_pin,
					 LCD_PORT_TYPE CE_port,
					 LCD_PIN_TYPE  CE_pin,
					 LCD_PORT_TYPE Data_ports[LCD_DATA_SIZE],
					 LCD_PIN_TYPE  Data_pins[LCD_DATA_SIZE]){

		LCD_t LCD_handler;
		int i = 0;

		LCD_handler.RS_port = RS_port;
		LCD_handler.RS_pin  = RS_pin;

		LCD_handler.RW_port = RW_port;
		LCD_handler.RW_pin  = RW_pin;

		LCD_handler.CE_port = CE_port;
		LCD_handler.CE_pin  = CE_pin;

		for(i = 0; i < LCD_DATA_SIZE; i++){
			LCD_handler.Data_ports[i] = Data_ports[i];
			LCD_handler.Data_pins[i]  = Data_pins[i];
		}

		LCD_init(&LCD_handler);

		return LCD_handler;
	}

#else
	LCD_t LCD_create(LCD_PORT_TYPE LCD_port,
					 LCD_PIN_TYPE  RS_pin,
					 LCD_PIN_TYPE  RW_pin,
					 LCD_PIN_TYPE  CE_pin,
					 LCD_PIN_TYPE  Data_pins[LCD_DATA_SIZE]){

		LCD_t LCD_handler;
		int i = 0;

		LCD_handler.LCD_port = LCD_port;

		LCD_handler.RS_pin  = RS_pin;

		LCD_handler.RW_pin  = RW_pin;

		LCD_handler.CE_pin  = CE_pin;

		for(i = 0; i < LCD_DATA_SIZE; i++){
			LCD_handler.Data_pins[i]  = Data_pins[i];
		}

		return LCD_handler;

	}
#endif

void LCD_init(LCD_t *lcd){
	LCD_Write_en(lcd, 0);
	DELAY(100);
	LCD_Send_Command(lcd, WAKE_UP_CMD);
	DELAY(30);
	LCD_Send_Command(lcd, WAKE_UP_CMD);
	DELAY(10);
	LCD_Send_Command(lcd, WAKE_UP_CMD);
	DELAY(10);
	LCD_Send_Command(lcd, MODE_8_BIT_2_LINES_CMD);
	LCD_Send_Command(lcd, SET_CURSOR_HOME_CMD);
	LCD_Send_Command(lcd, DISPLAY_ON_CURSOR_ON_CMD);
	LCD_Send_Command(lcd, ENTRY_MODE_SET_CMD);
	LCD_clear(lcd);
}


void LCD_write_string(LCD_t *lcd, char * string){
	uint8_t message_len = strlen(string);

	//check sitring lenght
	for(int j = 0; j < message_len; j++){
		#ifndef SINGLE_GPIO_PORT
			for(int i = 0; i < LCD_DATA_SIZE; i++){
				HAL_GPIO_WritePin(lcd->Data_ports[i], lcd->Data_pins[i], string[j] & (1 << i));
			}
		#else
			for(int i = 0; i < LCD_DATA_SIZE; i++){
				HAL_GPIO_WritePin(lcd->LCD_port, lcd->Data_pins[i], string[j] & (1 << i));
			}
		#endif

		LCD_Write_rs(lcd, 1);
		LCD_Write_rw(lcd, 0);
		LCD_Write_en(lcd, 1);

		DELAY(1);

		LCD_Write_en(lcd, 0);
	}
}


void LCD_set_cursor(LCD_t *lcd, uint8_t row, uint8_t col){

}


void LCD_clear(LCD_t *lcd){
	LCD_Send_Command(lcd, DISPLAY_CLEAR_CMD);

}


void LCD_go_home(LCD_t *lcd){
	LCD_Send_Command(lcd, SET_CURSOR_HOME_CMD);
}



