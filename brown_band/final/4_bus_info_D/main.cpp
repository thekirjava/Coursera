#include <iostream>
#include <fstream>
#include "manager.h"

int main() {
    std::ifstream in ("input.txt");
    Database database;
    TransportManager busManager(database);
    std::cout.precision(6);
    //auto ans = busManager.ProcessAll();
    //PrintResults(ans);
    auto ans = busManager.ProcessAllJSON();
    Json::PrintNode(ans);
    return 0;
}
