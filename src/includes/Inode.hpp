#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "types.hpp" 

// describes exact file or directory
class Inode {

private:
    bool          is_directory;           // Type of source: directory - 1, file - 0
    int           magic_number;          // Unique number of inode (aka hash) 
    bit           optional_bit1 = 0;     // Bits for permissions (optional) // ???
    bit           optional_bit2 = 0;     // |
    int           number_references;     // Number of references to file
    str_t         identifier;            // Identificator of owner/user and group-owner (Maybe another type)
    int           sizeof_file;           // Current sizeof file
    time_t        last_access_time;      // | 
    time_t        last_file_modif_time;  // |
    time_t        last_inode_modif_time; // | 
    int           blocks_amount;         // Сurrent sizeof the array with storage block addresses
    vector_size_t blocks_storage;        // Array of storage block addresses
    


public:
    Inode() = default;
    Inode(bool src_type);
    Inode(bool src_type, size_t free_block);
    Inode(bool src_type, int magic_number, int sizeof_file, str_t identifier,
          int block_amount, vector_size_t storage_blocks):
                                            is_directory(src_type),
                                            magic_number(magic_number),
                                            number_references(0),
                                            identifier(identifier), 
                                            blocks_amount(block_amount), 
                                            blocks_storage(storage_blocks) 
            {
                time_t current_time = time(nullptr);
                last_access_time = current_time;
                last_file_modif_time = current_time;
                last_inode_modif_time = current_time;
            };
    Inode& operator=(const Inode& other) = default;
    ~Inode() = default;

    const vector_size_t& get_blocks_storage();
    size_t get_last_block();   
    void print_fields();
    str_t get_identifier();                                      
    int get_sizeof_file();                             
    int get_magic_number();
    int get_blocks_amount();
    int get_number_of_references();
    time_t get_last_access_time();
    time_t get_last_file_modif_time();
    time_t get_last_inode_modif_time();
    bool if_directory();
    void increase_blocks_amount();
    void add_size_to_sizeof_file(int add_size);
    void update_blocks_storage(size_t address);
    void update_inode(int size, int new_address);
    void update_last_access_time();
    void update_last_file_and_inode_modif_fields();
    void increase_references_amount();
    void decrease_references_amount();
};