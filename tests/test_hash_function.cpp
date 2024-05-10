#include <iostream>



uint32_t hash_function(const std::string& path) {
    uint32_t hash = 5381;
    for (char c : path) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

std::string decode_hash_value(uint32_t hash) {
    std::string path;
    while (hash != 0) {
        char c = (hash & 0xFF);
        path.push_back(c);
        hash >>= 8;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    std::string path = "/home/user/file.txt";
    uint32_t hash = hash_function(path);
    std::string decoded_path = decode_hash_value(hash);
    std::cout << decoded_path << std::endl; // Output: /home/user/file.txt

}