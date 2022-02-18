#include <string>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";

    map<string, int> myMap;
    map<string, int>::iterator p;

    for (int i = 0; i < participant.size(); i++) {
        p = myMap.find(participant[i]);
        if (p != myMap.end()) {
            int count = p->second + 1;
            myMap.erase(p);
            myMap.insert(pair<string, int>(participant[i], count));
        }
        else {
            myMap.insert(pair<string, int>(participant[i], 1));
        }
    }

    for (int i = 0; i < completion.size(); i++) {
        p = myMap.find(completion[i]); //iterator ¹ÝÈ¯

        if (p == myMap.end())
            break;
        else {
            if (p->second == 1) {
                myMap.erase(p);
            }
            else {
                string parti = p->first;
                int count = p->second - 1;
                myMap.erase(p);
                myMap.insert(pair<string, int>(parti, count));
            }

        }
    }

    p = myMap.begin();
    answer = p->first;
    return answer;
}

int main() {
    vector<string> vec = { "mislav", "stanko", "mislav", "ana" };
    vector<string> com = { "eden", "kiki" };
    string answer = "";
    answer = solution(vec, com);
    return 0;
}