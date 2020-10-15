#include <iostream>
#include "manager.h"


int main() {
    Database database;
    BusManager busManager(database);
    std::cout.precision(6);
    auto ans = busManager.ProcessAll();
    PrintResults(ans);
    return 0;
}
