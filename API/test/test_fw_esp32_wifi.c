#include "unity.h"
#include "fw_esp32_wifi.h"

#define wifi_ssid "test"
#define wifi_pass "test123"

//*****Test for fw_esp32_wifi_setup_ap*****/
TEST_CASE("fw_esp32_wifi_setup_ap_nullssid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_setup_ap(NULL,wifi_pass));
}

TEST_CASE("fw_esp32_wifi_setup_ap_nullpass", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_setup_ap(wifi_ssid,NULL));
}

TEST_CASE("fw_esp32_wifi_setup_ap_right", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_wifi_setup_ap(wifi_ssid,wifi_pass));
}

//*****Test for fw_esp32_wifi_connect*****/
TEST_CASE("fw_esp32_wifi_connect_nullssid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_connect(NULL,wifi_pass));
}
