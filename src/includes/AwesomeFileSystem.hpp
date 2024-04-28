#pragma once

#include "FileSystem.hpp"


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
private:
    void write_to_file_with_specified_boundaries(int start, int end, std::string data, int address) override;
    void update_inode(Inode& inode, int size, int new_address) override;


    // Directory operations:
    void create_dir(std::string src_name) override;
    void delete_dir(std::string src_name) override;
    void add_file_to_dir(std::string file_name, std::string dir_name) override;
    void delete_file_in_dir(std::string file_name, std::string dir_name) override;
    Inode open_dir(std::string src_name) override;
    void close_dir(std::string src_name) override;
    void link_dir(std::string src_name) override;
    void unlink_dir(std::string src_name) override;
};