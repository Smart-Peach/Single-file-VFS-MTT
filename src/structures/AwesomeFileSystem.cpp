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

void AwesomeFileSystem::loop_for_write(int start, int end, std::string data, int address, int index = 0){
    fs_file.seekg(address);
    for(int i = start; i < end; i++){
        fs_file.put(data[i + index]);
    }
};

void AwesomeFileSystem::update_inode(Inode& inode, int size, int new_address){
    inode.increase_blocks_amount();
    inode.add_size_to_sizeof_file(size);
    inode.update_storage_blocks(new_address);
};

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

void AwesomeFileSystem::create_file(std::string src_name) {
    if (!inode_map.is_file_in_directory(src_name)) {
        int free_block = superblock.get_free_block();
        Inode file_inode = Inode(free_block);
        superblock.update_fields_after_inode_addition(file_inode);
        inode_map.add_inode(src_name, free_block);
        load_all_into_memory();
    } else throw IOException("File " + src_name + "already exists!");
};

void AwesomeFileSystem::delete_file(std::string src_name) {
    if (inode_map.is_file_in_directory(src_name)) {
        Inode deleted_inode = inode_map.get_inode(src_name);
        inode_map.delete_inode(src_name);
        superblock.update_fields_after_inode_deletion(deleted_inode);
        load_all_into_memory();
    } else throw IOException("No such file in directory!");
};

void AwesomeFileSystem::write_to_file(std::string src_name, std::string data) { 
    Inode inode = open_file(src_name);
    int sizeof_file = inode.get_sizeof_file();
    int blocks_amount = inode.get_blocks_amount();
    int block_size = superblock.get_sizeof_block();

    int new_size = sizeof_file + data.size(); //new size for file
    int available_memory = blocks_amount * block_size; //for file on the current time
    int difference = new_size - available_memory; // check who is bigger

    if(difference <= 0){ //if we can write all data into last block
        int free_memory_in_last_block = available_memory - sizeof_file;
        int shift = block_size - free_memory_in_last_block; // shift for address from start of the last block
        size_t address = inode.get_last_block() + shift;
        loop_for_write(0, data.size(), data, address);
        fs_file.seekg(0);
        //update info in inode
        inode.add_size_to_sizeof_file(data.size());
        //TODO: update time_t fields in inode
    } else{
        int extra_blocks = difference/block_size; //the integer part of the number (extra blocks for data)
        if(difference % block_size > 0){
            extra_blocks ++;  //+ 1 block for data
        }
        if(superblock.check_num_free_blocks(extra_blocks)){
            int index = 0;
            while (extra_blocks > 1){
                int new_address = superblock.get_free_block();
                loop_for_write(0, block_size, data, new_address, index);
                index += block_size;
                
                //update info in inode
                update_inode(inode, block_size, new_address);
                //TODO: update time_t fields in inode

            extra_blocks --;
            }
            int new_address = superblock.get_free_block();
            loop_for_write(0, data.size(), data, new_address, index);
            fs_file.seekg(0);
        } else throw SuperblockException("Not enough memory");
    }
};

//Returns the file's inode
Inode AwesomeFileSystem::open_file(std::string src_name) {
    if (inode_map.is_file_in_directory(src_name)){
        Inode inode = inode_map.get_inode(src_name);
        return inode;
    } else throw IOException("No such file in directory!");
};

void AwesomeFileSystem::read_file(std::string src_name) {
    Inode inode = open_file(src_name);
    std::vector<size_t> storage = inode.get_storage_blocks();
    int num_of_available_char = inode.get_sizeof_file();
    int block_size = superblock.get_sizeof_block();

    for(int i = 0; i < storage.size(); i++){
        char c;
        fs_file.seekg(storage[i]); //change location to start of current block
        int count = 0;
        while (fs_file.get(c) && count < block_size && num_of_available_char > 0){
            std::cout << c;
            count++;
            num_of_available_char--;
        }
    }
    fs_file.seekg(0);
}

void AwesomeFileSystem::close_file(std::string src_name) { }

void AwesomeFileSystem::upload_to_file(std::string src_name){ }
