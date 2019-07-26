#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../src/config.cpp"
#include <iostream>

const string testDB = "test.db";

Configuration *config = new Configuration("test.db");

TEST_CASE("Should create a path inside user folder '.config' where database will be placed") {
    string userPath = getenv("HOME");
    string expectedPath = userPath + "/.config/" + testDB;
    REQUIRE(config->getFullCooperDBPath() == expectedPath);
}
