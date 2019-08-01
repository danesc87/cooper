#include <iostream>
#include <sqlite3.h>
#include <tuple>
#include "connection.hpp"
#include "stringutils.cpp"

using namespace std;

/*
 * Class that holds everything about all operations that Cooper
 * can do with SQlite3 DB's
 */
class Connection {
    
public:
    
    Connection(string cooperDBFullPath): cooperDBFullPath(cooperDBFullPath){}
    
    ~Connection() {
        sqlite3_close(cooperDB);
    }
    
private:
    
    string cooperDBFullPath;
    sqlite3 *cooperDB;
    sqlite3_stmt *statement;
    char *errorMessage = 0;
    int rc;
     
    tuple<bool, string> checkSQLiteError(string successfullMessage = "") {
        if (rc != SQLITE_OK) {
            string errorMessage = formatString(
                "SQL Error: %s", 
                sqlite3_errmsg(cooperDB)
            );
            return make_tuple(false, errorMessage);
        } else {
            return make_tuple(true, successfullMessage);
        }
    }
    
    void sqliteDone() {
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(cooperDB));
        }
    }
    
    void finalizeSQLStatement() {
        sqlite3_finalize(statement);
    }
    
    static int dbCallback(
        void *data, 
        int columnNumber, 
        char **columnData, 
        char **columnName
    ) {
        int i; 
        fprintf(stderr, "%s: ", (const char*)data);
        for (i=0; i<columnNumber; i++) {
            printf(
                "%s = %s\n", 
                columnName[i], 
                columnData[i] ? columnData[i] :"NULL"
            );
        }
        printf("\n");
        return 0;
    }
    
    void sqlInDataBaseWithExec(string sqlStatement) {
        rc = sqlite3_exec(
            cooperDB, 
            sqlStatement.c_str(), 
            dbCallback, 
            0,
            &errorMessage
        );
    }
    
    void sqlInDataBaseWithPrepare(string sqlStatement) {
        rc = sqlite3_prepare_v2(
            cooperDB, 
            sqlStatement.c_str(), 
            -1,
            &statement,
            NULL
        );
        
    }
    
    vector<ToDo> retrieveDataFromStatement() {
        vector<ToDo> toDoList;
        ToDo singleToDo;
        const unsigned char  *name, *description;
        while((rc = sqlite3_step(statement)) == SQLITE_ROW) {
            singleToDo.id = sqlite3_column_int(statement, 0);
            name = sqlite3_column_text(statement, 1);
            description = sqlite3_column_text(statement,2);
            singleToDo.name = (name != NULL) ? (char*)name : "";
            singleToDo.description = 
            (description != NULL) ? (char*)description: "";
            toDoList.push_back(singleToDo);
        }
        this->sqliteDone();
        this->finalizeSQLStatement();
        return toDoList;
    }


public:
    tuple<bool, string> createDataBase() {
        rc = sqlite3_open(cooperDBFullPath.c_str(), &cooperDB);
    
        if (rc) {
            return make_tuple(false, sqlite3_errmsg(cooperDB));
        } else {
            return make_tuple(true, "");
        }
    }
    
    tuple<bool, string> createTables() {
        this->sqlInDataBaseWithExec(TODOLIST_TABLE);
        sqlite3_free(errorMessage);
        return this->checkSQLiteError("Table created successfully");
    }
    
    tuple<bool, string> insertDataIntoTable(string name, string description) {
        string dataToInsert = formatString(
            INSERT_RECORD, 
            name.c_str(), 
            description.c_str()
        );
        this->sqlInDataBaseWithExec(dataToInsert);
        sqlite3_free(errorMessage);
        return this->checkSQLiteError("Record inserted successfully");
    }
    
    vector<ToDo> getAllFromDB() {
        this->sqlInDataBaseWithPrepare(GET_ALL_RECORDS);
        this->checkSQLiteError();
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
        
        this->sqlInDataBaseWithPrepare(query);
        this->checkSQLiteError();
        return this->retrieveDataFromStatement();
    }
    
    tuple<bool, string> deleteRecordFromDB(string name) {
        vector<ToDo> toDoForDeletion = this->getByNameFromDB(name, true);
        string query = formatString(DELETE_RECORD, toDoForDeletion[0].id);
        this->sqlInDataBaseWithExec(query);
        string succesfullDeleteMessage = formatString(
            "Record %s was deleted successfully\n", 
            name.c_str()
        );
        return this->checkSQLiteError(succesfullDeleteMessage);
    }
};
