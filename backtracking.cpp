#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<numeric>
#include<string.h>
#include<math.h>
#include<unordered_map>

using namespace std;

void print_1D_vector(vector<int>& v) {
    for(int i=0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void print_2D_vector(vector<vector<int>>& v) {
    for(int i=0; i<v.size(); ++i) {
        cout << '[' << " ";
        for(int j=0; j<v[i].size(); ++j) {
            cout << v[i][j] << " ";
        } 
        cout << ']' << "  ";
    }
    cout << endl;
}

//-------------------------------------------------------------------------------------------------------------------------//

// Count inversions
long merge(vector<int>& arr, vector<int>& temp, int start, int mid, int end) {
    int i=start, j=mid+1, k=start;
    long c=0;
    while(i<=mid && j<=end) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            c += mid - i + 1;
        }
    }
    while(i<=mid)
        temp[k++] = arr[i++];
    while(j<=end)
        temp[k++] = arr[j++];
    while(start <= end) {
        arr[start] = temp[start];
        ++start;
    }
    return c;
}

long merge_sort(vector<int>& arr, vector<int>& temp, int start, int end) {
    if(start >= end) return 0;
    int mid = start + (end - start) / 2;
    long c = 0;
    c += merge_sort(arr, temp, start, mid);
    c += merge_sort(arr, temp, mid+1, end);
    c += merge(arr, temp, start, mid, end);
    return c;
}

//-------------------------------------------------------------------------------------------------------------------------//

// In place merge sort
void merge_in_place(vector<int>& v, int start, int mid, int end) {
    int total_len = end - start + 1;
    int gap = total_len/2 + total_len%2;
    while(gap > 0) {
        int i=start, j=start+gap;
        while(j<=end) {
            if(v[i] > v[j]) swap(v[i], v[j]);
            ++i, ++j;
        }
        gap = gap <= 1 ? 0:(gap/2) + (gap%2);
    }
}

void merge_sort(vector<int>& v, int start, int end) {
    if(start >= end) return;
    int mid = (start+end) >> 1;
    merge_sort(v, start, mid);
    merge_sort(v, mid+1, end);
    merge_in_place(v, start, mid, end);
}

//-------------------------------------------------------------------------------------------------------------------------//

// Maximun subarray
int max_sub_array(vector<int>& v, int start, int end) {
    if(start == end) return v[start];
    int max_left_border_sum = INT_MIN;
    int max_right_border_sum = INT_MIN;
    int mid = start + ((end - start) >> 1);
    int max_left_sum = max_sub_array(v, start, mid);
    int max_right_sum = max_sub_array(v, mid+1, end);

    int left_border_sum = 0, right_border_sum = 0;
    for(int i=mid; i>=start; i--) {
        left_border_sum += v[i];
        if(left_border_sum > max_left_border_sum)
            max_left_border_sum = left_border_sum;
    }
    for(int i=mid+1; i<=end; i++) {
        right_border_sum += v[i];
        if(right_border_sum > max_right_border_sum)
            max_right_border_sum = right_border_sum;
    }
    int cross_border_sum = max_left_border_sum + max_right_border_sum;
    return max(cross_border_sum, max(max_right_sum, max_left_sum));
}

//-------------------------------------------------------------------------------------------------------------------------//

// Combination sum 1&2
void combination_sum_1(vector<int>& candidates, int target, vector<int>& v, vector<vector<int>>& ans, int index=0) {
    if(target == 0) {
        ans.push_back(v);
        return;
    }
    if(target < 0) return;
    for(int i=index; i<candidates.size(); i++) {
        v.push_back(candidates[i]);
        combination_sum_1(candidates, target-candidates[i], v, ans, i);
        v.pop_back();
    }
}
void combination_sum_2(vector<int>& candidates, int target, vector<int>& v, vector<vector<int>>& ans, int index=0) {
    if(target == 0) {
        ans.push_back(v);
        return;
    }
    if(target < 0) return;
    for(int i=index; i<candidates.size(); i++) {
        if(i > index && candidates[i] == candidates[i-1]) continue;
        v.push_back(candidates[i]);
        combination_sum_2(candidates, target-candidates[i], v, ans, i+1);
        v.pop_back();
    }
}

