#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <memory>
#include <string>

/*!
 * \brief The Database class
 *
 * This class performs low-level manipulations with SQLite3 database.
 */

class Database {
    /*!
     * \brief database - Database descriptor
     */
    sqlite3 *database;
    /*!
     * \brief statement - Prepared SQLite query statement
     */
    sqlite3_stmt *statement;

public:
    Database();
    ~Database();

    /*!
     * \brief openDatabase - Opens database for reading
     * \param path - Path to database (relative or absoulte)
     * \return - Returns true on successful open, false if any errors occoured
     */
    bool open(const char *path);
    /*!
     * \brief prepareQuery - Creates query statement for further processing
     * \param query - SQLite query (use '?' for parameters that will be bound by bindToQuery)
     */
    bool prepareQuery(const char *query);
    /*!
     * \brief bindToQuery - Binds parameter marked by '?' to query statement. Parameter will be encrypted
     * \param index - Index of parameter in query (starts from 0)
     * \param value - Data to be bound to query
     */
    bool bindToQueryString(int index, std::string value);
    /*!
     * \brief bindToQuery - Binds parameter marked by '?' to query statement. Parameter won't be encrypted
     * \param index - Index of parameter in query (starts from 0)
     * \param value - Data to be bound to query
     */
    bool bindToQueryInt(int index, int value);
    /*!
     * \brief executeQuery - Executes prepared query statement
     * \return - Returns true on success, false on failure
     */
    bool executeQuery();
    /*!
     * \brief executeQuery - Prepares query and immidiately executes it
     * \param query - Query to be executed
     * \return - Returns true on success, false on failure
     */
    bool executeQuery(const char *query);
    /*!
     * \brief getQueryResult - Retrieves decrypted content of executed query that can be accessed by index.
     * \param column - Index of column (starts from 0)
     * \return - Content of column
     */
    std::string getQueryResult(int column);
    /*!
     * \brief getQueryResult - Retrieves plain content of executed query that can be accessed by index
     * \param column - Index of column (starts from 0)
     * \return - Content of column
     */
    std::string getQueryResultPlain(int column);
};

#endif // DATABASE_H
