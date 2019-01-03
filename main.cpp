#include <iostream>

using std::cout;
using std::endl;


void runTest() {
    cout << "[" << __FILE__ << "] (" << __LINE__ << ") - [" << __FUNCTION__ << "]" << endl;
}

int main() {
    runTest();
    return 0;
}
