#ifndef ITEMS_H
#define ITEMS_H

#include "database.h"
#include "item_struct.h"

#include <string>

class Items {
    /*!
     * \brief db - Database descriptor
     */
    std::shared_ptr<Database> db;

public:
    /*!
     * \brief ITable - Constructor of ITable class
     * \param d - Smart pointer to DataBase object
     */
    Items(std::shared_ptr<Database> database);
    /*!
     * \brief createTable - Creates Items table
     * \return - Returns true on success (or if table is already exists) and false on failure
     */
    bool createTable();
    /*!
     * \brief add - Adds Item to Items table
     * \param item - Item descriptor
     * \return - Returns true on success, false on failure
     */
    bool add(Item item);
    /*!
     * \brief get - Gets Item descriptor from database
     * \param name - Name of Item
     * \param path - Path of Item
     * \return - Returns Item descriptor
     */
    Item get(std::string name, std::string path);
    /*!
     * \brief remove - Delete Item entry from database
     * \param name - Name of Item
     * \param path - Path of Item
     * \return - Returns true on success, false on failure
     */
    bool remove(std::string name, std::string path);
    /*!
     * \brief getLastIndex - Gets last Item ID (equal to size_of_table - 1)
     * \return - Returns Item ID on success, 0 on failure
     */
    int getLastIndex();
};

#endif // ITEMS_H
