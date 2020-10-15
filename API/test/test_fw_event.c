#include "unity.h"
#include "mp_event.h"

void test_handler();
ESP_EVENT_DEFINE_BASE(TEST_EVENTS);
#define EVENT1 1
#define EVENT2 2

//*****Test for fw_event_max_priority_handler_register*****/
TEST_CASE("fw_event_max_priority_handler_register_nullhandler", "[proyecto]") 
{
	fw_event_max_priority_loop_create();
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_max_priority_handler_register(TEST_EVENTS, EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_max_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_max_priority_handler_register(TEST_EVENTS, EVENT1, test_handler, NULL));
}

//*****Test for fw_event_max_priority_post*****/
TEST_CASE("fw_event_max_priority_post_wrongevent", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_max_priority_post(TEST_EVENTS, EVENT2,NULL, 0, 0));
}

TEST_CASE("fw_event_max_priority_post_rightevent", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_max_priority_post(TEST_EVENTS, EVENT1,NULL, 0, 0));
}

//*****Test for fw_event_max_priority_handler_unregister*****/
TEST_CASE("fw_event_max_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_max_priority_handler_register(TEST_EVENTS, EVENT1, NULL));
}

TEST_CASE("fw_event_max_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_max_priority_handler_register(TEST_EVENTS, EVENT1, test_handler));
}

//*****Test for fw_event_med_priority_handler_register*****/
TEST_CASE("fw_event_med_priority_handler_register_nullhandler", "[proyecto]") 
{
	fw_event_med_priority_loop_create();
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_med_priority_handler_register(TEST_EVENTS, EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_med_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_med_priority_handler_register(TEST_EVENTS, EVENT1, test_handler, NULL));
}

//*****Test for fw_event_med_priority_post*****/
TEST_CASE("fw_event_med_priority_post_wrongevent", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_med_priority_post(TEST_EVENTS, EVENT2,NULL, 0, 0));
}

TEST_CASE("fw_event_med_priority_post_rightevent", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_med_priority_post(TEST_EVENTS, EVENT1,NULL, 0, 0));
}

//*****Test for fw_event_max_priority_handler_unregister*****/
TEST_CASE("fw_event_med_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_med_priority_handler_register(TEST_EVENTS, EVENT1, NULL));
}

TEST_CASE("fw_event_med_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_med_priority_handler_register(TEST_EVENTS, EVENT1, test_handler));
}

//*****Test for fw_event_min_priority_handler_register*****/
TEST_CASE("fw_event_min_priority_handler_register_nullhandler", "[proyecto]") 
{
	fw_event_min_priority_loop_create();
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_min_priority_handler_register(TEST_EVENTS, EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_min_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_min_priority_handler_register(TEST_EVENTS, EVENT1, test_handler, NULL));
}

//*****Test for fw_event_min_priority_post*****/
TEST_CASE("fw_event_min_priority_post_wrongevent", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_min_priority_post(TEST_EVENTS, EVENT2,NULL, 0, 0));
}

TEST_CASE("fw_event_min_priority_post_rightevent", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_min_priority_post(TEST_EVENTS, EVENT1,NULL, 0, 0));
}

//*****Test for fw_event_min_priority_handler_unregister*****/
TEST_CASE("fw_event_min_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(ESP_OK,fw_event_min_priority_handler_register(TEST_EVENTS, EVENT1, NULL));
}

TEST_CASE("fw_event_min_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(ESP_OK,fw_event_min_priority_handler_register(TEST_EVENTS, EVENT1, test_handler));
}