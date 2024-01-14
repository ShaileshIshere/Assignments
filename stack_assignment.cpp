#include<iostream>
#include<stack>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

int count_reverse(string s) {
    if(s.size() & 1) 
        return -1;
    int ans = 0;
    stack<char> st;
    for(char ch : s) {
        if(ch == '{')
            st.push(ch);
        else {
            if(!st.empty() && st.top() == '{')
                st.pop();
            else 
                st.push(ch);
        }
    }
    while(!st.empty()) {
        char a = st.top(); st.pop();
        char b = st.top(); st.pop();
        if(a == b) 
            ans += 1;
        else 
            ans += 2;
    }
    return ans;
}

    string removeDuplicates(string s) {
        stack<char> st;
        for(auto ch : s) {
            if(!st.empty() && st.top() == ch) {
                st.pop();
            }
            else {
                st.push(ch);
            }
        }
        string ans;
        while(!st.empty()) {
            ans += st.top();
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    int celebrity(vector<vector<int> >& M, int n) 
    {
        stack<char> st;
        for(int i=0; i<n; ++i) {
            st.push(i);
        }
        while(st.size() != 1) {
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            if(M[a][b]) {
                st.push(b);
            }
            else {
                st.push(a);
            }
        }
        int might_be_celebrity = st.top(); st.pop();
        for(int i=0; i<n; ++i) {
            if(M[might_be_celebrity][i] != 0 && i != might_be_celebrity) {
                return -1;
            }
        }
        for(int i=0; i<n; ++i) {
            if(M[i][might_be_celebrity] == 0 && i != might_be_celebrity) {
                return -1;
            }
        }
        return might_be_celebrity;
    }

class Node {
public:
    int val;
    Node* next;

    Node() : next(nullptr) {}
    Node(int data) : val(data), next(nullptr) {}
};
void print_LL(Node* head) {
    Node* temp = head;
    while(temp != nullptr) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << "NULL";
    cout << endl;
}
void insert_at_head(Node* &head, int data) {
    if(head == nullptr) {
        Node* new_node = new Node(data);
        head = new_node;
    }
    else {
        Node* new_node = new Node(data);
        new_node->next = head;
        head = new_node;
    }
}
vector<int> next_larger_nodes(Node* head) {
    vector<int> ll;
    while(head) {
        ll.push_back(head->val);
        head = head->next;
    }
    stack<int> st;
    for(int i=0; i<ll.size(); ++i) {
        while(!st.empty() && ll[i] > ll[st.top()]) {
            int kids = st.top();
            st.pop();
            ll[kids] = ll[i];
        }
        st.push(i);
    }
    while(!st.empty()) {
        ll[st.top()] = 0; st.pop();
    }
    return ll;
}

    bool isValid(string s) {
        if(s[0] != 'a') return false;
        // create a stack to store characters
        stack<char> st;
        for(char ch : s) {
            if(ch == 'a')
                st.push(ch);
            else if(ch == 'b') {
                if(!st.empty() && st.top() == 'a')
                    st.push(ch);
                else 
                    return false;
            }
            else {
                // if we are here that means the current character we're gonna insert is c
                if(!st.empty() && st.top() == 'b') {
                    st.pop();
                    if(!st.empty() && st.top() == 'a')
                        st.pop();
                    else
                        return false;
                }
                else 
                    return false;
            }
        }
        return st.empty();
    }

    string decodeString(string s) {
        stack<string> st;
        for(auto ch : s) {
            if(ch == ']') {
                string stringToRepeat = "";
                while(!st.empty() && st.top() != "[") {
                    string top = st.top();
                    stringToRepeat += top;
                    st.pop();
                }

                // we're poping this "[" here
                st.pop();
                string numericTimes = "";
                while(!st.empty() && isdigit(st.top()[0])) {
                    numericTimes += st.top();
                    st.pop();
                }

                // if we've a two digit no. so stack would return 10 -> 01 that's why we're reversing it here
                reverse(numericTimes.begin(), numericTimes.end());

                // we're converring string to integer here
                int n = stoi(numericTimes);

                // now we're concatinating/making a full fleged string here
                string currentDecode = "";
                while(n--) {
                    currentDecode += stringToRepeat;
                }
                st.push(currentDecode);
            }
            else {
                string temp(1, ch);
                st.push(temp);
            }
        }
        string ans;
        while(!st.empty()) {
            ans += st.top();
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    void buildAns(stack<string> &s, string &ans) {
        if(s.empty()) return;
        string minPath = s.top(); s.pop();
        buildAns(s, ans);
        ans += minPath;
    }
    string simplifyPath(string path) {
        stack<string> s;
        int i=0;
        while(i<path.size()) {
            int start=i;
            int end=i+1;
            while(end<path.size() && path[end] != '/') {
                ++end;
            }
            string minPath = path.substr(start, end-start);
            i=end;
            if(minPath == "/" || minPath == "/.") {
                continue;
            }
            if(minPath != "/..") {
                s.push(minPath);
            }
            else if(!s.empty()) {
                s.pop();
            }
        }
        string ans = s.empty() ? "/" : "";
        buildAns(s, ans);
        return ans;
    }

    class Car {
    public:
        int pos;
        int speed;
        Car(int p, int s) : pos(p), speed(s) {}
    };
    static bool myComp(Car &a, Car &b) {
        return a.pos < b.pos;
    }
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<Car> cars;
        for(int i=0; i<position.size(); ++i) {
            Car car(position[i], speed[i]);
            cars.push_back(car);
        }
        sort(cars.begin(), cars.end(), myComp);
        stack<float> st;
        for(auto car : cars) {
            float time = (target - car.pos) / ((float) car.speed);
            while(!st.empty() && time >= st.top()) {
                st.pop();
            }
            cout << " -> " << time << endl;
            st.push(time);
        }
        cout << "these are the values at stack :" << endl;
        int count=0;
        while(!st.empty()) {
            count++;
            cout << st.top() << endl;
            st.pop();
        }
        return count;
    }

    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        vector<double> answer(cars.size(), -1);
        stack<int> st;
        for(int i=cars.size()-1; i>=0; --i) {
            while(!st.empty() && cars[st.top()][1] >= cars[i][1]) {
                st.pop();
            }
            while(!st.empty()) {
                double colTime = (double) (cars[st.top()][0] - cars[i][0]) / (cars[i][1] - cars[st.top()][1]);
                if(answer[st.top()] == -1 || colTime <= answer[st.top()]) {
                    answer[i] = colTime;
                    break;
                }
                st.pop();
            }
            st.push(i);
        }
        return answer;
    }

int main() {

    // minimum bracket reversal
    // string s;
    // cin >> s;
    // cout << "the number of bracket reversal is : " << count_reverse(s) << endl;

    // remove all adjacents in string
    // string s;
    // cin >> s;
    // cout << removeDuplicates(s) << endl;

    // celebrity problem
    // int n = 5;
    // vector<vector<int>> M = {{1,0,1,0,0}, {0,0,1,0,1}, {0,0,0,0,0}, {0,0,1,1,0}, {1,0,1,0,0}};
    // cout << "the celebrity here is : " << celebrity(M, n) << endl;

    // next greater node in linked list (by stack)
    // Node* head = nullptr;
    // insert_at_head(head, 1);
    // insert_at_head(head, 4);
    // insert_at_head(head, 3);
    // insert_at_head(head, 6);
    // insert_at_head(head, 9);
    // insert_at_head(head, 2);
    // insert_at_head(head, 5);
    // print_LL(head);
    // vector<int> ans = next_larger_nodes(head);
    // for(int i=0; i<ans.size(); ++i) {
    //     cout << ans[i] << " ";
    // }
    // cout << endl;
    
    // LC - 1003
    // string s;
    // cin >> s;
    // if(isValid(s)) {
    //     cout << "yes it is a valid string :)" << endl;
    // }
    // else {
    //     cout << "no it is not a valid string :(" << endl;
    // }

    // decode string
    // string s;
    // cin >> s;
    // cout << decodeString(s) << endl;

    // simplify path
    // string s;
    // cin >> s;
    // cout << simplifyPath(s) << endl;

    // car fleet - I
    // vector<int> position{6,4,1,8,10,2};
    // vector<int> speed{2,3,3,4,4,2};
    // int target = 20;
    // cout << "the no. of car fleet is : " << carFleet(target, position, speed) << endl;

    // car fleet - II
    vector<vector<int>> cars = {{5,3}, {6,2}, {7,1}, {8,2}};
    vector<double> ans = getCollisionTimes(cars);
    cout << "the timings of each car's collision is :-" << endl;
    for(int i=0; i<ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}