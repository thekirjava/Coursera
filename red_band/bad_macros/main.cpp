#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        int x = 5;
        PRINT_VALUES(output, x-2, "x");
        ASSERT_EQUAL(output.str(), "3\nx\n");
    }, "PRINT_VALUES usage example");
}