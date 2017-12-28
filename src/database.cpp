#include "include/database.h"
#include <iostream>
using namespace std;

Database::Database() {

}

Database::~Database() {
    sqlite3_close(database);
}

bool Database::open(const char *path) {
    int stat = sqlite3_open(path, &this->database);

    if (stat == SQLITE_OK) {
        sqlite3_prepare_v2(this->database, "PRAGMA foreign_keys = ON;", -1, &statement, 0);
        cout << "Database opened successfully" << endl;
        return true;
    }
    else {
        cout << "Database opened with error" << endl;
        return false;
    }
}

bool Database::prepareQuery(const char *query) {
    sqlite3_finalize(statement); // returns 21 if error, 0 if success

    int stat = sqlite3_prepare_v2(this->database, query, -1, &statement, 0);
    if (stat == SQLITE_OK) {
        cout << "Query prepared successfully" << endl;
        return true;
    }
    else {
        //sqlite3_errmsg(database);
        cout << "Query error:" << endl;
        cout << sqlite3_errmsg(database) << endl;
        return false;
    }
}

bool Database::bindToQueryString(int index, string value) {
    // encrypt data here
    cout << "Bind value: " << value << endl;
    const char *array = value.c_str();

    int stat = sqlite3_bind_blob(this->statement, ++index, array, value.length(), SQLITE_TRANSIENT);

    if (stat == SQLITE_OK) {
        cout << "Bind success" << endl;
        return true;
    }
    else {
        cout << "Bind error" << endl;
        return false;
    }
}

bool Database::bindToQueryInt(int index, int value) {
    cout << "Bind value: " << value << endl;
    int stat = sqlite3_bind_int(this->statement, ++index, value);

    if (stat == SQLITE_OK) {
        cout << "Bind success" << endl;
        return true;
    }
    else {
        cout << "Bind error" << endl;
        return false;
    }
}


bool Database::executeQuery() {
    int stat = sqlite3_step(this->statement);

    if (stat == SQLITE_ROW) {
        cout << "Execute query success" << endl;
        return true;
    }
    else if (stat == SQLITE_DONE) {
        cout << "Execute query success" << endl;
        return true;
    }
    else {
        cout << "Execute query error" << endl;
        return false;
    }
}

bool Database::executeQuery(const char *query) {
    this->prepareQuery(query);
    return this->executeQuery();
}

string Database::getQueryResult(int column) {
    char *result = (char *)sqlite3_column_blob(this->statement, column);
    int bytes = sqlite3_column_bytes(this->statement, column);

    if (result || bytes == 0) {
        // decrypt data here
        cout << "getQuery success" << endl;
        string str(result);
        return str;
    }
    else {
        cout << "getQuery error" << endl;
        string str("");
        return str;
    }
}

string Database::getQueryResultPlain(int column) {
    int result = sqlite3_column_int(this->statement, column);

    if (result != 0) {
        cout << "getQuery success" << endl;
        return std::to_string(result);
    }
    else {
        cout << "getQuery error" << endl;
        string str("");
        return str;
    }
}
