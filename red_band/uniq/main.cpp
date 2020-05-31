#include <string>
#include <vector>

using namespace std;
#define UNIQ_LINE_CONT_2(lineno) uniq##lineno
#define UNIQ_LINE_CONT(lineno)  UNIQ_LINE_CONT_2(lineno)
#define UNIQ_ID UNIQ_LINE_CONT(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}