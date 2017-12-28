#ifndef ITEM_STRUCT_H
#define ITEM_STRUCT_H

#include <string>
/*!
 * \brief The Item struct
 *
 * This structure is meant to be the temporary holder of Item meta-info
 */
struct Item {
    /*!
     * \brief id - Item index in DB
     */
    int id;
    /*!
     * \brief name - Item name
     */
    std::string name;
    /*!
     * \brief path - Relative path of Item inside of container
     */
    std::string path;
    /*!
     * \brief size - Item size (in bytes)
     */
    int size;
};
#endif // ITEM_STRUCT_H
