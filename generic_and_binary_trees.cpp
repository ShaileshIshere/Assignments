#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<unordered_map>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int data) : left(nullptr), right(nullptr), data(data) {}
};

Node* create_tree() {
    int data;
    cout << "enter the node : " << endl;
    cin >> data;
    if(data == 0) 
        return nullptr;
    Node* root = new Node(data);
    cout << "enter the element you wanna insert in the left part of the tree" << endl;
    root->left = create_tree();
    cout << "enter the element you wanna insert in the right part of the tree" << endl;
    root->right = create_tree();
    return root;
}

void level_order_traversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty()) {
        Node* front = q.front();
        q.pop();
        if(!front) {
            cout << endl;
            if(!q.empty())
                q.push(nullptr);
        }
        else {
            cout << front->data << " ";
            if(front->left)
                q.push(front->left);
            if(front->right)
                q.push(front->right);
        }
    }
}

// optimal solution for fastest way to calculate diameter
static int diameter = 0;
int diameter_of_binary_tree(Node* root) {
    if(!root)
        return 0;
    int left_height = diameter_of_binary_tree(root->left);
    int right_height = diameter_of_binary_tree(root->right); 
    int current_diameter = left_height + right_height;
    diameter = max(current_diameter, diameter);
    return max(left_height, right_height)+1;
}
int solution(Node* root) {
    diameter_of_binary_tree(root);
    return diameter;
}

// balanced binary tree optimal solution
int balanced_binary_tree(Node* root, bool &isBalanced) {
    if(!root)
        return 0;
    int left_height = balanced_binary_tree(root->left, isBalanced);
    int right_height = balanced_binary_tree(root->right, isBalanced);
    if(isBalanced && (left_height - right_height) > 1) {
        isBalanced = false;
    }
    return max(left_height, right_height) + 1;
}

// symmetric/mirror trees
bool is_mirror(Node* p, Node* q) {
    if(!p && !q)
        return true;
    if(p && q)
        return (p->data == q->data) && is_mirror(p->left, q->right) && is_mirror(p->right, q->left);
    return false;
}

// diagonal traversal of a binary tree
vector<int> diagonal(Node* root) {
    vector<int> ans;
    if(!root)
        return ans;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* temp = q.front(); q.pop();
        while(temp) {
            ans.push_back(temp->data);
            if(temp->left)
                q.push(temp->left);
            temp = temp->right;
        }
    }
    return ans;
}

// vertical level order traversal of a binary tree
vector<vector<int>> vertical_traversal(Node* root) {
    vector<vector<int>> ans;
    queue<pair<Node*, pair<int, int>>> q;
    q.push({root, {0,0}});
    map<int, map<int, multiset<int>>> mp;
    while(!q.empty()) {
        // auto front = q.front(); q.pop();
        pair<Node*, pair<int, int>> front = q.front(); q.pop();
        Node* &node = front.first;
        // auto &coordinate = front.second;
        pair<int, int> &coordinate = front.second;
        int &row = coordinate.first;
        int &col = coordinate.second;
        mp[col][row].insert(node->data);
        if(node->left)
            q.push({node->left, {row+1, col-1}});
        if(node->right)
            q.push({node->right, {row+1, col+1}});
    }
    for(auto it:mp) {
        // auto &colMap = it.second;
        map<int, multiset<int>> &colMap = it.second;
        vector<int> vLine;
        for(auto colMapIt:colMap) {
            // auto &mset = colMapIt.second;
            multiset<int> &mset = colMapIt.second;
            vLine.insert(vLine.end(), mset.begin(), mset.end());
        }
        ans.push_back(vLine);
    }
    return ans;
}

// zig zag level order traversal
vector<vector<int>> zigzag_level_order(Node* root) {
    vector<vector<int>> ans;
    if(!root)
        return ans;
    bool left_to_right_direction = true;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int width = q.size();
        vector<int> oneLevel(width);
        for(int i=0; i<width; ++i) {
            Node* front = q.front(); q.pop();
            int index = left_to_right_direction ? i : width - i - 1;
            oneLevel[index] = front->data;
            if(front->left)
                q.push(front->left);
            if(front->right)
                q.push(front->right);
        }
        left_to_right_direction = !left_to_right_direction;
        ans.push_back(oneLevel);
    }
    return ans;
}

