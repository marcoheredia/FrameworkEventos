#include "unity.h"
#include "fw_esp32_i2c.h"

//*****Test for fw_esp32_i2c_config*****/
TEST_CASE("fw_esp32_i2c_config_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(-1, I2C_MODE_MASTER, 3, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(3, I2C_MODE_MASTER, 3, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_negativemode", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, -1, 3, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_highmode", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, 4, 3, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_negativeSDApin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, -1, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_highSDApin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, 50, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_negativeSCLpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, 3, -1, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_highSCLpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, 3, 50, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_rightmaster", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, 3, 4, 32000,0));
}

TEST_CASE("fw_esp32_i2c_config_rightmaster", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_i2c_config(I2C_NUM_1, I2C_MODE_SLAVE, 5, 6, 32000,1000));
}

//*****Test for fw_i2c_master_read*****/
char *buffer=NULL;
TEST_CASE("fw_esp32_i2c_master_read_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_read(-1, 100, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c_master_read_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_read(4, 100, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c_master_read_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_read(I2C_NUM_0, 100, NULL, 20));
}

TEST_CASE("fw_esp32_i2c_master_read_nosize", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_read(I2C_NUM_0, 100, (uint8_t *) buffer, 0));
}

//*****Test for fw_esp32_i2c_master_write*****/
TEST_CASE("fw_esp32_i2c_master_write_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_write(-1, 100, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c_master_write_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_write(4, 100, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c_master_write_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_write(I2C_NUM_0, 100, NULL, 20));
}

TEST_CASE("fw_esp32_i2c_master_write_nosize", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_master_write(I2C_NUM_0, 100, (uint8_t *) buffer, 0));
}

//*****Test for fw_esp32_i2c_slave_read*****/
TEST_CASE("fw_esp32_i2c_slave_read_negativeport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_read(-1, (uint8_t *)buffer, 20));
}

TEST_CASE("fw_esp32_i2c_slave_read_highport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_read(4, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c_slave_read_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_read(I2C_NUM_1,  NULL, 20));
}

TEST_CASE("fw_esp32_i2c_slave_read_nosize", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_read(I2C_NUM_1, (uint8_t *) buffer, 0));
}

//*****Test for fw_esp32_i2c__slave_write*****/
TEST_CASE("fw_esp32_i2c__slave_write_negativeport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_write(-1, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c__slave_write_highport", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_write(4, (uint8_t *) buffer, 20));
}

TEST_CASE("fw_esp32_i2c__slave_write_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_write(I2C_NUM_1,  NULL, 20));
}

TEST_CASE("fw_esp32_i2c__slave_write_nosize", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(-1,fw_esp32_i2c_slave_write(I2C_NUM_1, (uint8_t *) buffer, 0));
}

//*****Test for fw_esp32_i2c_free*****/
TEST_CASE("fw_esp32_i2c_free_negativeport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_free(-1));
}

TEST_CASE("fw_esp32_i2c_free_highport", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_i2c_free(4));
}

TEST_CASE("fw_esp32_i2c_free_rightport", "[proyecto]") 
{
	fw_esp32_i2c_config(I2C_NUM_0, I2C_MODE_MASTER, 3, 4, 32000,0);
    TEST_ASSERT_TRUE(fw_esp32_i2c_free(I2C_NUM_0));
}