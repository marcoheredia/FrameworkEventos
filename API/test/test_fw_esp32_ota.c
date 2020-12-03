#include "unity.h"
#include "fw_esp32_ota.h"

//*****Test for fw_esp32_ota_init*****/
TEST_CASE("fw_esp32_ota_init_nullurl", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_ota_init(NULL, NULL));
}


TEST_CASE("fw_esp32_ota_init_wrongurl", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_ota_init("google.com", NULL));
}
