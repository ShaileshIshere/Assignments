#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int sum_of_max_window_of_size_K(vector<int> &nums, int k ) {
    deque<int> dq1, dq2;
    int ans = 0;
    for(int i=0; i<k; ++i) {
        while(!dq1.empty() && nums[i] >= nums[dq1.back()]) {
            dq1.pop_back();
        }
        while(!dq2.empty() && nums[i] <= nums[dq2.back()]) {
            dq2.pop_back();
        }
        dq1.push_back(i);
        dq2.push_back(i);
    }
    ans += nums[dq1.front()] + nums[dq2.front()];

    for(int i=k; i<nums.size(); ++i) {
        if(!dq1.empty() && i-dq1.front() >= k) {
            dq1.pop_front();
        }
        if(!dq2.empty() && i-dq2.front() >= k) {
            dq2.pop_front();
        }
        while(!dq1.empty() && nums[i] >= nums[dq1.back()]) {
            dq1.pop_back();
        }
        while(!dq2.empty() && nums[i] <= nums[dq2.back()]) {
            dq2.pop_back();
        }
        dq1.push_back(i);
        dq2.push_back(i);
        ans += nums[dq1.front()] + nums[dq2.front()];
    }

    return ans;
}

int main() {

    int n, k;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i) {
        cin >> nums[i];
    }
    cout << "enter the size of window : ";
    cin >> k;
    cout << "sum of min or max elements of all size of " << k << " is : " << sum_of_max_window_of_size_K(nums, k) << endl;

    return 0;
}