#include "include/blocks.h"

Blocks::Blocks(std::shared_ptr<Database> database) {
    this->db = database;
}

bool Blocks::createTable() {
    db->prepareQuery("CREATE TABLE IF NOT EXISTS BLOCKS(ID INT, VALUE INT, SUCCESSOR INT, FILE_ID INT, FOREIGN KEY(FILE_ID) REFERENCES ITEMS(ID) ON UPDATE CASCADE);");

    return db->executeQuery();
}

bool Blocks::add(int id, int value, int successor, int file_id) {
    db->prepareQuery("INSERT INTO BLOCKS(ID, VALUE, SUCCESSOR, FILE_ID) VALUES(?, ?, ?, ?);");

    db->bindToQueryInt(0, id);
    db->bindToQueryInt(1, value);
    db->bindToQueryInt(2, successor);
    db->bindToQueryInt(3, file_id);

    return db->executeQuery();
}

int Blocks::getFirstValueByFileId(int file_id) {
    db->prepareQuery("SELECT * FROM BLOCKS WHERE FILE_ID=? AND ID=1 LIMIT 1;");

    db->bindToQueryInt(0, file_id);

    db->executeQuery();

    return db->getQueryResultInt(1);
}

int Blocks::getSuccessorByValue(int value) {
    db->prepareQuery("SELECT * FROM BLOCKS WHERE VALUE=? LIMIT 1;");

    db->bindToQueryInt(0, value);

    db->executeQuery();

    return db->getQueryResultInt(2);
}

bool Blocks::remove(int value) {
    db->prepareQuery("DELETE FROM BLOCKS WHERE VALUE=?;");

    db->bindToQueryInt(0, value);

    return db->executeQuery();
}

bool Blocks::move(int old_value, int new_value) {
    db->prepareQuery("SELECT * FROM BLOCK WHERE VALUE=?;");

    db->bindToQueryInt(0, old_value);

    db->executeQuery();

    int file_id = db->getQueryResultInt(3);
    if (file_id == -1)
        return false;

    int index = db->getQueryResultInt(0);
    if (index == -1)
        return false;

    bool removed = this->remove(old_value);
    if (!removed)
        return false;

    db->prepareQuery("UPDATE VTABLE SET ID=?, FILE_ID=? WHERE POSITION=?;");
    db->bindToQueryInt(0, index);
    db->bindToQueryInt(1, file_id);
    db->bindToQueryInt(2, new_value);

    return db->executeQuery();
}

