#pragma once

#include "FileSystem.hpp"
// #include "Superblock.hpp"


class AwesomeFileSystem: public FileSystem {
public:
    AwesomeFileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name):
                FileSystem(superblock, inode_map, fs_name) { }
    AwesomeFileSystem(const AwesomeFileSystem& other) = delete;
    ~AwesomeFileSystem() { fs_file.close(); };

    // Memory functions:
    void load_superblock_into_memory() override;
    void load_superblock_from_memory() override;
    void load_all_into_memory() override;

    // File operations:
    void create_file(std::string src_name) override;
    void delete_file(std::string src_name) override;
    void write_to_file(std::string src_name, std::string data) override;
    Inode open_file(std::string src_name) override;
    void read_file(std::string src_name) override;
    void close_file(std::string src_name) override;
    void upload_to_file(std::string src_name) override;
    void loop_for_write(int start, int end, std::string data, int address, int index);
    void update_inode(Inode& inode, int size, int new_address);
};