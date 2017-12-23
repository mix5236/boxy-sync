#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

class Storage {
    long m_storage_length;
    std::string m_storage_file_path;
    std::fstream *m_storage_file;
    int m_block_size;

public:
    Storage(int block_size);
    ~Storage();

    bool open(std::string path);
    long writeBlock(const char *buffer);
    void rewriteBlock(long position, const char *buffer);
    long deleteBlock(long position);
    bool readBlock(long position, char *buffer);

protected:
    long getSize();
};

#endif // STORAGE_H
