#include "../includes/AwesomeFileSystem.hpp"
#include "../exceptions/IOException.hpp"
#include "../exceptions/OutOfMemoryException.hpp"

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

    fs_file.seekg(SIZEOF_BOOT_SECTOR);
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

void AwesomeFileSystem::load_all_into_memory() {
    load_superblock_into_memory();
}

//Goes to the specified address and writes data to the specified boundaries
void AwesomeFileSystem::write_to_file_with_specified_boundaries(int start, int num_of_char, str_t data, int address){
    fs_file.seekg(address);
    fs_file << data.substr(start, num_of_char);
};

//Reads data from second 1024 bytes and loads it to Superblock
void AwesomeFileSystem::load_superblock_from_memory() {

    if (!fs_file.is_open()) {
        throw SuperblockException("Superblock: It's impossible to load, because file is closed");
    }

    fs_file.seekg(SIZEOF_BOOT_SECTOR);
    fs_file.read((char*)(&superblock.sizeof_fs), sizeof(superblock.sizeof_fs));
    fs_file.read((char*)(&superblock.max_sizeof_file), sizeof(superblock.max_sizeof_file));
    fs_file.read((char*)(&superblock.sizeof_ilist_bytes), sizeof(superblock.sizeof_ilist_bytes));
    // fs_file.read((char*)(&Superblock::number_blocks), sizeof(superblock.number_blocks));
    fs_file.read((char*)(&superblock.number_free_blocks), sizeof(superblock.number_free_blocks));
    fs_file.read((char*)(&superblock.number_available_inodes), sizeof(superblock.number_available_inodes));
    fs_file.read((char*)(&superblock.sizeof_block), sizeof(superblock.sizeof_block));
    fs_file.read((char*)(&superblock.size_of_rootdir), sizeof(superblock.size_of_rootdir));
    
    fs_file.seekg(SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK);
    fs_file.read((char*)(&superblock.free_blocks), sizeof(superblock.free_blocks));
    fs_file.seekg(0);
}

void AwesomeFileSystem::create_file(str_t src_name) {
    if (!current_dir->is_src_in_directory(src_name)) {
        int free_block = superblock.get_free_block();
        Inode file_inode = Inode(0, free_block);

        inode_map.add_inode(0, get_abs_path(src_name), free_block);  // pass zero - type of src for inode
        current_dir->d_add_src(src_name);

        superblock.update_fields_after_inode_addition(file_inode);
        load_all_into_memory();
    } else throw IOException("File " + src_name + " already exists!"); // 🐱‍👤
};

void AwesomeFileSystem::delete_file(str_t src_name) {
    if (inode_map.is_file_in_directory(src_name)) {
        str_t abs_path = get_abs_path(src_name);

        Inode& deleted_inode = inode_map.get_inode(abs_path);
        inode_map.delete_inode(abs_path);
        current_dir->d_delete_src(src_name);

        superblock.update_fields_after_inode_deletion(deleted_inode);
        load_all_into_memory();
    } else throw IOException("No such file in directory!");
};

void AwesomeFileSystem::write_to_file(str_t src_name, str_t data) { 
    Inode& inode = open_file(src_name);
    int sizeof_file = inode.get_sizeof_file();
    int blocks_amount = inode.get_blocks_amount();
    int block_size = superblock.sizeof_block;

    int new_size = sizeof_file + data.size(); //new size for file
    int available_memory = blocks_amount * block_size; //for file on the current time

    int free_memory_in_last_block = available_memory - sizeof_file;
    int shift = block_size - free_memory_in_last_block; // shift for address from start of the last block
    size_t address = inode.get_last_block() + shift;

    if(new_size <= available_memory){ //if we can write all data into last block
        write_to_file_with_specified_boundaries(0, data.size(), data, address);
        fs_file.seekg(0);
        //update info in inode
        inode.add_size_to_sizeof_file(data.size());
        inode.update_last_file_and_inode_modif_fields();
    } else{
        write_to_file_with_specified_boundaries(0, free_memory_in_last_block, data, address); //fill in the last block to the end
        inode.add_size_to_sizeof_file(free_memory_in_last_block);

        int extra_blocks = (new_size - available_memory)/block_size; //the integer part of the number (extra blocks for data)
        if((new_size - available_memory) % block_size > 0){
            extra_blocks ++;  //+ 1 block for data
        }
        if(superblock.check_needed_number_of_free_blocks(extra_blocks)){
            int index = 0;
            while (extra_blocks > 1){
                int new_address = superblock.get_free_block();
                write_to_file_with_specified_boundaries(index, block_size, data, new_address);
                index += block_size;
                
                //update info in inode
                inode.update_inode(block_size, new_address);
                inode.update_last_file_and_inode_modif_fields();

            extra_blocks --;
            }
            int new_address = superblock.get_free_block();
            write_to_file_with_specified_boundaries(index, data.size() - index, data, new_address);
            fs_file.seekg(0);
        } else throw OutOfMemoryException("Not enough memory");
    }
};

//Returns the file's inode
Inode& AwesomeFileSystem::open_file(str_t src_name) {
    if (inode_map.is_file_in_directory(src_name)){
        Inode& inode = inode_map.get_inode(src_name);
        inode.update_last_access_time();
        return inode;
    } else throw IOException("No such file in directory!");
};

void AwesomeFileSystem::read_file(str_t src_name) {
    Inode& inode = open_file(src_name);
    vector_size_t storage = inode.get_blocks_storage();
    int num_of_available_char = inode.get_sizeof_file();
    const int block_size = superblock.sizeof_block;

    for(int i = 0; i < storage.size(); i++){
        int index = storage[i];
        fs_file.seekg(index); //change location to start of current block
        int count = 0;
        while (count < block_size && num_of_available_char > 0){
            char y;
            fs_file.read((char*)&y,sizeof(y));
            std::cout << y;
            count++;
            num_of_available_char--;
        }
    }
    fs_file.seekg(0);
}

void AwesomeFileSystem::close_file(str_t src_name) { }

void AwesomeFileSystem::upload_to_file(str_t src_name){ }

void AwesomeFileSystem::change_superblock(int new_item) {
    superblock.number_free_blocks = new_item;
}

int AwesomeFileSystem::get_for_test(){
    return superblock.sizeof_ilist_bytes;
}

// Directory's operations:
void AwesomeFileSystem::create_dir(str_t src_name) {
    if (!current_dir->is_src_in_directory(src_name)) {
        int free_block = superblock.get_free_block();
        Inode file_inode = Inode(1, free_block);

        inode_map.add_inode(1, get_abs_path(src_name), free_block);  // pass zero - type of src for inode
        current_dir->d_add_src(src_name);

        superblock.update_fields_after_inode_addition(file_inode);
        load_all_into_memory();
    } else throw IOException("File " + src_name + " already exists!"); // 🐱‍👤
}

void AwesomeFileSystem::delete_dir(str_t src_name) { }
void AwesomeFileSystem::add_file_to_dir(str_t file_name, str_t dir_name) { }
void AwesomeFileSystem::delete_file_in_dir(str_t file_name, str_t dir_name) { }
Inode& AwesomeFileSystem::open_dir(str_t src_name) { return open_file(src_name);}
void AwesomeFileSystem::close_dir(str_t src_name) { }
// void AwesomeFileSystem::link_dir(str_t src_name) { }
// void AwesomeFileSystem::unlink_dir(str_t src_name) { }
