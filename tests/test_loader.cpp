#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#include "../src/includes/LoaderBinFile.hpp"

std::string BIN_FILE_NAME = "tests/test-loader.bin";


class LoaderTest {
    LoaderBinFile loader  = LoaderBinFile(BIN_FILE_NAME);

public:

    void prepare_file() {
        size_t address = 0;
        for(int i = 0; i < 10000; i++) {
            loader.write_char(address, 0);
        }
    }

    void run_all_tests() {
        test_write_int();
        test_write_multiple_ints();
        test_int_boundaries();
        test_write_char();
        test_string();
        test_time();
        test_different_types();
        test_read_wrong_memory();
        test_write_freeblocks();
        test_superblock();
        test_inode();
        test_mapa();
    }

    void checker_inodes(const Inode& inode_exp, const Inode& inode_act) {

        ASSERT_EQ(inode_exp.is_directory, inode_act.is_directory);
        ASSERT_EQ(inode_exp.magic_number, inode_act.magic_number);
        ASSERT_EQ(inode_exp.optional_bit1, inode_act.optional_bit1);
        ASSERT_EQ(inode_exp.optional_bit2, inode_act.optional_bit2);
        ASSERT_EQ(inode_exp.number_references, inode_act.number_references);
        ASSERT_EQ(inode_exp.identifier, inode_act.identifier);
        ASSERT_EQ(inode_exp.sizeof_file, inode_act.sizeof_file);
        ASSERT_EQ(inode_exp.last_access_time, inode_act.last_access_time);
        ASSERT_EQ(inode_exp.last_file_modif_time, inode_act.last_file_modif_time);
        ASSERT_EQ(inode_exp.last_inode_modif_time, inode_act.last_inode_modif_time);
        ASSERT_EQ(inode_exp.blocks_amount, inode_act.blocks_amount);
    
        ASSERT_EQ(inode_exp.blocks_storage.size(), inode_act.blocks_storage.size());

        for (size_t i=0; i< inode_exp.blocks_storage.size(); i++) {
            ASSERT_EQ(inode_exp.blocks_storage[i], inode_act.blocks_storage[i]);
        }
    }

    void test_write_char() {
        std::cout << "[RUN-] WriteReadChar\n";
        prepare_file();
        size_t address = 0;
        loader.write_char(address, 'a');
        loader.write_char(address, 'b');
        loader.write_char(address, 'c');
        loader.write_char(address, 'd');

        size_t address0 = 0;
        size_t address1 = 1;
        size_t address2 = 2;
        size_t address3 = 3;

        ASSERT_EQ(loader.read_char(address1), 'b');
        ASSERT_EQ(loader.read_char(address0), 'a');
        ASSERT_EQ(loader.read_char(address3), 'd');
        ASSERT_EQ(loader.read_char(address2), 'c');

        std::cout << "[--OK] WriteReadChar\n";
    }

    void test_read_wrong_memory() { // !!!!!!!!!!
        std::cout << "[RUN-] ReadWrongAddress\n";

        std::cout << "[--OK] ReadWrongAddress\n";
    }

    void test_write_int() {
        std::cout << "[RUN-] ReadWriteSingleInt\n";
        prepare_file();

        size_t address = 0;
        loader.write_int(address, 123);
        size_t address0 = 0;
        ASSERT_EQ(loader.read_int(address0), 123);

        std::cout << "[--OK] ReadWriteSingleInt\n";
    }

    void test_write_multiple_ints() {
        std::cout << "[RUN-] ReadWriteSingleInt\n";
        prepare_file();
        size_t address = 0;
        size_t size = sizeof(unsigned int);

        loader.write_int(address, 123);
        loader.write_int(address, 5660077);
        loader.write_int(address, 788);

        size_t address0 = 0;
        ASSERT_EQ(loader.read_int(address0), 123);
        ASSERT_EQ(loader.read_int(address0), 5660077);
        ASSERT_EQ(loader.read_int(address0), 788);

        std::cout << "[--OK] ReadWriteSingleInt\n";
    }

    void test_int_boundaries() {
        std::cout << "[RUN-] ReadIntBoundaries\n";
        prepare_file();

        size_t address = 0;
        loader.write_int(address, 2147483647);

        size_t address0 = 0;
        ASSERT_EQ(loader.read_int(address0), 2147483647);

        address = 0;
        loader.write_int(address, 4294967295);
        address0 = 0;
        ASSERT_EQ(loader.read_int(address0), 4294967295);

        std::cout << "[--OK] ReadIntBoundaries\n";
    }

    void test_different_types() {
        std::cout << "[RUN-] ReadDifferentTypes\n";
        prepare_file();

        size_t address = 0;
        loader.write_char(address, '5');

        size_t address0 = 0;
        unsigned int num = loader.read_int(address0); // 808464437 --> UB (Ok)
        
        std::cout << "[--OK] ReadDifferentTypes\n";
    }

    void test_string() {
        std::cout << "[RUN-] ReadWriteConstChar\n";
        prepare_file();

        size_t address = 0;
        loader.write_string(address, "Hello world!");

        size_t address0 = 0;
        std::string res = loader.read_string(address0);
        
        ASSERT_EQ(res, "Hello world!");
        std::cout << "[--OK] ReadWriteConstChar\n";
    }

