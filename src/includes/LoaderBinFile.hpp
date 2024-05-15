#pragma once

#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"


// Abstract class which helps to work with address space. It loads to memory our structures 
// and provides functions for reading from address space 
class LoaderBinFile : public Loader {
private:
    std::fstream        fs_file;        // opened file --> open in VFS_init

    char read_char(size_t address);
    int  read_int(size_t address);
    bitset<> read_bitset(size_t address);

    void write_char(size_t address, char ch);
    void write_int(size_t address, unsigned int num);

public:
    LoaderBinFile(std::fstream file_src) : fs_file(file_src) {}
    ~LoaderBinFile() = default;

    void load_superblock();
    void load_inode_map();
    void load_rootdir();

    void unload_superblock();
    void unload_inode_map();
    void unload_rootdir();
};
