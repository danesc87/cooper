/*
 * This file only contains some 
 * helper functions for strings
 * 
 * @author Daniel Córdova A.
 */

#include "stringutils.hpp"

string formatString(const string stringToFormat, ...) {
    vector<char> formattedString(100,'\0');
    va_list arguments;
    while (1) {
        va_start(arguments, stringToFormat);
        auto n = vsnprintf(
            formattedString.data(), 
            formattedString.size(), 
            stringToFormat.c_str(), 
            arguments
        );
        va_end(arguments);
        if ((n > -1) && (size_t(n) < formattedString.size())) {
            return formattedString.data();
        }
        if (n > -1) {
            formattedString.resize( n + 1 );
        } else {
            formattedString.resize( formattedString.size() * 2);
        }
    }
    return formattedString.data();
}


void splitString(
    string &stringToSplit, 
    char delimiter, 
    vector<string> &vectorWithSplittedString
) {
    // TODO Change this function to return a Vector
    int colonPosition = stringToSplit.find_first_of(delimiter);
    if (colonPosition < 0) {
        vectorWithSplittedString.push_back(stringToSplit);
        vectorWithSplittedString.push_back("");
    } else {
        vectorWithSplittedString.push_back(
            stringToSplit.substr(0, colonPosition)
        );
        vectorWithSplittedString.push_back(
            stringToSplit.substr(colonPosition + 1)
        );
    }
}
