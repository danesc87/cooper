#include <sstream>
#include <string.h>
#include <vector>
#include <sqlite3.h>
#include "Connection.cpp"
#include "config.cpp"

using namespace std;

const string cooperDBName = "cooper.db";

void createDatabase(Connection*);
void createTables(Connection*);
void actionPerformed(Connection*, char*, string);
void printResults(vector<ToDo>);
void addNewToDo(Connection*, string);
void splitString(string&, char, vector<string>&);
void deleteToDo(Connection*, string);
void printStatusMessages(tuple<bool, string>, string);

int main(int argc, char *argv[]) {
    Configuration *configuration = new Configuration(cooperDBName);
    Connection *connection = new Connection(
        configuration->getFullCooperDBPath()
    );
    
    createDatabase(connection);
    createTables(connection);
    
    if(argc < 2) {
       fprintf(stderr, "Too few argumens\n"); 
    } else {
        char *action = argv[1];
        string toDo = (argv[2] != NULL)? (string)argv[2] : "";
        actionPerformed(connection, action, toDo);
    }
    
    delete connection;
    delete configuration;
    return 0;
}

void createDatabase(Connection *connection) {
    tuple<bool, string> createConnection = connection->createDataBase();
    printStatusMessages(createConnection, "Cannot open database due to: %s\n");
}

void createTables(Connection *connection) {
    tuple<bool, string> createTables = connection->createTables();
    printStatusMessages(createTables, "Cannot create tables due to: %s\n");
}


void actionPerformed(
    Connection *connection,
    char *action,
    string toDo
) {
    switch(*action) {
        case 'a': addNewToDo(connection, toDo);
                break;
        case 'l': printResults(connection->getAllFromDB());
                break;
        case 's': printResults(connection->getByNameFromDB(toDo));
                break;
        case 'x': printResults(connection->getByNameFromDB(toDo, true));
                break;
        case 'd': deleteToDo(connection, toDo);
                break;
        default: cout << "Invalid argument" << endl;            
    }
}

void splitString(
    string &toDo, 
    char delimiter, 
    vector<string> &nameAndDescription
) {
    int colonPosition = toDo.find_first_of(delimiter);
    if (colonPosition < 0) {
        nameAndDescription.push_back(toDo);
        nameAndDescription.push_back("");
    } else {
        nameAndDescription.push_back(toDo.substr(0, colonPosition));
        nameAndDescription.push_back(toDo.substr(colonPosition + 1));
    }
}

void addNewToDo(Connection *connection, string toDo) {
    if(toDo.size() < 1){
        printf("Cannot save Empty ToDo\n"); 
    } else {
        vector<string> nameAndDescription;
        splitString(toDo, ':', nameAndDescription);
        string name = nameAndDescription.at(0);
        string description = nameAndDescription.at(1);
        connection->insertDataIntoTable(name, description);
    }
}

void deleteToDo(Connection *connection, string toDoName) {
    tuple<bool, string> wasDeleted = connection->deleteRecordFromDB(toDoName);
    printStatusMessages(wasDeleted, "Cannot delete record due to: %s\n");
}

void printResults(vector<ToDo> toDoList) {
    for (int i = 0; i < toDoList.size(); i++) {
        printf("Name:        %s\n", toDoList[i].name.c_str());
        printf("Description: %s\n\n", toDoList[i].description.c_str());
    }
}

void printStatusMessages(
    tuple<bool,string> statusMessage, 
    string customErrorMessage
) {
    if(get<0>(statusMessage)) {
        printf("%s", get<1>(statusMessage).c_str());
    } else {
        fprintf(
            stderr, 
            customErrorMessage.c_str(),
            get<1>(statusMessage).c_str()
        );
    }
}
