#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;


int main() {
    fstream file;
    file.open("test.bin", ios_base::out | ios_base::binary);
    if(!file.is_open())
    {
        cout<<"Unable to open the file\n";
        return 0;
    }
    string myStr = "This string is written to the binary file.";
    // Example 1:
    // for(int i=0;i<myStr.size();i++)
    // {
    //     file.put(myStr[i]);
    // }

    // Example 2:
    // myStruct obj;
    // obj.name = "Mohtashim Nawaz";
    // obj.gender = "male";
 
    // file.write((char*)&obj, sizeof(obj));

    file << myStr;
    file.close();
    return 0;
}