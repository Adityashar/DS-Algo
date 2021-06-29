/*

On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.
Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Input：stations = [3,6,12,19,33,44,67,72,89,95]，K = 2
Output：14.00

*/


class Solution {
public:

    bool getStations(double dist, vector<int> &s, int k) {
        int cnt = 0;

        for (int i = 1; i < s.size(); i++) {
            cnt += (ceil((s[i] - s[i - 1]) / dist)) - 1;
            // cnt += ((s[i]-s[i-1])/dist + (fmod(s[i]-s[i-1], dist) != 0)) -1;
        }
        cout << cnt << " ";
        return cnt <= k;
    }

    double minmaxGasDist(vector<int> &stations, int k) {
        double ans = 0;
        int n = stations.size();
        double low = 0, high = stations[n - 1] - stations[0], mid;

        while (high - low >= 0.000001) {
            mid = (high - low) / 2.0 + low;

            if (getStations(mid, stations, k)) {
                ans = mid;
                // cout<<ans<<" ";
                high = mid;
            }
            else {
                low = mid;
            }
        }

        return ans;
    }
};