    void test_write_freeblocks() {
        std::cout << "[RUN-] ReadWriteFREEBLOCKS\n";
        prepare_file();

        std::vector<bit> nums {false, true, true, true, false, false, true, false, true, true, true, false, true, false, true, true, false, true, true};
        loader.write_freeblocks(nums);

        std::vector<bit> actual = loader.read_freeblocks(nums.size());

        ASSERT_EQ(nums.size(), actual.size());
        for (size_t i=0; i< nums.size(); i++) {
            ASSERT_EQ(nums[i], actual[i]);
        }

        std::cout << "[--OK] ReadWriteFREEBLOCKS\n";
    }

    void test_superblock() {
        std::cout << "[RUN-] ReadWriteSUPERBLOCK\n";
        prepare_file();

        std::vector<bit> vec {false, false, false};
        Superblock superblock_exp = Superblock("linear", 1000, 10, 100, 3, 52, 30, 5, 50, vec);
        loader.load_superblock(superblock_exp);
        Superblock superblock_actual = loader.unload_superblock();

        // check fs type
        ASSERT_EQ(superblock_exp.sizeof_fs,               superblock_actual.sizeof_fs);
        ASSERT_EQ(superblock_exp.max_sizeof_file,         superblock_actual.max_sizeof_file);
        ASSERT_EQ(superblock_exp.sizeof_ilist_bytes,      superblock_actual.sizeof_ilist_bytes);
        ASSERT_EQ(superblock_exp.number_blocks,           superblock_actual.number_blocks);
        ASSERT_EQ(superblock_exp.number_free_blocks,      superblock_actual.number_free_blocks);
        ASSERT_EQ(superblock_exp.number_available_inodes, superblock_actual.number_available_inodes);
        ASSERT_EQ(superblock_exp.sizeof_block,            superblock_actual.sizeof_block);
        ASSERT_EQ(superblock_exp.size_of_rootdir,         superblock_actual.size_of_rootdir);
        
        ASSERT_EQ(superblock_exp.free_blocks.size(), superblock_actual.free_blocks.size());

        for (size_t i=0; i< vec.size(); i++) {
            ASSERT_EQ(superblock_exp.free_blocks[i], superblock_actual.free_blocks[i]);
        }

        std::cout << "[--OK] ReadWriteSUPERBLOCK\n";
    }

    void test_inode() {
        std::cout << "[RUN-] ReadWriteINODE\n";
        prepare_file();

        // Inode inode_exp = Inode(0, 512);
        vector_size_t blocks {1258, 789, 4567, 79965, 12566};
        // is_dir, magic_num, references, ident, sizeof_file, blocks_amount, <blocks>
        Inode inode_exp = Inode(false, 123456, 864, "Neighbour", 5,  blocks);

        size_t address = 0;
        loader.load_inode(address, inode_exp, 256);

        size_t address0 = 0;
        Inode inode_act = loader.unload_inode(address0, 256).value();

        checker_inodes(inode_exp, inode_act);

        std::cout << "[--OK] ReadWriteINODE\n";
    }

    void test_mapa() {
        std::cout << "[RUN-] ReadWriteMAPAPAPAPAPA\n";

        prepare_file();

        vector_size_t blocks1 {1258, 789, 4567, 79965, 12566};
        Inode inode_1 = Inode(false, 123456, 864, "Neighbour", 5,  blocks1);

        vector_size_t blocks2 {898, 36546, 5646, 654654, 56645, 7898445, 454545};
        Inode inode_2 = Inode(true, 654654, 1245, "Owner", 7,  blocks2);

        vector_size_t blocks3 {33212321, 554, 654654, 787897, 66465, 654654, 465477, 79889, 7878787, 111111};
        Inode inode_3 = Inode(false, 222222, 1000, "User", 10,  blocks3);

        InodeMap mapa = InodeMap();

        mapa.add_inode(inode_1);
        mapa.add_inode(inode_2);
        mapa.add_inode(inode_3);     

        loader.load_inode_map(mapa, 10, 100);

        InodeMap mapa_act = loader.unload_inode_map(300, 10, 100);

        ASSERT_EQ(mapa.inode_map.size(), mapa_act.inode_map.size());

        for (auto inode : mapa.inode_map) {
            Inode inode_exp = inode.second;
            int key = inode_exp.get_magic_number();
            Inode inode_act = mapa_act[key];
            checker_inodes(inode_exp, inode_act);
        }
        std::cout << "[--OK] ReadWriteMAPAPAPAPAPA\n";
    }

    void test_time() {
        std::cout << "[RUN-] ReadWriteTime_t\n";
        prepare_file();

        time_t current_time;
        time(&current_time);

        size_t address = 0;
        loader.write_time_t(address, current_time);

        size_t address0 = 0;
        time_t actual_time = loader.read_time_t(address0);

        ASSERT_EQ(current_time, actual_time);

        std::cout << "[--OK] ReadWriteTime_t\n";
    }
};


int main(int argc, char** argv) {
    LoaderTest test;
    test.run_all_tests();
}
