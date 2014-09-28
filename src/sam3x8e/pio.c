/*
 * pio.c
 *
 *  Created on: Sep 18, 2014
 *      Author: Theodor Lindquist
 *      Author: Soded Alatia
 */

#include "pio.h"


void pio_close(void) {
	uint32_t *p_pmc_pcer0 = (uint32_t *)0x400E0610;
	*p_pmc_pcer0 &= ~(0b111111<<11);	//clear bit 11 to 16 in PMC_PCER0
}

void pio_conf_pin(pio_reg_t *port, uint8_t pin_number, uint8_t input, uint8_t pullup) {
	//use the port function to set a single pin
	pio_conf_pins(port, (uint32_t)(1<<pin_number), input, pullup);
}

void pio_conf_pins(pio_reg_t *port, uint32_t pin_numbers, uint8_t input, uint8_t pullup) {

	//set output/input
	if(input == 1) {
		//use the output disable register to enable inputs
		port->PIO_ODR = pin_numbers;
	} else {
		//use the output enable register to enalbe outputs
		port->PIO_OER = pin_numbers;
	}

	//set pullupts
	if(pullup == 1) {
		//use the pull up enable register
		port->PIO_PUER = pin_numbers;
	} else {
		//use the pull up disable register
		port->PIO_PUDR = pin_numbers;
	}
}

void pio_conf_port(pio_reg_t *port, uint32_t inputs, uint32_t pullups) {

	//TODO move this to init ?
	//enable the pins of the port
	port->PIO_PER = ~(0);

	//set output/input
	port->PIO_ODR = inputs;		//if a bit is 1, disable output for that pin
	port->PIO_OER = ~inputs;		//if a bit is 0, enable output for that pin

	//set pullups

	//point to pull-up enable register
	port->PIO_PUER = pullups;		//enable pull-ups

	//point to pull-up disable register
	port->PIO_PUDR = ~pullups;		//disable pull-ups
}

void pio_set_pin(pio_reg_t *port, uint8_t pin_number, uint8_t level) {
	pio_set_pins(port, (uint32_t)(1<<pin_number), level);
}

void pio_set_pins(pio_reg_t *port, uint32_t pin_numbers, uint8_t level) {

	if(level == 1) {
		//set pins high
		port->PIO_SODR |= pin_numbers;
	} else {
		//set pins low
		port->PIO_SODR &= ~pin_numbers;
	}
}

void pio_set_port(pio_reg_t *port, uint32_t levels) {

	port->PIO_SODR = levels;
}

uint8_t pio_read_pin(pio_reg_t *port, uint8_t pin_number) {
	uint8_t ret = ((pio_read_port(&port) & (1<<pin_number)) >> pin_number);
	return ret;
}

uint32_t pio_read_port(pio_reg_t *port) {
	return port->PIO_PDSR;
}
