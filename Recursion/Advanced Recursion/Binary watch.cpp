/*
401. Binary Watch

A binary watch has 4 LEDs on the top which represent the hours (0-11),
and the 6 LEDs on the bottom represent the minutes (0-59). Each LED represents a zero or one,
with the least significant bit on the right.

Given an integer turnedOn which represents the number of LEDs that are currently on,
return all possible times the watch could represent.
You may return the answer in any order.

The hour must not contain a leading zero.

For example, "01:00" is not valid. It should be "1:00".
The minute must be consist of two digits and may contain a leading zero.

For example, "10:2" is not valid. It should be "10:02"

Input: turnedOn = 1
Output:

["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]

*/


class Solution {
public:
    vector<string> ans;
    vector<int> hours;
    vector<int> mins;

    void DFS(int index, int n, pair<int, int> time) {
        if (n == 0) {
            string temp = to_string(time.first) + (time.second < 10 ? ":0" : ":") + to_string(time.second);
            ans.push_back(temp);
            return;
        }

        for (int i = index; i < hours.size() + mins.size(); i++) {
            if (i < hours.size()) {
                time.first += hours[i];
                if (time.first < 12)
                    DFS(i + 1, n - 1, time);
                time.first -= hours[i];
            }
            else {
                time.second += mins[i - hours.size()];
                if (time.second < 60)
                    DFS(i + 1, n - 1, time);
                time.second -= mins[i - hours.size()];
            }
        }
    }

    vector<string> readBinaryWatch(int turnedOn) {
        hours = {1, 2, 4, 8};
        mins = {1, 2, 4, 8, 16, 32};

        DFS(0, turnedOn, {0, 0});

        return ans;
    }
};