/* TODO: EXTENDS FileSystem.cpp

Create file:
    - Create Inode
    - Add Inode to i-list
    - Add Inode to Superblock (update fields in Superblock --> it will be in Superblock.cpp)
    (I guess we don't need to open bin file here, because in description of "AddInode" in InodeMap it should write to bin file)

*/
#include "AwesomeFileSystem.hpp"

AwesomeFileSystem::~FileSystem(){};
void AwesomeFileSystem::write_to_file(string file_name, string data){};
void AwesomeFileSystem::open_file(string file_name){};
void AwesomeFileSystem::read_file(string file_name){};
void AwesomeFileSystem::close_file(string file_name){};
void AwesomeFileSystem::upload_to_file(string file_name){}
AwesomeFileSystem::FileSystem(Superblock superblock, bitset_t free_blocks, InodeMap inode_map, str_t fs_name):
                                superblock(superblock),
                                free_blocks(free_blocks), 
                                inode_map(inode_map) 
    {
        fs_file.open(fs_name, std::ios_base::out | std::ios_base::binary);
        fs_file.close();
    };