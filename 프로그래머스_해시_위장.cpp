#include <string>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

bool solution(vector<vector<string>> clothes) {
    int answer = 1;
    map<string, int> myClo;
    map<string, int>::iterator p;

    for (int i = 0; i < clothes.size(); i++) {
        p = myClo.find(clothes[i][1]);
        if (p != myClo.end()) {
            int count = p->second + 1;
            myClo.erase(p);
            myClo.insert(pair<string, int>(clothes[i][1], count));
        }
        else {
            myClo.insert(pair<string, int>(clothes[i][1], 2)); // 입고 안입고 2가지 경우
        }
    }

    int size = myClo.size();

    for (p = myClo.begin(); p != myClo.end(); p++) {

        answer = answer * p->second;
    }

    answer -= 1;
    return answer;
}

int main() {
    vector<vector<string>> vec = { {"crowmask", "face" }, { "bluesunglasses", "face" }, { "smoky_makeup", "face" }
    };
    bool answer = "";
    answer = solution(vec);
    return 0;
}