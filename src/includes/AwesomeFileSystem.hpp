#pragma once

#include "FileSystem.hpp"

class AwesomeFileSystem: protected FileSystem{
public:
    AwesomeFileSystem(Superblock superblock, bitset_t free_blocks, InodeMap inode_map, str_t fs_name):
                FileSystem(superblock, free_blocks, inode_map, fs_name) { }
    AwesomeFileSystem(const AwesomeFileSystem& other) = delete;
    ~AwesomeFileSystem() = default;

    void write_to_file(string, string);
    void open_file(string);
    void read_file(string);
    void close_file(string);
    void upload_to_file(string);
};