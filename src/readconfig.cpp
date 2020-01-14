#include <iostream>
#include <fstream>
#include "stringutils.cpp"

using namespace std;

const string DB_PATH_KEY = "dbPath";

class ReadConfig {
    
private:
    string dbPath;
    
public:
    void readConfigFile(string fileConfigPath) {
        string line;
        char delimiter = '=';
        ifstream configFile (fileConfigPath);
        if(configFile.is_open()) {
            while(getline(configFile,line)) {
                vector<string> configLine = splitString(line, delimiter);
                string key = configLine.at(0);
                string value = configLine.at(1);
                if (key == DB_PATH_KEY) {
                    dbPath = value;
                }
                printf("Key is: %s\n", key.c_str());
                printf("Value is: %s\n", value.c_str());
            }
            configFile.close();
        }
    }
    
    string getDbPath() {
        return dbPath;
    }
};
