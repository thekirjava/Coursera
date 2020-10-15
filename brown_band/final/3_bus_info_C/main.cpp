#include <iostream>
#include <fstream>
#include "manager.h"

int main() {
    std::ifstream in ("input.txt");
    Database database;
    BusManager busManager(database);
    std::cout.precision(6);
    auto ans = busManager.ProcessAll();
    PrintResults(ans);
    return 0;
}
