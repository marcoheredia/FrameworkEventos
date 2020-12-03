#include "unity.h"
#include "fw_esp32_spi.h"

    spi_device_handle_t spi;
//*****Test for fw_esp32_spi_initialize*****/
TEST_CASE("fw_esp32_spi_initialize_negativeinput", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(-1, 2, 3, 4, 12 ,spi));
}

TEST_CASE("fw_esp32_spi_initialize_negativeoutput", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(1, -2, 3, 4, 12 ,spi));
}

TEST_CASE("fw_esp32_spi_initialize_negativeclock", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(1, 2, -3, 4, 12 ,spi));
}

TEST_CASE("fw_esp32_spi_initialize_negativeCS", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(1, 2, 3, -4, 12 ,spi));
}

TEST_CASE("fw_esp32_spi_initialize_negativeMHz", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(1, 2, 3, 4, -12 ,spi));
}

TEST_CASE("fw_esp32_spi_initialize_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_initialize(1, 2, 3, 4, 12 ,NULL));
}

TEST_CASE("fw_esp32_spi_initialize_correct", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_spi_initialize(1, 2, 3, 4, 12 ,spi));
}
//*****Test for fw_esp32_spi_transmit*****/
TEST_CASE("fw_esp32_spi_transmit_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(4,fw_esp32_spi_transmit(null,"Test",4));
}

TEST_CASE("fw_esp32_spi_transmit_zero", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(4,fw_esp32_spi_transmit(spi,"Test",0));
}

TEST_CASE("fw_esp32_spi_transmit_correct", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(4,fw_esp32_spi_transmit(spi,"Test",4));
}

//*****Test for fw_esp32_spi_remove*****/
TEST_CASE("fw_esp32_spi_remove_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_remove(NULL));
}

TEST_CASE("fw_esp32_spi_remove_correct", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_spi_remove(spi));
}

TEST_CASE("fw_esp32_spi_remove_nullhandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spi_remove(NULL));
}

TEST_CASE("fw_esp32_spi_remove_correct", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_spi_remove(spi));
}