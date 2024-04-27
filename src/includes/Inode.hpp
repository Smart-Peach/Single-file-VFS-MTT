#pragma once

#include <iostream>
#include <vector>
#include <ctime>

typedef std::string str_t;
typedef std::time_t time_t;

// describes exact file or directory
class Inode {

// TODO: add destructor, overload constructor (?)
private:
    int                 magic_number;          // Unique number of inode (aka hash) 
    int                 optional_bit1 = 0;     // | bits for permissions (optional)
    int                 optional_bit2 = 0;     // |
    int                 number_references;     // Number of references to file
    str_t               identifier;            // Identificator of owner/user and group-owner (Maybe another type)
    int                 sizeof_file;           // Current sizeof file
    time_t              last_access_time;      // | 
    time_t              last_file_modif_time;  // |
    time_t              last_inode_modif_time; // | 
    int                 blocks_amount;         // Сurrent sizeof the array with storage block addresses
    std::vector<size_t> storage_blocks;        // Array of storage block addresses
    
    // TODO: Should storage_block be a linked-list?
    // tmp:  changed to vector type due to conflicts in constructor


public:
    Inode() = default;  // tmp: only for test InodeMap funcs, should be removed lately
    ~Inode() = default;
    Inode& operator=(const Inode& other) = default;
    Inode(str_t src_name, size_t free_block);
    Inode(int magic_number, int sizeof_file, str_t identifier,
          int block_amount, std::vector<size_t> storage_blocks):
                                            magic_number(magic_number),
                                            number_references(0),
                                            identifier(identifier), 
                                            blocks_amount(block_amount), 
                                            storage_blocks(storage_blocks) 
            {
                time_t current_time = time(nullptr);
                last_access_time = current_time;
                last_file_modif_time = current_time;
                last_inode_modif_time = current_time;
            };


    const std::vector<size_t>& get_storage_blocks();   
    void print_fields();                                      
    int get_sizeof_file();                             
    int get_magic_number();
    int get_blocks_amount();
    
};