#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <cstdarg> // Import due to va_* functions from formatString
#include "../src/stringutils.cpp"


TEST_CASE("Should format a string to create a new one") {
    const string stringToFormat = "Hello %s, I'm a test for %s";
    string name = "Joe", formatFunction = "\"stringFormat\" function";
    const string expectedString = "Hello Joe, I'm a test for "
    "\"stringFormat\" function";
    string formattedString = formatString(
        stringToFormat, 
        name.c_str(), 
        formatFunction.c_str()
    );
    REQUIRE(formattedString == expectedString);
}


TEST_CASE("Should split some string by ':' and return a vector of strings") {
    string initialString = "Hello:World";
    vector<string> expectedValues {"Hello", "World"};
    vector<string> currentValues;
    splitString(initialString, ':', currentValues);
    for (int i = 0; i < currentValues.size(); i++) {
        REQUIRE(currentValues[i] == expectedValues[i]);
    }
}

TEST_CASE("Should split some string by '~' and return a vector of strings") {
    string initialString = "John~Doe";
    vector<string> expectedValues {"John", "Doe"};
    vector<string> currentValues;
    splitString(initialString, '~', currentValues);
    for (int i = 0; i < currentValues.size(); i++) {
        REQUIRE(currentValues[i] == expectedValues[i]);
    }
}
