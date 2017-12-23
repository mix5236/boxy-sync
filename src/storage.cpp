#include "include/storage.h"

using namespace std;

Storage::Storage(int block_size) {
    this->m_block_size = block_size;
}

Storage::~Storage() {
    delete this->m_storage_file;
}

bool Storage::open(string path) {
    this->m_storage_file_path = path;

    this->m_storage_file = new fstream(this->m_storage_file_path.c_str(), std::fstream::in | std::fstream::out);
    return true;
}

long Storage::writeBlock(const char *buffer) {
    long position = getSize();
    this->m_storage_file->write(buffer, this->m_block_size);
    return position;
}

bool Storage::readBlock(long position, char *buffer) {
    if (sizeof(buffer) != this->m_block_size) {
        return false;
    }
    else {
        long size = this->getSize();
        this->m_storage_file->seekp(position);
        this->m_storage_file->read(buffer, this->m_block_size);
        this->m_storage_file->seekp(size);
        return true;
    }
}

long Storage::getSize() {
    struct stat stat_buf;
    int return_code = stat(this->m_storage_file_path.c_str(), &stat_buf);

    if (return_code == 0) {
        return stat_buf.st_size;
    }
    else {
        return -1;
    }
}

