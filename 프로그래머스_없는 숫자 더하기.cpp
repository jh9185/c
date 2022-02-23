#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>

using namespace std;

int solution(vector<int> numbers) {
    int answer = 0;
    bool check[10] = { false, };

    for (int i = 0; i < numbers.size(); i++) {
        int temp = numbers[i];
        check[temp] = true;
    }

    for (int i = 0; i < 10; i++) {
        if (check[i] == false)
            answer = answer + i;
    }
    return answer;
}

int main() {

    vector<int> id_list = { 1,2,3,4,6,7,8,0 };

    int answer;
    answer = solution(id_list);
    return 0;
}