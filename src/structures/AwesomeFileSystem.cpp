#include "../includes/AwesomeFileSystem.hpp"
#include "../exceptions/IOException.hpp"

/* TODO: EXTENDS FileSystem.cpp
Create file:
    - Create Inode
    - Add Inode to i-list
    - Add Inode to Superblock (update fields in Superblock --> it will be in Superblock.cpp)
    (I guess we don't need to open bin file here, because in description of "AddInode" in InodeMap it should write to bin file)

*/

void AwesomeFileSystem::load_superblock_into_memory() {
    if (!fs_file.is_open()) {
        throw SuperblockException("Superblock: It's impossible to load, because file is closed");
    }

    fs_file.seekg(1024);
    fs_file << superblock.fs_type;
    fs_file << superblock.sizeof_fs;
    fs_file << superblock.max_sizeof_file;
    fs_file << superblock.sizeof_ilist_bytes;
    fs_file << superblock.number_of_blocks;
    fs_file << superblock.number_of_freeblocks;
    fs_file << superblock.number_available_inodes;
    fs_file << superblock.sizeof_block;
    fs_file << superblock.sizeof_rootdir;
    fs_file << superblock.free_blocks.to_string();
    fs_file.seekg(0);
}

void AwesomeFileSystem::write_to_file(string src_name, string data) { 
    Inode inode = inode_map.get_inode(src_name).value();
    std::vector<size_t> storage = inode.get_storage_blocks();
    fs_file << data;
};

void AwesomeFileSystem::open_file(string src_name) {
    if (inode_map.is_file_in_directory(src_name)){
        Inode inode = inode_map.get_inode(src_name).value();
        std::vector<size_t> storage = inode.get_storage_blocks();
    }
};

void AwesomeFileSystem::read_file(string src_name) {
    if (inode_map.is_file_in_directory(src_name)){
        Inode inode = inode_map.get_inode(src_name).value();
        std::vector<size_t> storage = inode.get_storage_blocks();
    } else throw new IOException("No such file in directory!");
 }

void AwesomeFileSystem::close_file(string src_name) { }

void AwesomeFileSystem::upload_to_file(string src_name){ }
