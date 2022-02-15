#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctime>

using namespace std;

struct car
{
    string time;
    string number;
    bool Inout;
};

struct feeCar
{
    string number;
    int time;
};

vector<int> fee_cal(vector<feeCar> feeCarList, int defalutTime, int defaultFee, int Time, int TimeFee) {
    vector<int> result;
    vector<int> sortNumber;

    int sumTime = 0;
    int sumFee = 0;
    int count = 0;
    float calTime = 0;
    string number;
    int carNumber;
    if (feeCarList.size() == 0)
        return result;

    for (int i = 0; i < feeCarList.size(); i++) {
        sortNumber.push_back(stoi(feeCarList[i].number));
    }

    sort(sortNumber.begin(), sortNumber.end());

    for (int i = 0; i < sortNumber.size(); i++) {
        for (;;) {
            if (sortNumber[i] == stoi(feeCarList[count].number)) {
                sumTime = feeCarList[count].time;
                // 5000 + ⌈(334 - 180) / 10⌉ x 600 = 14600
                if (sumTime < defalutTime) {
                    result.push_back(defaultFee);
                }
                else {
                    calTime = ceil((float)(sumTime - defalutTime) / Time);
                    sumFee = defaultFee + calTime * TimeFee;
                    result.push_back(sumFee);
                }
                feeCarList.erase(feeCarList.begin() + count);
                count = 0;
                break;
            }
            else {
                count++;
            }

        }
        if (feeCarList.size() == 0)
            break;
    }

    return result;
}

void time_cal(time_t time_st, time_t time_end, int& tm_hour, int& tm_min) {
    double     d_diff;
    d_diff = difftime(time_end, time_st);

    tm_hour = d_diff / (60 * 60);
    d_diff = d_diff - (tm_hour * 60 * 60);

    tm_min = d_diff / 60;
}



vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    int defalutTime = fees.at(0);
    int defaultFee = fees.at(1);
    int Time = fees.at(2);
    int TimeFee = fees.at(3);

    vector<feeCar> feeCarList;
    feeCar tempFee;
    vector<car> carInput;
    vector<car> carOutput;
    vector<string> splitString;
    string split;
    car temp;
    int count = 0;
    bool bFind, bListFind = false;

    for (int i = 0; i < records.size(); i++) {
        stringstream ss(records.at(i));

        while (getline(ss, split, ' ')) {
            splitString.push_back(split);
            switch (count % 3) {
            case 0:
                temp.time = split;
                break;
            case 1:
                temp.number = split;
                break;
            case 2:
                if (split == "IN") {
                    carInput.push_back(temp);
                    temp.Inout = true;
                }
                else {
                    temp.Inout = false;
                    carOutput.push_back(temp);
                }
                break;
            }
            count++;
        }//공백 단위로 구분        
    }

    time_t     tm_st;
    time_t     tm_nd;
    int        tm_day, tm_hour, tm_min, tm_sec;
    struct tm  stime;
    struct tm  etime;

    for (;;) {
        temp = carInput[0];
        stime.tm_year = 2022 - 1900;
        stime.tm_mon = 2 - 1;
        stime.tm_mday = 15;
        stime.tm_hour = stoi(temp.time.substr(0, 2));
        stime.tm_min = stoi(temp.time.substr(3, 2));
        stime.tm_sec = 0;
        stime.tm_isdst = 0;

        for (int j = 0; j < carOutput.size(); j++) {
            if (carOutput[j].number == temp.number) {
                bFind = true;
                etime.tm_year = 2022 - 1900;
                etime.tm_mon = 2 - 1;
                etime.tm_mday = 15;
                etime.tm_hour = stoi(carOutput[j].time.substr(0, 2));
                etime.tm_min = stoi(carOutput[j].time.substr(3, 2));
                etime.tm_sec = 0;
                etime.tm_isdst = 0;

                tm_st = mktime(&stime);
                tm_nd = mktime(&etime);

                time_cal(tm_st, tm_nd, tm_hour, tm_min);

                tempFee.number = temp.number;
                tempFee.time = (tm_hour * 60) + tm_min;

                if (feeCarList.size() != 0) {
                    for (int k = 0; k < feeCarList.size(); k++) {
                        if (feeCarList[k].number == temp.number) {
                            feeCarList[k].time += tempFee.time;
                            bListFind = true;
                            break;
                        }
                    }
                    if (bListFind == false)
                        feeCarList.push_back(tempFee);
                }
                else
                    feeCarList.push_back(tempFee);

                bListFind = false;

                carInput.erase(carInput.begin());
                carOutput.erase(carOutput.begin() + j);
                break;
            }
        }

        if (bFind == false) {
            etime.tm_year = 2022 - 1900;
            etime.tm_mon = 2 - 1;
            etime.tm_mday = 15;
            etime.tm_hour = 23;
            etime.tm_min = 59;
            etime.tm_sec = 0;
            etime.tm_isdst = 0;

            tm_st = mktime(&stime);
            tm_nd = mktime(&etime);

            time_cal(tm_st, tm_nd, tm_hour, tm_min);

            tempFee.number = temp.number;
            tempFee.time = (tm_hour * 60) + tm_min;

            if (feeCarList.size() != 0) {
                for (int k = 0; k < feeCarList.size(); k++) {
                    if (feeCarList[k].number == temp.number) {
                        feeCarList[k].time += tempFee.time;
                        bListFind = true;
                        break;
                    }
                }
                if (bListFind == false)
                    feeCarList.push_back(tempFee);
            }
            else
                feeCarList.push_back(tempFee);

            bListFind = false;
            carInput.erase(carInput.begin());
        }

        bFind = false;

        if (carInput.size() == 0)
            break;
    }

    answer = fee_cal(feeCarList, defalutTime, defaultFee, Time, TimeFee);

    return answer;
}

int main()
{
    vector<int> fees = { 180, 5000, 10, 600 };
    vector<string> records = { "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT", "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN", "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT" };
    vector<int> answer = solution(fees, records);
    return answer.at(0);
}
