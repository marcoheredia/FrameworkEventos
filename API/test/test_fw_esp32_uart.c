#include "unity.h"
#include "fw_esp32_uart.h"

//*****Test for fw_esp32_uart_configure*****/
TEST_CASE("fw_esp32_uart_configure_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( -1,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( 4,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_negativelength", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  -1,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_highlength", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  6,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_negativestop", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  -1,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_highstop", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  4,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_negativeparity", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  -1,  92000));
}

TEST_CASE("fw_esp32_uart_configure_highparity", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  4,  92000));
}


TEST_CASE("fw_esp32_uart_configure_rightport", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_1,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_2,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_rightlength", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_5_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_6_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_1,  UART_DATA_7_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_rightstop", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_1,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_1_5,  UART_PARITY_ODD,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

TEST_CASE("fw_esp32_uart_configure_rightparity", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_DISABLE,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_EVEN,  92000));
    TEST_ASSERT_TRUE(fw_esp32_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_ODD,  92000));
}

//*****Test for fw_esp32_uart_write*****/
TEST_CASE("fw_esp32_uart_write_negativeport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_write( -1,  "Test",  4));
}

TEST_CASE("fw_esp32_uart_write_highport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_write( 5,  "Test",  4));
}

TEST_CASE("fw_esp32_uart_write_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_write( UART_NUM_0,  NULL,  4));
}

TEST_CASE("fw_esp32_uart_write_right", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(4,fw_esp32_uart_write( UART_NUM_0, "Test",  4));
}

//*****Test for fw_esp32_uart_read*****/
TEST_CASE("fw_esp32_uart_read_negativeport", "[proyecto]") 
{
    char *buffer;
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_read( -1,  buffer,  4));
}

TEST_CASE("fw_esp32_uart_read_highport", "[proyecto]") 
{
    char *buffer;
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_read( 5,  buffer,  4));
}

TEST_CASE("fw_esp32_uart_read_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_uart_read( UART_NUM_0,  NULL,  4));
}

//*****Test for fw_esp32_uart_flush*****/
TEST_CASE("fw_esp32_uart_configure_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_flush( -1));
}

TEST_CASE("fw_esp32_uart_configure_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_uart_flush( 4));
}

TEST_CASE("fw_esp32_uart_configure_rightport", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_uart_flush( UART_NUM_0));
    TEST_ASSERT_TRUE(fw_esp32_uart_flush( UART_NUM_1));
    TEST_ASSERT_TRUE(fw_esp32_uart_flush( UART_NUM_2));
}
