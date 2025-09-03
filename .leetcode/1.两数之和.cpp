/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#include<bits/stdc++.h>
using namespace std;
int main(){
    return 0;
}
// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n=nums.size();
        map<int,int> hash;
        auto iter=hash.end();
        for(int i=0;i<n;i++){
            iter=hash.find(target-nums[i]);
            if(iter!=hash.end()){
                return{hash[target-nums[i]],i};
            }
            else hash[nums[i]]=i;
        }
        return{};
    }
};
// @lc code=end

