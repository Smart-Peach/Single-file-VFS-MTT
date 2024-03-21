#include <iostream>

class Inode {
// describes exact file or directory

private:

    const int   magic_number;          // Unique number of inode (aka hash) 
    int         optional_bit1 = 0;     // | bits for permissions (optional)
    int         optional_bit2 = 0;     // |
    int         number_references;     // Number of references to file
    std::string identifier;            // Identificator of owner/user and group-owner (Maybe another type)
    int         sizeof_file;           // Current sizeof file
    int         last_access_time;      // | Maybe another type
    int         last_file_modif_time;  // |
    int         last_inode_modif_time; // | 
    int         storage_blocks[];      // Array of storage block addresses

    void generate_magic_number() {
        // aka hash
    }

public:

    int* get_storage_blocks() {  // Maybe another type
        return Inode::storage_blocks;
    }

    void print() {

    }

// hz whether we need this:
    int get_sizeof_file() {
        return sizeof_file;
    }

    int get_magic_number() {
        return magic_number;
    }

    int get_modification_time() {
        // Returns all time fields ??? or prints
    }

    
};

class I_list {
    // Hashtable
};
