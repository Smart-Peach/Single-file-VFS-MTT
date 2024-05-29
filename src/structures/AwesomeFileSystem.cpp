#include "../includes/AwesomeFileSystem.hpp"
#include "../exceptions/IOException.hpp"
#include "../exceptions/OutOfMemoryException.hpp"


void AwesomeFileSystem::create_file(str_t src_name) {
    std::cout << "\nCreate file: " << src_name << "\n" << std::endl;
    if (!inode_map.is_file_in_directory(src_name)) {
        int free_block = superblock.get_free_block();
        // std::cout << free_block << src_name << std::endl;
        Inode file_inode = Inode(0, free_block);
        superblock.update_fields_after_inode_addition(file_inode);
        inode_map.add_inode(0, src_name, free_block);  // pass zero - type of src for inode
        // // load_all_into_memory();
    } else throw IOException("File " + src_name + " already exists!");
};

void AwesomeFileSystem::delete_file(str_t src_name) {
    if (inode_map.is_file_in_directory(src_name)) {
        Inode& deleted_inode = inode_map.get_inode(src_name);
        inode_map.delete_inode(src_name);
        superblock.update_fields_after_inode_deletion(deleted_inode);
        // load_all_into_memory();
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
    std::cout << "Address to write : " << address << "\n";
        loader->write_string_with_limits(address, 0, data.size(), data);  // LOADER
        // fs_file.seekg(0); // DELETE

        //update info in inode
        inode.add_size_to_sizeof_file(data.size());
        inode.update_last_file_and_inode_modif_fields();
    } else{
        loader->write_string_with_limits(address, 0, free_memory_in_last_block, data); //fill in the last block to the end
        inode.add_size_to_sizeof_file(free_memory_in_last_block);

        // CHANGE TO ONE STRING
        int extra_blocks = (new_size - available_memory)/block_size; //the integer part of the number (extra blocks for data)
        if((new_size - available_memory) % block_size > 0){
            extra_blocks ++;  //+ 1 block for data
        }

        
        if(superblock.check_needed_number_of_free_blocks(extra_blocks)){
            int index = 0;
            while (extra_blocks > 1){
                size_t new_address = superblock.get_free_block();
                loader->write_string_with_limits(new_address, index, block_size, data);
                index += block_size;
                
                //update info in inode
                inode.update_inode(block_size, new_address);
                inode.update_last_file_and_inode_modif_fields();

            extra_blocks --;
            }
            size_t new_address = superblock.get_free_block();
            loader->write_string_with_limits(new_address, index, data.size() - index, data);
            // fs_file.seekg(0); // DELETED
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
    std::cout << "Reading file\n";

    Inode& inode = open_file(src_name);

    vector_size_t storage = inode.get_blocks_storage();
    int num_of_available_char = inode.get_sizeof_file();
    const int block_size = superblock.sizeof_block;

    for(int i = 0; i < storage.size(); i++){
        size_t index = storage[i];
        int count = 0;

        std::cout << index << " - BLOCK ADDRESS\n";
        while (count < block_size && num_of_available_char > 0){
            char y;
            // fs_file.read((char*)&y,sizeof(y));
            std::cout << loader->read_char(index); // Check index!!!!!!!!!!!!!!!!
            count++;
            num_of_available_char--;
        }
    }
}

void AwesomeFileSystem::close_file(str_t src_name) { }

void AwesomeFileSystem::upload_to_file(str_t src_name){ }

void AwesomeFileSystem::change_superblock(int new_item) {
    superblock.number_free_blocks = new_item;
}

// Directory's operations:
void AwesomeFileSystem::create_dir(str_t src_name) {
    Inode dir_inode = open_file(src_name);
}

void AwesomeFileSystem::delete_dir(str_t src_name) { }
void AwesomeFileSystem::add_file_to_dir(str_t file_name, str_t dir_name) { }
void AwesomeFileSystem::delete_file_in_dir(str_t file_name, str_t dir_name) { }
Inode& AwesomeFileSystem::open_dir(str_t src_name) { return open_file(src_name);}
void AwesomeFileSystem::close_dir(str_t src_name) { }
void AwesomeFileSystem::link_dir(str_t src_name) { }
void AwesomeFileSystem::unlink_dir(str_t src_name) { }
