#include "unity.h"
#include "fw_event.h"

void test_handler();

#define EVENT1 1
#define EVENT2 2

//*****Test for fw_event_max_priority_handler_register*****/
TEST_CASE("fw_event_max_priority_handler_register_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_max_priority_handler_register(EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_max_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_max_priority_handler_register(EVENT1, test_handler, NULL));
}

//*****Test for fw_event_post*****/
TEST_CASE("fw_event_post_wrongevent", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_post(EVENT2,NULL));
}

TEST_CASE("fw_event_post_rightevent", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_post(EVENT1,NULL));
}

//*****Test for fw_event_max_priority_handler_unregister*****/
TEST_CASE("fw_event_max_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_max_priority_handler_register(EVENT1, NULL));
}

TEST_CASE("fw_event_max_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_max_priority_handler_register(EVENT1, test_handler));
}

//*****Test for fw_event_med_priority_handler_register*****/
TEST_CASE("fw_event_med_priority_handler_register_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_med_priority_handler_register(EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_med_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_med_priority_handler_register(EVENT1, test_handler, NULL));
}


//*****Test for fw_event_max_priority_handler_unregister*****/
TEST_CASE("fw_event_med_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_med_priority_handler_register(EVENT1, NULL));
}

TEST_CASE("fw_event_med_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_med_priority_handler_register(EVENT1, test_handler));
}

//*****Test for fw_event_min_priority_handler_register*****/
TEST_CASE("fw_event_min_priority_handler_register_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_min_priority_handler_register(EVENT1, NULL, NULL));
}

TEST_CASE("fw_event_min_priority_handler_register_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_min_priority_handler_register(EVENT1, test_handler, NULL));
}

//*****Test for fw_event_min_priority_handler_unregister*****/
TEST_CASE("fw_event_min_priority_handler_unregister_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_NOT_EQUAL(true,fw_event_min_priority_handler_register(EVENT1, NULL));
}

TEST_CASE("fw_event_min_priority_handler_unregister_righthandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(true,fw_event_min_priority_handler_register(EVENT1, test_handler));
}