#include "unity.h"
#include "fw_timer.h"

//*****Test for fw_start_timer*****/
TEST_CASE("fw_start_timer_negativetimerid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_start_timer(-1, 100,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_wrongtimerid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_start_timer(5, 100,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_negativetime", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_start_timer(1, -1,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_timer0", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_start_timer(0, 100,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_timer1", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_start_timer(1, 1000,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_timer2", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_start_timer(2, 500,false,NULL,NULL));
}

TEST_CASE("fw_start_timer_timer3", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_start_timer(3, 2000,false,NULL,NULL));
}

//*****Test for fw_stop_timer*****/
TEST_CASE("fw_stop_timer_negativetimerid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_stop_timer(-1));
}

TEST_CASE("fw_stop_timer_wrongtimerid", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_stop_timer(5));
}

TEST_CASE("fw_stop_timer_timer0", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_stop_timer(0));
}

TEST_CASE("fw_stop_timer_timer1", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_stop_timer(1));
}

TEST_CASE("fw_stop_timer_timer2", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_stop_timer(2));
}

TEST_CASE("fw_stop_timer_timer3", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_stop_timer(3));
}
