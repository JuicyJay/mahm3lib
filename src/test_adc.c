#include "unity.h"
#include "test_adc.h"

#include "adc.h"




void setUp(void) {
}

void tearDown(void) {
}

void resetTest(void) {
	tearDown();
	setUp();
}

void test_adc(void) {

	TEST_ASSERT_FALSE(adc_init(1));
//	TEST_ASSERT_FALSE(adc_get_channel_status(ADC_CHANNEL_0));
//	adc_enable_channel(ADC_CHANNEL_0);
//	TEST_ASSERT_TRUE(adc_get_channel_status(ADC_CHANNEL_0));



}
