#include <iostream>

// describes exact file or directory
class Inode {

// TODO: add constructor, destructor
private:
    int         magic_number;          // Unique number of inode (aka hash) 
    int         optional_bit1 = 0;     // | bits for permissions (optional)
    int         optional_bit2 = 0;     // |
    int         number_references;     // Number of references to file
    std::string identifier;            // Identificator of owner/user and group-owner (Maybe another type)
    int         sizeof_file;           // Current sizeof file
    int         last_access_time;      // | Maybe another type
    int         last_file_modif_time;  // |
    int         last_inode_modif_time; // | 
    int         amount_blocks;         // Сurrent sizeof the array with storage block addresses
    int         storage_blocks[];      // Array of storage block addresses


public:
    int* get_storage_blocks();          // Maybe another type
    void print();                       // Print all fields of inode 
    int get_sizeof_file();              // hz whether we need this:
    void set_magic_number(int new_magic_number);
    int get_magic_number();
    
};