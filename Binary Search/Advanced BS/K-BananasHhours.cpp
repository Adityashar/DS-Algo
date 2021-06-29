"""
Koko loves to eat bananas.  There are N piles of bananas, the i-th pile has piles[i] bananas.  The guards have gone and will come back in H hours.

Koko can decide her bananas-per-hour eating speed of K.  Each hour, she chooses some pile of bananas, and eats K bananas from that pile.  If the pile has less than K bananas, she eats all of them instead, and wont eat any more bananas during this hour.

Koko likes to eat slowly, but still wants to finish eating all the bananas before the guards come back.

Return the minimum integer K such that she can eat all the bananas within H hours.

 

Example 1:

Input: piles = [3,6,7,11], H = 8
Output: 4
"""

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int n=piles.size();
        sort(piles.begin(), piles.end());
        
        if(n == H) return piles[n-1];
        
        int high = piles[n-1], low =1, mid = (high-low)/2 + low;
        int ans = -1;
        
        while(low <= high){
            
            int cnt = 0;
            for(int p: piles) cnt += (p + mid - 1) / mid;
            
            if(cnt <= H){
                ans = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
            
            mid = (high-low)/2 + low;
        }
        
        return ans;
    }
};