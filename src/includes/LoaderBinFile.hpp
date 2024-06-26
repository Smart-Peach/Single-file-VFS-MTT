#pragma once

#include <fstream>
#include <optional>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"

#include "Loader.hpp"

// Abstract class which helps to work with address space. It loads to memory our structures 
// and provides functions for reading from address space 
class LoaderBinFile : public Loader {
    
    std::fstream fs_file;        // opened file --> open in VFS_init

    unsigned int read_int(size_t& address) override;
    str_t read_string(size_t& address) override;
    time_t read_time_t(size_t& address);
    std::vector<bit> read_freeblocks(int freeblocks_amount);
    std::optional<Inode> unload_inode(size_t& address, size_t sizeof_inode);
    void write_data(size_t& address, const str_t& string); 

    void write_int(size_t& address, unsigned int num) override;
    void write_freeblocks(std::vector<bit> free_blocks);
    void write_string(size_t& address, const str_t string) override;
    void write_time_t(size_t& address, time_t time);
    void load_inode(size_t& address, Inode& inode, size_t sizeof_inode);

public:
    LoaderBinFile(str_t file_src) {
        std::cout << "Create loader\n";
        fs_file.open(file_src, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
        std::cout << "Loader is built\n";
    }

    ~LoaderBinFile(){
        fs_file.close();
    }

    char read_char(size_t& address) override;
    void write_char(size_t& address, char ch) override;
    void write_string_with_limits(size_t& address, int start, int num_of_char, str_t data) override;

    void load_superblock(Superblock superblock) override;
    void load_inode_map(InodeMap& mapa, size_t sizeof_freeblocks, size_t sizeof_inode) override;
    void load_rootdir() override;

    Superblock unload_superblock() override;
    InodeMap unload_inode_map(size_t sizeof_ilist, size_t sizeof_freeblocks, size_t sizeof_inode) override;
    void unload_rootdir() override;

    friend class LoaderTest;
};
