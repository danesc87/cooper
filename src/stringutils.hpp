/*
 * Header for StringUtils
 * 
 * @author Daniel Córdova A.
 */

#ifndef STRING_UTILS
#define STRING_UTILS

#include <string>
#include <vector>

using namespace std;

/*
 * Function that formats string like 
 * String.format from JVM langs
 */
string formatString(const string stringToFormat, ...);

/*
 * Function that split strings and place
 * them in a vector of strings it receives
 * 
 * A string
 * A delimiter
 * A vector
 */
void splitString(string&, char, vector<string>&);

#endif