//-------------------------------------------------------------------------------------------------------------------------//

// Permutations - II
void unique_permutation(vector<int>& nums, vector<vector<int>>& ans, int start=0) {
    if(start == nums.size()) {
        ans.push_back(nums);
        return;
    }
    unordered_map<int, bool>visited;
    for(int i=start; i<nums.size(); i++) {
        if(visited.find(nums[i]) != visited.end()) continue;
        visited[nums[i]] = true;
        swap(nums[i], nums[start]);
        unique_permutation(nums, ans, start+1);
        swap(nums[i], nums[start]);
    }
}

//-------------------------------------------------------------------------------------------------------------------------//

// Beautiful arrangements
void solve(vector<int>&v, int& n, int& ans, int curr_num) {
    if(curr_num == n+1) {
        for(int i=1; i<=n; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
        ++ans;
        return;
    }
    for(int i=1; i<=n; ++i) {
        if(v[i] == 0 && (curr_num % i == 0 || i % curr_num == 0)) {
            v[i] = curr_num;
            solve(v, n, ans, curr_num+1);
            v[i] = 0;
        }
    }
}

int count_arrangements(int n) {
    vector<int>v (n+1);
    int ans=0;
    solve(v, n, ans, 1);
    return ans;
}

//-------------------------------------------------------------------------------------------------------------------------//

//Distribute repeating integers
bool solve(vector<int>& counts, vector<int>& quantity, int ith_customer=0) {
    if(ith_customer == quantity.size())
        return true;
    for(int i=0; i<counts.size(); ++i) {
        if(counts[i] >= quantity[ith_customer]) {
            counts[i] -= quantity[ith_customer];
            if(solve(counts, quantity, ith_customer+1)) 
                return true;
            counts[i] += quantity[ith_customer];
        }
    }
    return false;
}

bool can_distribute(vector<int>& nums, vector<int>& quantity) {
    unordered_map<int, int> count_map;
    for(auto num:nums)
        count_map[num]++;
    vector<int> counts;
    for(auto it:count_map)
        counts.push_back(it.second);
    sort(quantity.rbegin(), quantity.rend());
    return solve(counts, quantity);
}

int main() {

    // Count inversions
    // vector<int> arr{8,7,5,3,4,1};
    // vector<int> temp(arr.size(), 0);
    // int start = 0;
    // int end = arr.size()-1;
    // long ans = merge_sort(arr, temp, start, end);
    // cout << ans << endl;

//-------------------------------------------------------------------------------------------------------------------------//

    // In place merge sort
    // vector<int> v{12,11,13,6,7,5};
    // merge_sort(v, 0, v.size()-1);
    // print_1D_vector(v);

//-------------------------------------------------------------------------------------------------------------------------//

    // Maximun subarray
    // vector<int> v{-4,5,-1,2,-4,6};
    // cout << max_sub_array(v, 0, v.size()-1) << endl;

//-------------------------------------------------------------------------------------------------------------------------//

    // Combination sum 1&2
    // vector<int> candidates{2,5,2,1,2};
    // sort(candidates.begin(), candidates.end());
    // int target = 5;
    // vector<int> v;
    // vector<vector<int>> ans;
    // combination_sum_2(candidates, target, v, ans);
    // print_2D_vector(ans);

//-------------------------------------------------------------------------------------------------------------------------//

    // Permutations - II
    // vector<int> nums{1,7,3,7};
    // vector<vector<int>> ans;
    // unique_permutation(nums, ans);
    // print_2D_vector(ans);

//-------------------------------------------------------------------------------------------------------------------------//

    // Beautiful arrangements
    // int n;
    // cin >> n;
    // cout << count_arrangements(n) << endl;

//-------------------------------------------------------------------------------------------------------------------------//

    //Distribute repeating integers
    vector<int> nums{1,2,3,3};
    vector<int> quantity{2};
    if(can_distribute(nums, quantity)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }

    return 0;
}