// path sum III
// static int ans = 0;
void path_from_one_node(Node* root, long long sum, int &ans) {
    if(!root)
        return;
    if(sum == root->data)
        ++ans;
    path_from_one_node(root->left, sum-root->data, ans);
    path_from_one_node(root->right, sum-root->data, ans);
}
int path_sum_3(Node* root, long long target_sum, int &ans) {
    if(root) {
        path_from_one_node(root, target_sum, ans);
        path_sum_3(root->left, target_sum, ans);
        path_sum_3(root->right, target_sum, ans);
    }
    return ans;
}

// transform to a sum tree
int sum_tree(Node* root) {
    if(!root)
        return 0;
    if(!root->left && !root->right) {
        int temp = root->data;
        root->data = 0;
        return temp;
    }
    int left_sum = sum_tree(root->left);
    int right_sum = sum_tree(root->right);
    int temp = root->data;
    root->data = left_sum + right_sum;
    return root->data+temp;
}

// max sum of non-adjacent nodes
pair<int, int> get_max_sum(Node* root) {
    if(!root)
        return {0,0};
    auto left = get_max_sum(root->left);
    auto right = get_max_sum(root->right);
    
    // sum including node
    int sum_1 = root->data + left.second  + right.second;

    // sum excluding node
    int sum_2 = max(left.first, left.second) + max(right.first, right.second);
    return {sum_1, sum_2}; 
}

// sum of the longest bloodline of the tree
pair<int, int> height(Node* root) {
    if(!root)
        return {0,0};
    auto left_height = height(root->left);
    auto right_height = height(root->right);
    int sum = root->data;
    if(left_height.first == right_height.first) {
        sum += left_height.second > right_height.second ? left_height.second : right_height.second;
    }        
    else if(left_height.first > right_height.first) {
        sum += left_height.second;
    }
    else { 
        sum += right_height.second;
    }
    return {max(left_height.first, right_height.first) + 1, sum};
}

// morris traversal
    vector<int> morris_Traversal(Node* root) {
        vector<int> ans;
        Node* curr = root;
        while(curr) {
            // left node is null then visit it and go right
            if(!curr->left) {
                ans.push_back(curr->data);
                curr = curr->right;
            }
            // left node isn't null
            else {
                // find inorder predecessor
                Node* pred = curr->left;
                while(pred->right != curr && pred->right)
                    pred = pred->right;
                // if pred's right node is null then go left after establishing link from pred to curr
                if(!pred->right) {
                    pred->right = curr;
                    curr = curr->left;
                }
                else {
                    // left is already visited go after visiting curr node while removing the link
                    pred->right = nullptr;
                    ans.push_back(curr->data);
                    curr = curr->right;
                }
            }
        }
        return ans;
    }

    Node* parent_mapping(Node* root, unordered_map<Node*, Node*> &parentMap, int target) {
        queue<Node*> q;
        Node* targetNode = 0;
        q.push(root);
        parentMap[root] = 0;
        while(!q.empty()) {
            Node* front = q.front(); q.pop();
            if(front->data == target) 
                targetNode = front;
            if(front->left) {
                q.push(front->left);
                parentMap[front->left] = front;
            }
            if(front->right) {
                q.push(front->right);
                parentMap[front->right] = front;
            }
        }
        return targetNode;
    }
    int BurnTheTree(Node* targetNode, unordered_map<Node*, Node*> &parentMap) {
        unordered_map<Node*, bool> isBurnt;
        queue<Node*> q;
        int T = 0;
        q.push(targetNode);
        isBurnt[targetNode] = 1;
        while(!q.empty()) {
            int size = q.size();
            bool isFireSpreaded = 0;
            for(int i=0; i<size; ++i) {
                Node* front = q.front(); q.pop();
                if(front->left && !isBurnt[front->left]) {
                    q.push(front->left);
                    isBurnt[front->left] = 1;
                    isFireSpreaded = 1;
                }
                if(front->right && !isBurnt[front->right]) {
                    q.push(front->right);
                    isBurnt[front->right] = 1;
                    isFireSpreaded = 1;
                }
                if(parentMap[front] && !isBurnt[parentMap[front]]) {
                    q.push(parentMap[front]);
                    isBurnt[parentMap[front]] = 1;
                    isFireSpreaded = 1;
                }
            }
            if(isFireSpreaded) ++T;
        }
        return T;
    }


