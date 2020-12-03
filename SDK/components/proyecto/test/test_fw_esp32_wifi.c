#include "unity.h"
#include "fw_esp32_wifi.h"

//*****Test for fw_esp32_wifi_setup_ap*****/
TEST_CASE("fw_esp32_wifi_setup_ap_nullssid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_setup_ap(NULL,"test"));
}

TEST_CASE("fw_esp32_wifi_setup_ap_nullpass", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_setup_ap("test",NULL));
}

TEST_CASE("fw_esp32_wifi_setup_ap_nullpass", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_wifi_setup_ap("test","test123"));
}

//*****Test for fw_esp32_wifi_connect*****/
TEST_CASE("fw_esp32_wifi_connect_nullssid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_connect(NULL,"test"));
}

TEST_CASE("fw_esp32_wifi_setup_ap_nullpass", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_wifi_connect("test",NULL));
}