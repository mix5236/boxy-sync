#ifndef BLOCKS_H
#define BLOCKS_H
#include <memory>
#include <list>
#include "database.h"

class Blocks {
    /*!
     * \brief db - Database descriptor
     */
    std::shared_ptr<Database> db;

public:
    Blocks(std::shared_ptr<Database> database);

    bool createTable();

    bool add(int id, int value, int successor, int file_id);

    int getFirstValueByFileId(int file_id);
    int getSuccessorByValue(int value);

    bool remove(int value);
    bool move(int old_value, int new_value);
};

#endif // BLOCKS_H
