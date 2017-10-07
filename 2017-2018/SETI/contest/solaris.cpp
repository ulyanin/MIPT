//
// Created by ulyanin on 07.10.17.
//

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

static char * ReadAllBytes(const char * filename, int * read)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    // What happens if the OS supports really big files.
    // It may be larger than 32 bits?
    // This will silently truncate the value/
    int length = pos;

    // Manuall memory management.
    // Not a good idea use a container/.
    char *pChars = new char[length];
    ifs.seekg(0, ios::beg);
    ifs.read(pChars, length);

    // No need to manually close.
    // When the stream goes out of scope it will close the file
    // automatically. Unless you are checking the close for errors
    // let the destructor do it.
    ifs.close();
    *read = length;
    return pChars;
}

int main()
{
    freopen("solaris.dat", "r", stdin);
    freopen("solaris.ans", "w", stdout);
    while (1) {
        int c1 = getchar();
        if (c1 == -1) {
            return 0;
        }
        int c2 = getchar();
        if (c2 == -1) {
            return 0;
        }
        putchar(c2);
        putchar(c1);
    }

}
