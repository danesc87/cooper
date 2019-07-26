#include <string>

using namespace std;

const string CONFIG_PATH = ".config";
const char SLASH = '/';

class Configuration {
public:
    Configuration(string cooperDBName) :cooperDBName(cooperDBName) {
        setFullCooperDBPath();
    }
    
private:
    string cooperDBName;
    string cooperDBFullPath;
    
    void setFullCooperDBPath() {
        string userPath = getenv("HOME");
        cooperDBFullPath = userPath + SLASH + CONFIG_PATH + SLASH + cooperDBName;
    }
    
public:
    
    string getFullCooperDBPath() {
        return cooperDBFullPath;
    }
    
};
