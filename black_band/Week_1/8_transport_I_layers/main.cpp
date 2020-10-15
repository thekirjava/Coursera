#include <iostream>
#include <fstream>
#include "manager.h"
#include "json.h"
int main() {
    std::ifstream in("input.json");
    std::ofstream out("output.json");
    TransportDatabase::DatabaseManager dm;
    std::cout.precision(6);
    //auto ans = busManager.ProcessAll();
    //PrintResults(ans);
    auto ans = dm.processAllJsonRequests();
    Json::PrintNode(ans);
    return 0;
}
