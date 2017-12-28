#include "include/items.h"

using namespace std;

Items::Items(std::shared_ptr<Database> database) {
    this->db = database;
}

bool Items::createTable() {
    db->prepareQuery("CREATE TABLE IF NOT EXISTS ITEMS(ID INT UNIQUE, NAME BLOB, PATH BLOB, SIZE BLOB);");

    return db->executeQuery();
}

bool Items::add(Item item) {
    db->executeQuery("BEGIN TRANSACTION;");

    // 1. insert entry with empty ID
    db->prepareQuery("INSERT INTO ITEMS VALUES(NULL, ?, ?, ?);");

    db->bindToQueryString(0, item.name);
    db->bindToQueryString(1, item.path);
    db->bindToQueryInt(2, item.size);

    db->executeQuery();

    // 2. get rowid of this entry
    db->prepareQuery("SELECT ROWID FROM ITEMS WHERE NAME=? AND PATH=? LIMIT 1;");

    db->bindToQueryString(0, item.name);
    db->bindToQueryString(1, item.path);

    db->executeQuery();

    int result = std::stoi(db->getQueryResultPlain(0));

    // 3. set that ID = rowid - 1
    db->prepareQuery("UPDATE ITEMS SET ID=? WHERE NAME=? AND PATH=?;");

    db->bindToQueryInt(0, result);
    db->bindToQueryString(1, item.name);
    db->bindToQueryString(2, item.path);

    if (db->executeQuery()) {
        return db->executeQuery("COMMIT");
    }
    else {
        db->executeQuery("ROLLBACK");
        return false;
    }
}

Item Items::get(string name, string path) {
    db->prepareQuery("SELECT * FROM ITEMS WHERE NAME=? AND PATH=? LIMIT 1;");

    db->bindToQueryString(0, name);
    db->bindToQueryString(1, path);

    db->executeQuery();

    Item item;
    item.name = db->getQueryResult(1);
    item.path = db->getQueryResult(2);

    if (item.name.empty() && item.path.empty()) {
        item.id = -1;
        item.size = -1;
        return item;
    }

    string temp = db->getQueryResult(3);

    try {
        item.size = stoi(temp);
    }
    catch (std::exception &ex) {
        // cout << ex.what() << endl;
        item.size = -1;
    }

    temp = db->getQueryResultPlain(0);

    try {
        item.id = stoi(temp);
    }
    catch (std::exception &ex) {
        // cout << ex.what() << endl;
        item.id = -1;
    }

    return item;
}

bool Items::remove(string name, string path) {
    db->prepareQuery("DELETE FROM ITEMS WHERE NAME=? AND PATH=?;");

    db->bindToQueryString(0, name);
    db->bindToQueryString(1, path);

    return db->executeQuery();
}
