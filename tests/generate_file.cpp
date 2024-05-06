#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ofstream ofs("tests/test-file.bin", std::ios::binary | std::ios::out);

    for(size_t i = 0; i < 1073741824; i++)
    {
        ofs.put(0);
    }
}