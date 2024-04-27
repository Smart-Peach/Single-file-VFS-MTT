#include "../includes/AwesomeFileSystem.hpp"
#include "../exceptions/IOException.hpp"

/* TODO: EXTENDS FileSystem.cpp
Create file:
    - Create Inode
    - Add Inode to i-list
    - Add Inode to Superblock (update fields in Superblock --> it will be in Superblock.cpp)
    (I guess we don't need to open bin file here, because in description of "AddInode" in InodeMap it should write to bin file)

*/


//Loads Superblock's fields into second 1024 bytes
void AwesomeFileSystem::load_superblock_into_memory() {
    if (!fs_file.is_open()) {
        throw SuperblockException("Superblock: It's impossible to load, because file is closed");
    }

    fs_file.seekg(1024);
    fs_file << superblock.fs_type;
    fs_file << superblock.sizeof_fs;
    fs_file << superblock.max_sizeof_file;
    fs_file << superblock.sizeof_ilist_bytes;
    fs_file << superblock.number_blocks;
    fs_file << superblock.number_free_blocks;
    fs_file << superblock.number_available_inodes;
    fs_file << superblock.sizeof_block;
    fs_file << superblock.size_of_rootdir;
    fs_file << superblock.free_blocks.to_string();
    fs_file.seekg(0);
}

//Reads data from second 1024 bytes and loads it to Superblock
void AwesomeFileSystem::load_superblock_from_memory() {

    if (!fs_file.is_open()) {
        throw SuperblockException("Superblock: It's impossible to load, because file is closed");
    }

    fs_file.seekg(1024);
    fs_file.read((char*)(&superblock.sizeof_fs), sizeof(superblock.sizeof_fs));
    fs_file.read((char*)(&superblock.max_sizeof_file), sizeof(superblock.max_sizeof_file));
    fs_file.read((char*)(&superblock.sizeof_ilist_bytes), sizeof(superblock.sizeof_ilist_bytes));
    fs_file.read((char*)(&Superblock::number_blocks), sizeof(superblock.number_blocks));
    fs_file.read((char*)(&superblock.number_free_blocks), sizeof(superblock.number_free_blocks));
    fs_file.read((char*)(&superblock.number_available_inodes), sizeof(superblock.number_available_inodes));
    fs_file.read((char*)(&superblock.sizeof_block), sizeof(superblock.sizeof_block));
    fs_file.read((char*)(&superblock.size_of_rootdir), sizeof(superblock.size_of_rootdir));
    fs_file.seekg(2048);
    fs_file.read((char*)(&superblock.free_blocks), sizeof(superblock.free_blocks));
    fs_file.seekg(0);
}

void AwesomeFileSystem::create_file(string src_name) {
    int free_block = superblock.get_free_block();
    Inode file_inode = Inode(src_name, free_block);
    superblock.update_fields_after_inode_addition(file_inode);
    inode_map.add_inode(file_inode);
    load_all_into_memory();
};

void AwesomeFileSystem::delete_file(string src_name) {
    if (inode_map.is_file_in_directory(src_name)) {
        inode_map.delete_inode(src_name);
        superblock.update_fields_after_inode_deletion();
        load_all_into_memory();
    } else throw IOException("No such file in directory!");
};

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
    } else throw IOException("No such file in directory!");
 }

void AwesomeFileSystem::close_file(string src_name) { }

void AwesomeFileSystem::upload_to_file(string src_name){ }
