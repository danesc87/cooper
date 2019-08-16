/*
 * Class that holds stuff around configurations
 * 
 * @author Daniel Córdova A.
 */
#include <string>

using namespace std;

const string CONFIG_PATH = ".config";
const char SLASH = '/';

class Configuration {

public:
    Configuration(string dbName) :dbName(dbName) {
        setFullCooperDBPath();
    }
    
private:
    string dbName;
    string fullDBPath;
    
    void setFullCooperDBPath() {
        string userPath = getenv("HOME");
        fullDBPath = userPath + SLASH + CONFIG_PATH + SLASH + dbName;
    }
    
public:
    
    string getFullCooperDBPath() {
        return fullDBPath;
    }
    
};
