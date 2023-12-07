#include <cstddef>
#include "basic_vector.h"

using namespace std;

int main(int argc, char *argv[]) {
    basic_vector<string> bv(10);

    bv.push_back("test1");
    bv.push_back("test2");
    bv.push_back("test3");
    bv.push_back("test4");
    bv.push_back("test5");
    bv.push_back("test6");
    bv.push_back("test7");
    bv.push_back("test8");

    cout << "Initial basic_vector: \n" <<  bv;

    

    return 0;
}