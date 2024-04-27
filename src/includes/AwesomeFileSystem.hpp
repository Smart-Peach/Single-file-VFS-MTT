#pragma once

#include "FileSystem.hpp"

class AwesomeFileSystem: public FileSystem {
public:
    AwesomeFileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name):
                FileSystem(superblock, inode_map, fs_name) { }
    AwesomeFileSystem(const AwesomeFileSystem& other) = delete;
    ~AwesomeFileSystem() { fs_file.close(); };

    // Memory functions:
    void load_superblock_into_memory() override { };
    void load_superblock_from_memory() override { };
    void load_all_into_memory() override { };

    // File operations:
    void create_file(string src_name) override { };
    void delete_file(string src_name) override { };
    void write_to_file(string src_name, string data) override { };
    void open_file(string src_name) override { };
    void read_file(string src_name) override { };
    void close_file(string src_name) override { };
    void upload_to_file(string src_name) override { };
};