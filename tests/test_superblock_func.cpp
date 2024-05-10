#include "../src/includes/AwesomeFileSystem.hpp"
#include "../src/exceptions/SuperblockException.hpp"

#include <assert.h>
#include <fstream>
#include <iostream>

using namespace std;


void test_superblock_memory() {
    Superblock superblock;
    InodeMap map;

    AwesomeFileSystem fs(superblock, map, "tests/test.bin");
    int prev = fs.get_for_test();
    fs.load_superblock_into_memory();
    fs.change_superblock(200);
    fs.load_superblock_from_memory();

    assert(fs.get_for_test() == prev);
}

class TestSuperblock {

public:
    void test_get_free_block_exception() {
        Superblock superblock;
        superblock.number_free_blocks = 1;

        Inode inode1 = Inode("a", 2048);
        Inode inode2 = Inode("b", 3048);

        superblock.update_fields_after_inode_addition(inode1);

        try {
            superblock.update_fields_after_inode_addition(inode2);
        } catch (SuperblockException){
            std::cout<< "PASSED" << std::endl;
        }
    }

    void test_update_after_inode_addition() {
        Superblock changable;
        Superblock prev;

        Inode inode = Inode("a", 2048);
        changable.update_fields_after_inode_addition(inode);
        
        assert(changable.number_available_inodes == prev.number_available_inodes - 1);
        assert(changable.number_free_blocks == prev.number_free_blocks - 1);
    }

    void test_update_after_inode_deletion() {
        Superblock changable;
        Superblock prev;

        Inode inode = Inode("a", 2048);
        changable.update_fields_after_inode_addition(inode);
        changable.update_fields_after_inode_deletion(inode);

        assert(changable.number_available_inodes == prev.number_available_inodes);
        assert(changable.number_free_blocks == prev.number_free_blocks);
    }

};

int main() {
    std::fstream file;
    file.open("tests/test.bin", std::ios_base::out | std::ios_base::binary);
    if(!file.is_open())
    {
        std::cout<<"Unable to open the file\n";
        return 0;
    }

    TestSuperblock test;

    test_superblock_memory();
    test.test_update_after_inode_addition();
    test.test_get_free_block_exception();
    file.close();
}
