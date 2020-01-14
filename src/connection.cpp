/*
 * Class that holds everything about
 * operations around SQlite3 DB's
 * 
 * @author Daniel Córdova A.
 */

#include <iostream>
#include <sqlite3.h>
#include <tuple>

using namespace std;

class Connection {
    
public:
    
    Connection(string dbPath): fullDBPath(dbPath){}
    
    ~Connection() {
        sqlite3_close(db);
    }
    
private:
    
    string fullDBPath;
    sqlite3 *db;
    sqlite3_stmt *statement;
    char *errorMessage = 0;
    int rc;
    
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


public:

    sqlite3_stmt *getStatement() {
        return statement;
    }

    char *getErrorMessage() {
        return errorMessage;
    }

    tuple<bool, string> checkSQLiteError(string successfullMessage = "") {
        if (rc != SQLITE_OK) {
            string errorMessage = formatString(
                "SQL Error: %s",
                sqlite3_errmsg(db)
            );
            return make_tuple(false, errorMessage);
        } else {
            return make_tuple(true, successfullMessage);
        }
    }

    void sqliteDone() {
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        }
    }

    void finalizeSQLStatement() {
        sqlite3_finalize(statement);
    }

    void sqlInDataBaseWithExec(string sqlStatement) {
        rc = sqlite3_exec(
            db,
            sqlStatement.c_str(), 
            dbCallback, 
            0,
            &errorMessage
        );
    }

    void sqlInDataBaseWithPrepare(string sqlStatement) {
        rc = sqlite3_prepare_v2(
            db,
            sqlStatement.c_str(), 
            -1,
            &statement,
            NULL
        );
        
    }

    tuple<bool, string> createDataBase() {
        rc = sqlite3_open(fullDBPath.c_str(), &db);
    
        if (rc) {
            return make_tuple(false, sqlite3_errmsg(db));
        } else {
            return make_tuple(true, "");
        }
    }

    tuple<bool, string> createTables(string slqForTables) {
        this->sqlInDataBaseWithExec(slqForTables);
        sqlite3_free(errorMessage);
        return this->checkSQLiteError("Table created successfully");
    }
};
