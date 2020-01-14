/*
 * Class that holds stuff around configurations
 * 
 * @author Daniel Córdova A.
 */
#include <string>
#include "readconfig.cpp"

using namespace std;

const string CONFIG_PATH = ".config";
const char SLASH = '/';
const string CONFIG_FILE_NAME = "cooper.conf";

class Configuration {

public:
    Configuration(string dbName) :dbName(dbName) {
        setFullCooperConfigFilePath();
        setFullCooperDBPath();
    }
    
private:
    string dbName;
    string fullDBPath;
    string fullConfigFilePath;
    
    void setFullCooperConfigFilePath() {
        string userPath = getenv("HOME");
        fullConfigFilePath = userPath + SLASH + CONFIG_PATH + SLASH + CONFIG_FILE_NAME;
    }
    
    void setFullCooperDBPath() {
        ReadConfig *readConfig = new ReadConfig();
        readConfig->readConfigFile(fullConfigFilePath);
        string customDbPath = readConfig->getDbPath();
        if (customDbPath != "") {
            fullDBPath = customDbPath;
        } else {
            string userPath = getenv("HOME");
            fullDBPath = userPath + SLASH + CONFIG_PATH + SLASH + dbName;
        }
    }
    
public:
    
    string getFullCooperDBPath() {
        return fullDBPath;
    }
    
    string getFullCooperConfigFilePath() {
        return fullConfigFilePath;
    }
    
};
