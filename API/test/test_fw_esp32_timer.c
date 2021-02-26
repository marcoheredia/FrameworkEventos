#include "unity.h"
#include "fw_esp32_timer.h"

void fw_timer_callback(void* arg){
    
}

//*****Test for fw_esp32_timer_set*****/
TEST_CASE("fw_esp32_timer_set_negativetime", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(false,fw_esp32_timer_set(-5000, NULL));
}

TEST_CASE("fw_esp32_timer_set_righttime", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_esp32_timer_set(5000, NULL));
}

//*****Test for fw_esp32_timer_delete*****/
TEST_CASE("fw_esp32_timer_delete_right", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_esp32_timer_delete());
}

