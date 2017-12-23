#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

class Storage {
    std::string m_storage_file_path;
    int m_block_size;
    std::FILE *m_storage;

public:
    Storage(int block_size);
    ~Storage();

    bool open(std::string path);
    long writeBlock(const char *buffer);
    bool rewriteBlock(long position, const char *buffer);
    long deleteBlock(long position);
    bool readBlock(long position, char *buffer);

protected:
    long getSize();
};

#endif // STORAGE_H
