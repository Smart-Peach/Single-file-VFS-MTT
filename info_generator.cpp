#include <iostream>
#include <vector>

#include "src/includes/types.hpp"
#include "src/includes/Superblock.hpp"
#include "src/includes/LoaderBinFile.hpp"

// struct Superblock_load {
//     str_t             fs_type                 = "linear";   // Maybe special structure should be here (aka fs_type)
//     int               sizeof_fs               = 1073741824; // Sizeof file system in bytes, 1 Gb
//     int               max_sizeof_file         = 1048576;  // Maximum available file size, 1 Mb
//     int               sizeof_ilist_bytes      = 214726656  // Sizeof ilist in bytes (in memory)
//     int               number_blocks;          = 800000;
//     int               number_free_blocks      = 800000;     // Number of blocks available for data storage
//     int               number_available_inodes = 800000;     // Number of inodes available for storage
//     int               sizeof_block            = 1024;       // Sizeof one block
//     int               size_of_rootdir         = 512;        // Size of root directory
//     std::vector<bit> free_blocks;                          // May be faster in case array of bool --> in beginning 838776 0's

// };

void prepare_file(Loader* loader) {
    size_t address = 0;
    for(int i = 0; i < 1073741824; i++) {
        loader->write_char(address, 0);
        if (!(i % 1000)) { std::cout << i << "\n"; }
    }
}

int main(int argc, char** argv) {
    Loader* loader = new LoaderBinFile(str_t("AFS.bin"));
    // prepare_file(loader);
    std::vector<bit> free_blocks;
    Superblock superblock = Superblock("linear", 1073741824, 1048576, 214726656, 800000, 800000, 800000, 1024, 512, free_blocks);
    loader->load_superblock(superblock);
}
