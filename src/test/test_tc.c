/*
 * Timer Counter (TC) unit tests
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 16 Oktober 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "test/test_tc.h"

void test_tc_conf_channel(void) {
	const tc_channel_settings_t tc_settings = {
		.wave = 0,
		.tcclks = 1
	};

	pmc_enable_peripheral_clock(ID_TC0);

	tc_conf_channel(&tc_settings, TC0, 0);

	TEST_ASSERT_TRUE(TC0->TC_CHANNEL[0].TC_CCR);
}

void test_tc_conf_block(void) {

}

void test_tc_enable_clock(void) {
	tc_enable_clock(TC0, TC_CHANNEL_0);

	// Test if using ASF way of doing things
//	tc_channel_reg_t *tc_channel;
//	tc_channel = TC0->TC_CHANNEL + 1;
//	TEST_ASSERT_TRUE(tc_channel->TC_SR & TC_SR_CLKSTA_ENABLED);

	// Test if our own way
	TEST_ASSERT_TRUE( (TC0->TC_CHANNEL[0].TC_CCR) & TC_SR_CLKSTA_ENABLED );
}

void test_tc_disable_clock(void) {

}

void test_tc_start_clock(void) {

}

void test_tc_stop_clock(void) {

}

void test_tc_read_counter_value(void) {

}
