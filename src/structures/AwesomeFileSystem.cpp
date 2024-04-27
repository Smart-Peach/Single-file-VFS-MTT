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
    fs_file << superblock.get_sizeof_fs();
    fs_file << superblock.get_max_sizeof_file();
    fs_file << superblock.get_sizeof_ilist_bytes();
    fs_file << superblock.get_number_of_blocks();
    fs_file << superblock.get_number_of_freeblocks();
    fs_file << superblock.get_number_available_inodes();
    fs_file << superblock.get_sizeof_block();
    fs_file << superblock.get_sizeof_rootdir();
    fs_file << superblock.get_free_blocks().to_string();
    fs_file.seekg(0);
}
void AwesomeFileSystem::loop_for_write(int start, int end, string data, int address, int index = 0){
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

void AwesomeFileSystem::write_to_file(string src_name, string data) { 
    Inode inode = open_file(src_name);
    int sizeof_file = inode.get_sizeof_file();
    int blocks_amount = inode.get_blocks_amount();

    int new_size = sizeof_file + data.size(); //new size for file
    int available_memory = blocks_amount * BLOCK_SIZE; //for file on the current time
    int difference = new_size - available_memory; // check who is bigger

    if(difference <= 0){ //if we can write all data into last block
        int free_memory_in_last_block = available_memory - sizeof_file;
        int shift = BLOCK_SIZE - free_memory_in_last_block; // shift for address from start of the last block
        size_t address = inode.get_last_block() + shift;
        loop_for_write(0, data.size(), data, address);
        fs_file.seekg(0);
        //update info in inode
        inode.add_size_to_sizeof_file(data.size());
        //TODO: update time_t fields in inode
    } else{
        int extra_blocks = difference/BLOCK_SIZE; //the integer part of the number (extra blocks for data)
        if(difference % BLOCK_SIZE > 0){
            extra_blocks ++;  //+ 1 block for data
        }
        if(superblock.check_num_free_blocks(extra_blocks)){
            int index = 0;
            while (extra_blocks > 1){
                int new_address = superblock.get_free_block();
                loop_for_write(0, BLOCK_SIZE, data, new_address, index);
                index += BLOCK_SIZE;
                
                //update info in inode
                update_inode(inode, BLOCK_SIZE, new_address);
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
Inode AwesomeFileSystem::open_file(string src_name) {
    if (inode_map.is_file_in_directory(src_name)){
        Inode inode = inode_map.get_inode(src_name).value();
        return inode;
    } else throw IOException("No such file in directory!");
};

void AwesomeFileSystem::read_file(string src_name) {
    Inode inode = open_file(src_name);
    std::vector<size_t> storage = inode.get_storage_blocks();
    int num_of_available_char = inode.get_sizeof_file();

    for(int i = 0; i < storage.size(); i++){
        char c;
        fs_file.seekg(storage[i]); //change location to start of current block
        while (fs_file.get(c) && i < BLOCK_SIZE && num_of_available_char > 0){
            std::cout << c;
            i++;
            num_of_available_char --;
        }
    }
    fs_file.seekg(0);
}

void AwesomeFileSystem::close_file(string src_name) { }

void AwesomeFileSystem::upload_to_file(string src_name){ }
