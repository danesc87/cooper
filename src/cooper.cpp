#include "cooper.hpp"
#include "connection.cpp"

/*
 * Class that contains all stuff that Cooper
 * can do with a Connection to SQLite3 DB
 */
class Cooper {

public:
    Cooper(Connection *connection): cooperConnection(connection) {}
    
    ~Cooper() {
        delete cooperConnection;
    }
    
private:
    Connection *cooperConnection;
    int rc;
    
    vector<ToDo> retrieveDataFromStatement() {
        vector<ToDo> toDoList;
        ToDo singleToDo;
        const unsigned char  *name, *description;
        while((rc = sqlite3_step(
            cooperConnection->getStatement())) == SQLITE_ROW
        ) {
            singleToDo.id = sqlite3_column_int(
                cooperConnection->getStatement(),
                0
            );
            name = sqlite3_column_text(cooperConnection->getStatement(), 1);
            description = sqlite3_column_text(
                cooperConnection->getStatement(),
                2
            );
            singleToDo.name = (name != NULL) ? (char*)name : "";
            singleToDo.description = 
            (description != NULL) ? (char*)description: "";
            toDoList.push_back(singleToDo);
        }
        // TODO need to activate this control but print results with logger lib
        //cooperConnection->sqliteDone();
        cooperConnection->finalizeSQLStatement();
        return toDoList;
    }
    
public:
    
    tuple<bool, string> insertDataIntoTable(string name, string description) {
        string dataToInsert = formatString(
            INSERT_RECORD, 
            name.c_str(), 
            description.c_str()
        );
        cooperConnection->sqlInDataBaseWithExec(dataToInsert);
        sqlite3_free(cooperConnection->getErrorMessage());
        return cooperConnection->
            checkSQLiteError("Record inserted successfully");
    }
    
    vector<ToDo> getAllFromDB() {
        cooperConnection->sqlInDataBaseWithPrepare(GET_ALL_RECORDS);
        return this->retrieveDataFromStatement();
    }
    
    vector<ToDo> getByNameFromDB(string name, bool isExplicit = false) {
        string query;
        if (isExplicit){
            query = formatString(GET_BY_NAME, "=", name.c_str());
        } else {
            string likeName = "%" + name + "%";
            query = formatString(GET_BY_NAME, LIKE.c_str(), likeName.c_str());
        }
        
        cooperConnection->sqlInDataBaseWithPrepare(query);
        return this->retrieveDataFromStatement();
    }
    
    tuple<bool, string> deleteRecordFromDB(string name) {
        vector<ToDo> toDoForDeletion = this->getByNameFromDB(name, true);
        string succesfullDeleteMessage = "No records were deleted\n";
        if(toDoForDeletion.size() > 0) {
            string query = formatString(DELETE_RECORD, toDoForDeletion[0].id);
            cooperConnection->sqlInDataBaseWithExec(query);
            succesfullDeleteMessage = formatString(
                "Record %s was deleted successfully\n", 
                name.c_str()
            );
        }
        return cooperConnection->checkSQLiteError(succesfullDeleteMessage);
    }
    
};
