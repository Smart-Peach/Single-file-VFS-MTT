#pragma once

#include <bitset>
#include <vector>

const int SIZEOF_BOOT_SECTOR = 1024;
const int SIZEOF_SUPERBLOCK = 1024;
static const size_t BLOCKS_AMOUNT = 10000;

typedef std::string str_t;
typedef std::bitset<BLOCKS_AMOUNT> bitset_t;
typedef bool bit;
typedef std::vector<size_t> vector_size_t;