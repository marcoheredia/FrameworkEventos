#include "unity.h"
#include "fw_ota.h"

//*****Test for fw_ota_init*****/
TEST_CASE("fw_ota_init_nullurl", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_ota_init(NULL, NULL));
}


TEST_CASE("fw_stop_timer_wrongurl", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_ota_init("google.com", NULL));
}
