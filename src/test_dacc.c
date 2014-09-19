/**
 * @author Stefan Angelov
 */


//  TODO:
//- testa funktionen channel enable tv� g�nger, en f�r kanal 0 och en f�r kanal 1
//- testa funktionen channel disable tv� g�nger, en f�r kanal 0 och en f�r kanal 1
//- testa funktionen init, genom att l�sa mode register att dem st�memr �verrens med vad som ska st�llas in (du f�r prata med jonathan om det)
//- testa funktionen channel enabled, genom att sj�lv l�sa av registret och kontrollera att b�de funktionen och testet svarar samma

#include "dacc_test.h"
#include "unity.c"
#include "dacc.h"

void setUp(void){
	
}

void tearDown(void){
	
}

void test_dacc_channel_0(){
	TEST_ASSERT_TRUE(dacc_enable_channel_0);
}

void test_dacc_channel_1(){
	TEST_ASSERT_TRUE(dacc_enable_channel_1);	
}
