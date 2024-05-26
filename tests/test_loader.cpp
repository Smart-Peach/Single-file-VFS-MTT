#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#include "../src/includes/LoaderBinFile.hpp"

std::string BIN_FILE_NAME = "tests/test-loader.bin";


class LoaderTest {
    LoaderBinFile loader  = LoaderBinFile(BIN_FILE_NAME);

public:

    void prepare_file() {
        loader.fs_file.seekg(0);
        for(int i = 0; i < 10000; i++) {
            loader.write_char(i, 0);
        }
    }

    void run_all_tests() {
        // test_write_int();
        // test_write_multiple_ints();
        // test_int_boundaries();
        // test_write_char();
        // test_read_wrong_memory();
        // test_write_int();
        test_write_freeblocks();
        // test_different_types();
        // test_superblock();
    }

    void test_write_char() {
        std::cout << "[RUN-] WriteReadChar\n";
        prepare_file();

        loader.write_char(0, 'a');
        loader.write_char(1, 'b');
        loader.write_char(2, 'c');
        loader.write_char(3, 'd');

        ASSERT_EQ(loader.read_char(1), 'b');
        ASSERT_EQ(loader.read_char(0), 'a');
        ASSERT_EQ(loader.read_char(3), 'd');
        ASSERT_EQ(loader.read_char(2), 'c');

        std::cout << "[--OK] WriteReadChar\n";
    }

    void test_read_wrong_memory() { // !!!!!!!!!!
        std::cout << "[RUN-] ReadWrongAddress\n";

        std::cout << "[--OK] ReadWrongAddress\n";
    }

    void test_write_int() {
        std::cout << "[RUN-] ReadWriteSingleInt\n";
        prepare_file();

        loader.write_int(0, 123);
        ASSERT_EQ(loader.read_int(0), 123);

        std::cout << "[--OK] ReadWriteSingleInt\n";
    }

    void test_write_multiple_ints() {
        std::cout << "[RUN-] ReadWriteSingleInt\n";
        prepare_file();
        size_t size = sizeof(unsigned int);

        loader.write_int(0, 123);
        loader.write_int(size, 5660077);
        loader.write_int(size * 2, 788);

        ASSERT_EQ(loader.read_int(0), 123);
        ASSERT_EQ(loader.read_int(size), 5660077);
        ASSERT_EQ(loader.read_int(size * 2), 788);

        std::cout << "[--OK] ReadWriteSingleInt\n";
    }

    void test_int_boundaries() {
        std::cout << "[RUN-] ReadIntBoundaries\n";
        prepare_file();

        loader.write_int(0, 2147483647);
        ASSERT_EQ(loader.read_int(0), 2147483647);

        loader.write_int(0, 4294967295);
        ASSERT_EQ(loader.read_int(0), 4294967295);

        std::cout << "[--OK] ReadIntBoundaries\n";
    }

    void test_different_types() {
        std::cout << "[RUN-] ReadDifferentTypes\n";
        prepare_file();

        loader.write_char(0, '5');
        unsigned int num = loader.read_int(0); // 808464437 --> UB (Ok)
        
        std::cout << "[--OK] ReadDifferentTypes\n";
    }

    void test_constchar() {
        std::cout << "[RUN-] ReadWriteConstChar\n";
        prepare_file();

        loader.write_char(0, '5');
        unsigned int num = loader.read_int(0); // 808464437 --> UB (Ok)
        
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
            std::cout << nums[i] << " " << actual[i] << "\n";
            ASSERT_EQ(nums[i], actual[i]);
        }

        std::cout << "[--OK] ReadWriteFREEBLOCKS\n";
    }

    void test_superblock() {
        std::cout << "[RUN-] ReadWriteSUPERBLOCK\n";
        prepare_file();

        std::vector<bool> vec {false, false};
        Superblock superblock_exp = Superblock("linear", 1000, 10, 100, 52, 52, 30, 5, 50, vec);
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
        // check free blocks


        std::cout << "[--OK] ReadWriteSUPERBLOCK\n";
    }
};


int main(int argc, char** argv) {
    LoaderTest test;
    test.run_all_tests();
}
