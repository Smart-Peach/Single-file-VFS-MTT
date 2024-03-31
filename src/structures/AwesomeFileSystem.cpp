#include "../includes/AwesomeFileSystem.hpp"

/* TODO: EXTENDS FileSystem.cpp

Create file:
    - Create Inode
    - Add Inode to i-list
    - Add Inode to Superblock (update fields in Superblock --> it will be in Superblock.cpp)
    (I guess we don't need to open bin file here, because in description of "AddInode" in InodeMap it should write to bin file)

*/

void AwesomeFileSystem::write_to_file(string file_name, string data){};
void AwesomeFileSystem::open_file(string file_name){};
void AwesomeFileSystem::read_file(string file_name){};
void AwesomeFileSystem::close_file(string file_name){};
void AwesomeFileSystem::upload_to_file(string file_name){}
