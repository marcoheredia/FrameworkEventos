#include "unity.h"
#include "fw_esp32_spiffs.h"

//*****Test for fw_esp32_spiffs_create*****/
/*TEST_CASE("fw_esp32_spiffs_create_nullfilename", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spiffs_create(NULL));
}*/

TEST_CASE("fw_esp32_spiffs_create_rightfilename", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_spiffs_create("testfile.txt"));
    TEST_ASSERT_TRUE(fw_esp32_spiffs_create("testfile2.txt"));
}

//*****Test for fw_esp32_spiffs_write*****/
TEST_CASE("fw_esp32_spiffs_write_nullfilename", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(0,fw_esp32_spiffs_write(NULL, "Testing", 7));
}

TEST_CASE("fw_esp32_spiffs_write_rightfilename", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(7,fw_esp32_spiffs_write("testfile.txt", "Testing", 7));
}

TEST_CASE("fw_esp32_spiffs_write_nullbuffer", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(0,fw_esp32_spiffs_write("testfile.txt", NULL, 7));
}

TEST_CASE("fw_esp32_spiffs_write_negativebufferlength", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(0,fw_esp32_spiffs_write("testfile.txt", "Testing", -1));
}

TEST_CASE("fw_esp32_spiffs_write_greaterbufferlength", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(7,fw_esp32_spiffs_write("testfile.txt", "Testing", 10));
}

//*****Test for fw_esp32_spiffs_read*****/
TEST_CASE("fw_esp32_spiffs_read_nullfilename", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(NULL,fw_esp32_spiffs_read(NULL, 7));
}

TEST_CASE("fw_esp32_spiffs_read_rightfilename", "[proyecto]") 
{
    TEST_ASSERT_EQUAL("Testing",fw_esp32_spiffs_read("testfile.txt",  7));
}

TEST_CASE("fw_esp32_spiffs_read_negativelength", "[proyecto]") 
{
    TEST_ASSERT_EQUAL(NULL,fw_esp32_spiffs_read("testfile.txt", -1));
}

TEST_CASE("fw_esp32_spiffs_read_allfile", "[proyecto]") 
{
    TEST_ASSERT_EQUAL("Testing",fw_esp32_spiffs_read("testfile.txt", 0));
}

TEST_CASE("fw_esp32_spiffs_reade_greaterlenght", "[proyecto]") 
{
    TEST_ASSERT_EQUAL("Testing",fw_esp32_spiffs_read("testfile.txt", 10));
}

//*****Test for fw_esp32_spiffs_rename*****/
TEST_CASE("fw_esp32_spiffs_rename_nullfilename", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spiffs_rename(NULL,"testfile2.txt"));
}

TEST_CASE("fw_esp32_spiffs_rename_nullnewfilename", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spiffs_rename("testfile.txt",NULL));
}

TEST_CASE("fw_esp32_spiffs_rename_samefilename", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spiffs_rename("testfile.txt","testfile.txt"));
}

TEST_CASE("fw_esp32_spiffs_rename_alreadyexistfilename", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_esp32_spiffs_rename("testfile.txt","testfile2.txt"));
}


TEST_CASE("fw_esp32_spiffs_rename_rightfilename", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_esp32_spiffs_rename("testfile.txt","testfile3.txt"));
}
