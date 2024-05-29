#pragma once

#include "FileSystem.hpp"
#include "LoaderBinFile.hpp"
// #include "types.hpp"

class AwesomeFileSystem: public FileSystem {
public:
    // AwesomeFileSystem(Superblock superblock, InodeMap inode_map, LoaderBinFile loader):
    //             FileSystem(superblock, inode_map, loader) { }

    AwesomeFileSystem(Loader* loader) : FileSystem(loader) { std::cout << "AwesomeFileSystem is built\n"; }
    AwesomeFileSystem(const AwesomeFileSystem& other) = delete;
    ~AwesomeFileSystem() {
        loader->load_superblock(superblock);
        loader->load_inode_map(inode_map, superblock.number_blocks, 256); 
        // fs_file.close(); 
        };
    
    // Memory functions:
    // void load_superblock_into_memory() override;
    // void load_superblock_from_memory() override;
    // void load_all_into_memory() override;

    // File operations:
    void create_file(str_t src_name) override;
    void delete_file(str_t src_name) override;
    void write_to_file(str_t src_name, str_t data) override;
    Inode& open_file(str_t src_name) override;
    void read_file(str_t src_name) override;
    void close_file(str_t src_name) override;
    void upload_to_file(str_t src_name) override;
    void change_superblock(int new_item);

    int get_for_test();
    
private:
    // void init() override;
    // void finish() override;

    // void write_to_file_with_specified_boundaries(int start, int end, str_t data, int address) override;


    // Directory operations:
    void create_dir(str_t src_name) override;
    void delete_dir(str_t src_name) override;
    void add_file_to_dir(str_t file_name, str_t dir_name) override;
    void delete_file_in_dir(str_t file_name, str_t dir_name) override;
    Inode& open_dir(str_t src_name) override;
    void close_dir(str_t src_name) override;
    void link_dir(str_t src_name) override;
    void unlink_dir(str_t src_name) override;

};