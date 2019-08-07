/*
 * This header contains models for cooper database
 */

#ifndef TODO_LIST
#define TODO_LIST

#include <string>

using namespace std;

const string TODOLIST_TABLE = "CREATE TABLE TODOLIST("\
    "ID     INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL,"\
    "NAME                            TEXT    NOT NULL,"\
    "DESCRIPTION                     TEXT);";

const string INSERT_RECORD = 
    "INSERT INTO TODOLIST (NAME, DESCRIPTION) VALUES('%s', '%s');";
    
const string GET_ALL_RECORDS = "SELECT * FROM TODOLIST;";

const string GET_BY_NAME = 
    "SELECT * FROM TODOLIST WHERE NAME %s \"%s\";";

const string LIKE = "LIKE";

const string DELETE_RECORD = "DELETE FROM TODOLIST WHERE ID=\"%d\"";


/*
 * ToDo Table Model
 */
struct ToDo {
    int id;
    string name;
    string description;
};

#endif
