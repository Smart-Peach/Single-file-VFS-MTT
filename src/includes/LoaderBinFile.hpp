#pragma once

#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"

#include "Loader.hpp"

// Abstract class which helps to work with address space. It loads to memory our structures 
// and provides functions for reading from address space 
class LoaderBinFile : public Loader {
    
    friend class LoaderTest;
    std::fstream        fs_file;        // opened file --> open in VFS_init

    char read_char(size_t address) override;
    unsigned int read_int(size_t address) override;
    str_t read_string(size_t address) override;
    std::vector<bit> read_freeblocks(int freeblocks_amount);

    void write_char(size_t address, char ch) override;
    void write_int(size_t address, unsigned int num) override;
    void write_freeblocks(std::vector<bit> free_blocks);
    void write_string(size_t address, const str_t string) override;

public:
    LoaderBinFile(str_t file_src) {
        fs_file.open(file_src, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    }

    ~LoaderBinFile(){
        fs_file.close();
    }

    void load_superblock(Superblock superblock) override;
    void load_inode_map() override;
    void load_rootdir() override;

    Superblock unload_superblock() override;
    void unload_inode_map() override;
    void unload_rootdir() override;

    friend class LoaderTest;
};
