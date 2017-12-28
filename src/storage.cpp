#include "include/storage.h"

using namespace std;

Storage::Storage(int block_size) {
    cout << "Storage constructed" << endl;
    this->m_block_size = block_size;
}

Storage::~Storage() {
    cout << "Storage destructed" << endl;
    fclose(this->m_storage);
}

bool Storage::open(string path) {
    this->m_storage_file_path = path;
    this->m_storage = fopen(path.c_str(), "a+");

    if (!this->m_storage)
        return false;
    else
        return true;
}

long Storage::writeBlock(const char *buffer) {
    long size = this->getSize();
    fseek(this->m_storage, size, SEEK_SET);

    int wrote = fwrite(buffer, 1, this->m_block_size, this->m_storage);

    if (wrote < 0)
        return -1;
    else
        return size;
}

bool Storage::rewriteBlock(long position, const char *buffer) {
    fseek(this->m_storage, position, SEEK_SET);

    int wrote = fwrite(buffer, 1, this->m_block_size, this->m_storage);

    if (wrote < 0)
        return false;
    else
        return true;
}

bool Storage::readBlock(long position, char *buffer) {
    fseek(this->m_storage, position, SEEK_SET);

    int read = fread(buffer, 1, this->m_block_size, this->m_storage);

    if (read < 0)
        return false;
    else
        return true;
}

long Storage::deleteBlock(long position) {
    long storage_size = this->getSize();
    long last_block_position = storage_size - m_block_size;
    int storage_fd = fileno(this->m_storage);

    // first, check if our block is the last block of the storage
    if (position == last_block_position) {
        int return_code = ftruncate(storage_fd, last_block_position);
        if (return_code == 0)
            return -1;
        else
            return -2;
    }

    // if not, copy last block in it's place
    char buffer[this->m_block_size] = {0};
    this->readBlock(last_block_position, buffer);
    this->rewriteBlock(position, buffer);

    // and delete the last block
    int return_code = ftruncate(storage_fd, last_block_position);
    if (return_code == 0)
        return last_block_position;
    else
        return -2;
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