string preorder(Node* root, vector<Node*> &ans, unordered_map<string, int> &subTreeMap) {
    if(!root) 
        return "N";
    string curr = to_string(root->data);
    string left = preorder(root->left, ans, subTreeMap);
    string right = preorder(root->right, ans, subTreeMap);
    string s = curr + "," + left + "," + right;
    if(subTreeMap.find(s) != subTreeMap.end()) {
        if(subTreeMap[s] == 1)
            ans.push_back(root);
        subTreeMap[s]++;
    }
    else {
        subTreeMap[s] = 1;
    }
    return s;
}
vector<Node*> find_duplicates_subTree(Node* root) {
    unordered_map<string, int> subTreeMap;
    vector<Node*> ans;
    preorder(root, ans, subTreeMap);
    return ans;
}

int main() {

    Node* root = create_tree();
    // sum_tree(root);
    cout << "printing level order traversal :" << endl;
    level_order_traversal(root);

    // cout << "diameter of ther given tree is : " << solution(root) << endl;

    // bool isBalanced = 1;
    // balanced_binary_tree(root, isBalanced);
    // if(isBalanced) 
    //     cout << "the binary tree you've drawn is balanced" << endl;
    // else 
    //     cout << "the binary tree you've drawn isn't balanced" << endl;

    // if(is_mirror(root->right, root->left))
    //     cout << "true" << endl;
    // else 
    //     cout << "fasle" << endl;

    // vector<int>ans = diagonal(root);
    // for(auto i:ans) {
    //     cout << i << " ";
    // }
    // cout << endl;

    // vector<vector<int>> ans = vertical_traversal(root);
    // cout << "[ ";
    // for(auto vect1D:ans) {
    //     cout << "[ ";
    //     for(auto x:vect1D) {
    //         cout << x << " ";
    //     }
    //     cout << "]";
    // }
    // cout << " ]" << endl;

    // vector<vector<int>> ans = zigzag_level_order(root);
    // cout << "[ ";
    // for(auto vect1D:ans) {
    //     cout << "[ ";
    //     for(auto x:vect1D) {
    //         cout << x << " ";
    //     }
    //     cout << "]";
    // }
    // cout << " ]" << endl;

    // int test_case;
    // cin >> test_case;
    // while(test_case) {
    //     test_case--;
    //     int target_sum, ans=0;
    //     cout << "enter the target sum" << endl;
    //     cin >> target_sum;
    //     cout << "max paths in this tree " << path_sum_3(root, target_sum, ans) << endl;
    // }

    // auto ans = get_max_sum(root);
    // cout << "max sum of non adjacent nodes : " << max(ans.first, ans.second) << endl;

    // auto h = height(root);
    // cout << "sum of longest bloodline of the given tree : " << h.second << endl;

    // vector<int> ans = morris_Traversal(root);
    // cout << "[ ";
    // for(auto x:ans) {
    //     cout << x << " ";
    // }
    // cout << "]" << endl;

    // int test_case, target=0;
    // cout << "enter the test cases you want to try in this tree : ";
    // cin >> test_case;
    // while(test_case) {
    //     test_case--;
    //     cout << "enter the target you've to burn first : ";
    //     cin >> target;
    //     unordered_map<Node*, Node*> parentMap;
    //     Node* targetNode = parent_mapping(root, parentMap, target);
    //     cout << "the minimum time to burn the given tree would be [" << BurnTheTree(targetNode, parentMap) << "] seconds" << endl;
    // }

    // vector<Node*> ans = find_duplicates_subTree(root);
    // cout << "[ ";
    // for(auto itr:ans) {
    //     cout << itr->data << " ";
    // }
    // cout << "]" << endl;

    return 0;
}