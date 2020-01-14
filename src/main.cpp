/*
 * Main file of Cooper
 * 
 * @author Daniel Córdova A.
 */
#include <sstream>
#include <string.h>
#include <vector>
#include <sqlite3.h>
#include "config.cpp"
#include "cooper.cpp"

using namespace std;

const string COOPER_DB_NAME = "cooper.db";

void createDatabase(Connection*);
void createTables(Connection*);
void actionPerformed(Cooper*, char*, string);
void printResults(vector<ToDo>);
void addNewToDo(Cooper*, string);
void deleteToDo(Cooper*, string);
void printStatusMessages(tuple<bool, string>, string);

int main(int argc, char *argv[]) {
    Configuration *configuration = new Configuration(COOPER_DB_NAME);
    Connection *connection = new Connection(
        configuration->getFullCooperDBPath()
    );
    
    createDatabase(connection);
    createTables(connection);
    
    Cooper *cooper = new Cooper(connection);

    if(argc < 2) {
       fprintf(stderr, "Too few argumens\n"); 
    } else {
        char *action = argv[1];
        string toDo = (argv[2] != NULL)? (string)argv[2] : "";
        actionPerformed(cooper, action, toDo);
    }
    
    delete cooper;
    delete configuration;
    return 0;
}

void createDatabase(Connection *connection) {
    tuple<bool, string> createConnection = connection->createDataBase();
    printStatusMessages(createConnection, "Cannot open database due to: %s\n");
}

void createTables(Connection *connection) {
    tuple<bool, string> createTables = connection->createTables(TODOLIST_TABLE);
    // Print error only if SQLError is different than already exists
    if(!strstr(get<1>(createTables).c_str(), "already exists")) {
        printStatusMessages(createTables, "Cannot create tables due to: %s\n");
    }
}


void actionPerformed(
    Cooper *cooper,
    char *action,
    string toDo
) {
    switch(*action) {
        case 'a': addNewToDo(cooper, toDo);
                break;
        case 'l': printResults(cooper->getAllFromDB());
                break;
        case 's': printResults(cooper->getByNameFromDB(toDo));
                break;
        case 'x': printResults(cooper->getByNameFromDB(toDo, true));
                break;
        case 'd': deleteToDo(cooper, toDo);
                break;
        default: cout << "Invalid argument" << endl;            
    }
}

void addNewToDo(Cooper *cooper, string toDo) {
    if(toDo.size() < 1){
        printf("Cannot save Empty ToDo\n"); 
    } else {
        vector<string> nameAndDescription = splitString(toDo, ':');
        string name = nameAndDescription.at(0);
        string description = nameAndDescription.at(1);
        cooper->insertDataIntoTable(name, description);
    }
}

void deleteToDo(Cooper *cooper, string toDoName) {
    tuple<bool, string> wasDeleted = cooper->deleteRecordFromDB(toDoName);
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
