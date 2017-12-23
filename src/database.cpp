#include "include/database.h"
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
        return true;
    }
    else {
        return false;
    }
}

bool Database::prepareQuery(const char *query) {
    sqlite3_finalize(statement); // returns 21 if error, 0 if success

    int stat = sqlite3_prepare_v2(this->database, query, -1, &statement, 0);
    if (stat == SQLITE_OK) {
        return true;
    }
    else {
        //sqlite3_errmsg(database);
        return false;
    }
}

bool Database::bindToQuery(int index, string value) {
    // encrypt data here
    const char *array = value.c_str();

    int stat = sqlite3_bind_blob(this->statement, ++index, array, value.length(), SQLITE_TRANSIENT);

    if (stat == SQLITE_OK) {
        return true;
    }
    else {
        return false;
    }
}

bool Database::bindToQueryPlain(int index, string value) {
    int data = 0;

    try {
        data = std::stoi(value);
    }
    catch (const std::exception &ex) {
        return false;
    }

    int stat = sqlite3_bind_int(this->statement, ++index, data);

    if (stat == SQLITE_OK) {
        return true;
    }
    else {
        return false;
    }
}


bool Database::executeQuery() {
    int stat = sqlite3_step(this->statement);

    if (stat == SQLITE_ROW) {
        return true;
    }
    else if (stat == SQLITE_DONE) {
        return true;
    }
    else {
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
        string str(result);
        return str;
    }
    else {
        string str("");
        return str;
    }
}

string Database::getQueryResultPlain(int column) {
    int result = sqlite3_column_int(this->statement, column);

    if (result != 0) {
        return std::to_string(result);
    }
    else {
        string str("");
        return str;
    }
}
