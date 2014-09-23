/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

#include "global_definitions.h"
#include "delay_soft.h"
#include "pio.h"

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */

/*--------------------------

// Descriptive names for TIMING-pins
#define Arduino_Pin_24_Front_Reg    PIO_PA15_IDX		//Arduino Due pin 24 used to measure work load
#define Arduino_Pin_25_LineAnalizer	PIO_PD0_IDX		//Arduino Due pin 25 used to measure work load


int main (void)
{
	pio_init_param *param;

	(*param).porta = OFF;
	(*param).portb = OFF;
	(*param).portc = OFF;
	(*param).portd = ON;
	(*param).porte = OFF;
	(*param).portf = OFF;


	board_init();

	pio_init(param);



	// Insert application code here, after the board has been initialized.
	ioport_set_pin_dir(Arduino_Pin_25_LineAnalizer, IOPORT_DIR_OUTPUT);

	void pio_conf_pin(uint32_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);

	ioport_set_pin_dir(Arduino_Pin_24_Front_Reg, IOPORT_DIR_OUTPUT);
	while (1){
		ioport_set_pin_level(Arduino_Pin_24_Front_Reg, HIGH);
		//ioport_set_pin_level(Arduino_Pin_25_LineAnalizer, LOW);

		timer_delaySoftware_1us(1000);

		ioport_set_pin_level(Arduino_Pin_24_Front_Reg, LOW);
		//ioport_set_pin_level(Arduino_Pin_25_LineAnalizer, HIGH);



		volatile int j = 100;
		while (j != 0){
			j--;
		}

	}
}

-------------------------*/
