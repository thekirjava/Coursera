#include "descriptions.h"
#include "requests.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in ("input.json");
    ofstream out ("output.json");
    const auto input_doc = Json::Load(cin);
    const auto &input_map = input_doc.GetRoot().AsMap();

    const TransportCatalog db(
            Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
            input_map.at("routing_settings").AsMap(),
            input_map.at("render_settings").AsMap()
    );

    Json::PrintValue(
            Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
            cout
    );
    cout << endl;

    return 0;
}
