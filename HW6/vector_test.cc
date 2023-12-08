#include <cstddef>
#include "basic_vector.h"

using namespace std;

int main(int argc, char *argv[]) {
    basic_vector<string> bv(10);

    for (int i=0; i < 58800; i++) {
        bv.push_back("test " + std::to_string(i));
    }

    cout << "Initial basic_vector: \n" <<  bv;

    

    return 0;
}