#include "unity.h"
#include "fw_esp32_mqtt.h"

void test_handler();

//*****Test for fw_esp32_mqtt_close_client*****/
TEST_CASE("fw_esp32_mqtt_close_client_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_close_client(NULL));
}

//*****Test for fw_esp32_mqtt_client_subscribe*****/
TEST_CASE("fw_esp32_mqtt_client_subscribe_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_subscribe(NULL,"test",0));
}

TEST_CASE("fw_esp32_mqtt_client_subscribe_nulltopic", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_subscribe(test_handler,NULL,0));
}

TEST_CASE("fw_esp32_mqtt_client_subscribe_negativeqos", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_subscribe(test_handler,"test",-1));
}

TEST_CASE("fw_esp32_mqtt_client_subscribe_highqos", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_subscribe(test_handler,"test",3));
}

//*****Test for fw_esp32_mqtt_client_unsubscribe*****/
TEST_CASE("fw_esp32_mqtt_client_unsubscribe_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_unsubscribe(NULL,"test"));
}

TEST_CASE("fw_esp32_mqtt_client_unsubscribe_nulltopic", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_mqtt_client_unsubscribe(test_handler,NULL));
}

//*****Test for fw_esp32_mqtt_client_publish*****/
TEST_CASE("fw_esp32_mqtt_client_publish_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(NULL,"test","testdata",8,0));
}

TEST_CASE("fw_esp32_mqtt_client_publish_nulltopic", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(test_handler,NULL,"testdata",8,0));
}

TEST_CASE("fw_esp32_mqtt_client_publish_nulldata", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(test_handler,"test",NULL,8,0));
}

TEST_CASE("fw_esp32_mqtt_client_publish_negativelen", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(test_handler,"test","testdata",-1,0));
}

TEST_CASE("fw_esp32_mqtt_client_publish_negativeqos", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(test_handler,"test","testdata",8,-1));
}

TEST_CASE("fw_esp32_mqtt_client_publish_highqos", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_mqtt_client_publish(test_handler,"test","testdata",8,3));
}