#pragma once

#include "FileSystem.hpp"
#include "types.hpp"

class AwesomeFileSystem: public FileSystem {
public:
    AwesomeFileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name):
                FileSystem(superblock, inode_map, fs_name) { }
    AwesomeFileSystem(const AwesomeFileSystem& other) = delete;
    ~AwesomeFileSystem() { 
        fs_file.close();
        for (auto elem: dentry_map){
            if (elem.second) delete elem.second;
        }
    }

    // Memory functions:
    void load_superblock_into_memory() override;
    void load_superblock_from_memory() override;
    void load_all_into_memory() override;

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
    void write_to_file_with_specified_boundaries(int start, int end, str_t data, int address) override;

    // Directory operations:
    void create_dir(str_t src_name) override;
    void delete_dir(str_t src_name) override;
    void add_file_to_current_dir(str_t file_name) override;
    void delete_file_in_current_dir(str_t file_name) override;
    Inode& open_dir(str_t src_name) override;
    void close_dir(str_t src_name) override;
    void change_dir(str_t src_name) override;
    void change_to_parent_dir() override;
    str_t get_working_dir_name() override { return current_dir->get_d_name(); }

     // Utils
    str_t get_abs_path( str_t src_name) { return current_dir->get_d_name() + "/" + src_name; }
    bool get_existent_dir_name(str_t& src_name) override;
    bool is_dir_empty(str_t src_name) override;
    const std::vector<str_t> get_list_of_objects_names_in_dir(str_t src_name) override;
};