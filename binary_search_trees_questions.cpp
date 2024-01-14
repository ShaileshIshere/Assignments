#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert_into_BST(Node* root, int data) {
    if(!root) {
        root = new Node(data);
        return root;
    }
    if(data > root->data) {
        root->right = insert_into_BST(root->right, data);
        return root;
    }
    else {
        root->left = insert_into_BST(root->left, data);
        return root;
    }
    return root;
}

void create_BST(Node* &root) {
    int data;
    cout << "enter data : " << endl;
    cin >> data;
    while(data != 0) {
        root = insert_into_BST(root, data);
        cout << "enter data :" << endl;
        cin >> data;
    }
}

void level_order_traversal(Node* root) {
    queue<Node*> q;
    q.push(root); q.push(nullptr);
    while(!q.empty()) {
        Node* temp = q.front(); q.pop();
        if(!temp) {
            cout << endl;
            if(!q.empty())
                q.push(nullptr);
        }
        else {
            cout << temp->data << " ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    }
}

// inorder successor of a binary tree
Node* inorder_successor(Node* root, Node* x) {
    Node* succ = 0;
    Node* curr = root;
    while(curr) {
        if(curr->data > x->data) {
            succ = curr;
            curr = curr->left;
        }
        else 
            curr = curr->right;
    }
    return succ;
}

// inorder predecessor of a binary tree
Node* inorder_predecessor(Node* root, Node* x) {
    Node* pred = 0;
    Node* curr = root;
    while(curr) {
        if(curr->data < x->data) {
            pred = curr;
            curr = curr->right;
        }
        else 
            curr = curr->left;
    }
    return pred;
}

// through morris traversal
// Node* morris_inorder_successor(Node* root, Node* x) {
//     // Node* succ = 0;
//     Node* curr = root;
//     while(curr) {
//         // if(!curr->left) {
//         //     if(curr->data > x->data)
//         //         succ = curr;
//         //     curr = curr->right;
//         // }
//         // else {
//         //     Node* pred = curr->left;
//         //     while(pred->right != curr && pred->right)
//         //         pred = pred->right;
//         //     if(!pred->right) {
//         //         pred->right = curr;
//         //         curr = curr->left;
//         //     }
//         //     else {
//         //         pred->right = nullptr;
//         //         if(curr->data > x->data)
//         //             succ = curr;
//         //         curr = curr->right;
//         //     }
//         // }

//         // by chatGPT
//         if (curr->right) {
//             // Find the leftmost node in the right subtree
//             Node* successor = curr->right;
//             while (successor->left && successor->left != curr) {
//                 successor = successor->left;
//             }
//             if (!successor->left) {
//                 // Set the curr node as the predecessor of the leftmost node
//                 successor->left = curr;
//                 curr = curr->right;
//             } else {
//                 // Reset the left pointer to NULL (revert the temporary change)
//                 successor->left = NULL;
//                 // Check if the curr node is the target node
//                 if (curr > x) {
//                     return successor;
//                 }
//                 curr = curr->left;
//             }
//         } else {
//             // If the curr node doesn't have a right child
//             // Check if the curr node is the target node
//             if (curr > x) {
//                 return curr;
//             }
//             curr = curr->left;
//         }
//     }
//     return nullptr;
// }

// create a BST using preorder traversal
Node* build_BST_from_pre(int &i, int min, int max, vector<int> &preorder) {
    if(i >= preorder.size())
        return nullptr;
    Node* root = nullptr;
    if(preorder[i] < max && preorder[i] > min) {
        root = new Node(preorder[i++]);
        root->left = build_BST_from_pre(i, min, root->data, preorder);
        root->right = build_BST_from_pre(i, root->data, max, preorder);
    }
    return root;
}

// convert a BST into a balance BST
void inorder(vector<int> &in, Node* root) {
    if(!root)
        return;
    inorder(in, root->left);
    in.push_back(root->data);
    inorder(in, root->right);
}
Node* build_tree(vector<int> &in, int start, int end) {
    if(start > end) 
        return nullptr;
    int mid = start + ((end-start) >> 1);
    Node* root = new Node(in[mid]);
    root->left = build_tree(in, start, mid-1);
    root->right = build_tree(in, mid+1, end);
    return root;
}

// find median of BST
// 1st way
// 1st morris traversal
int find_count(Node* root) {
    int count=0;
    Node* curr = root;
    while(curr) {
        if(!curr->left) {
            count++;
            curr = curr->right;
        }
        else {
            Node* pred = curr->left;
            while(pred->right != curr && pred->right)
                pred = pred->right;
            if(!pred->right) {
                pred->right = curr;
                curr = curr->left;
            }
            else {
                pred->right = nullptr;
                count++;
                curr = curr->right;
            }
        }
    }
    return count;
}
// 2nd morris traversal
float find_actual_median(Node* root, int n) {
    int i=0;
    int odd1 = (n+1) >> 1, oddVal1 = -1;
    int even1 = n >> 1, evenVal1 = -1;
    int even2 = (n >> 1) + 1, evenVal2 = -1;
    Node* curr = root;
    while(curr) {
        if(!curr->left) {
            i++;
            if(i == odd1)
                oddVal1 = curr->data;
            if(i == even1)
                evenVal1 = curr->data;
            if(i == even2)
                evenVal2 = curr->data;
            curr = curr->right;
        }
        else {
            Node* pred = curr->left;
            while(pred->right != curr && pred->right)
                pred = pred->right;
            if(!pred->right) {
                pred->right = curr;
                curr = curr->left;
            }
            else {
                pred->right = nullptr;
                i++;
                if(i == odd1)
                    oddVal1 = curr->data;
                if(i == even1)
                    evenVal1 = curr->data;
                if(i == even2)
                    evenVal2 = curr->data;
                curr  = curr->right;
            }
        }
    }
    float median = 0.0;
    if(n&1) 
        median = oddVal1;
    else 
        median = (evenVal1 + evenVal2) / 2.0;
    return median;
}

// 2nd way
// creating a vector of nodes from given BST using morris traversal
void create_vector(Node* root, vector<int> &morris) {
    Node* curr = root;
    while(curr) {
        if(!curr->left) {
            morris.push_back(curr->data);
            curr = curr->right;
        }
        else {
            Node* pred = curr->left;
            while(pred->right != curr && pred->right)
                pred = pred->right;
            if(!pred->right) {
                pred->right = curr;
                curr = curr->left;
            }
            else {
                pred->right = nullptr;
                morris.push_back(curr->data);
                curr = curr->right;
            }
        }
    }
}
// find median within the vector
float find_median(Node* root) {
    vector<int> morris;
    create_vector(root, morris);
    int n = morris.size();
    int oddVal = (n + 1) >> 1;
    int evenVal1 = n >> 1;
    int evenVal2 = (n >> 1) + 1;
    if(n&1) 
        return morris[oddVal-1];
    else 
        return (morris[evenVal1-1] + morris[evenVal2-1])/2.0;
}

// find the dead end of BST
bool is_dead_end(Node* root, unordered_map<int, bool> &visited, bool &ans) {
    if(!root)
        return ans;
    visited[root->data] = 1;
    if(!root->right && !root->left) {
        int xp1 = root->data + 1;
        int xm1 = root->data - 1 == 0 ? root->data : root->data - 1;
        if(visited.find(xp1) != visited.end() && visited.find(xm1) != visited.end()) {
            ans = 1;
            return ans;
        }
    }
    return is_dead_end(root->left, visited, ans) || is_dead_end(root->right, visited, ans);
}

// range sum of BST
int range_sum(Node* root, int low, int high) {
    if(!root)
        return 0;
    int ans=0;
    bool inRange = 0;
    if(root->data >= low && root->data <= high) {
        inRange = 1;
        ans += root->data;
    }
    if(inRange)
        ans += range_sum(root->left, low, high) + range_sum(root->right, low, high);
    else if(root->data < low)
        ans += range_sum(root->right, low, high);
    else
        ans += range_sum(root->left, low, high);
    return ans;
}

void inorder(Node* root, Node* &prev) {
    if(!root)
        return;
    inorder(root->left, prev);
    prev->left = 0;
    prev->right = root;
    prev = root;
    inorder(root->right, prev);
}
Node* flatter(Node* root) {
    Node* dummy = new Node(-1);
    Node* prev = dummy;
    inorder(root, prev);
    prev->left = prev->right = 0;
    root = dummy->right;
    return root;
}
void print_LL(Node* head) {
    Node* temp = head;
    while(temp) {
        cout << temp->data << " -> ";
        temp = temp->right;
    }
    cout << "NULL" << endl;
}

// replace every element with its least greatest element on its right
Node* insert(Node* root, int val, int &succ) {
    if(!root)
        return new Node(val);
    if(val <= root->data) {
        succ = root->data;
        root->left = insert(root->left, val, succ);
    }
    else 
        root->right = insert(root->right, val, succ);
    return root;
}
vector<int> least_greatest_element(vector<int> &arr, int n) {
    vector<int> ans(arr.size(), -1);
    Node* root = nullptr;
    for(int i=arr.size()-1; i>=0; --i) {
        int succ = -1;
        root = insert(root, arr[i], succ);
        ans[i] = succ;
    }
    return ans;
}

// check if the BST is valid BST from pre-order
int check_BST(vector<int> &tree, int min, int max, int &i) {
    if(i >= tree.size())
        return 1;
    else {
        if(tree[i] > min && tree[i] < max) {
            int root_data = tree[i++];
            check_BST(tree, min, root_data, i);
            check_BST(tree, root_data, max, i);
        }
    }
    return i == tree.size();
}

// merge two binary search trees
vector<int> merge(Node *root1, Node *root2) {
    vector<int> ans;
    stack<Node*> st_a, st_b;
    Node *a = root1, *b = root2;
    while(a || b || !st_a.empty() || !st_b.empty()) {
        while(a) {
            st_a.push(a);
            a=a->left;
        }
        while(b) {
            st_b.push(b);
            b=b->left;
        }
        if(st_b.empty() || (!st_a.empty() && st_a.top()->data <= st_b.top()->data)) {
            Node* a_top = st_a.top(); st_a.pop();
            ans.push_back(a_top->data);
            a=a_top->right;
        }
        else {
            auto b_top = st_b.top(); st_b.pop();
            ans.push_back(b_top->data);
            b=b_top->right;
        }
    }
    return ans;
}

// brothers from different roots
// int count_pairs(Node* root1, Node* root2, int x) {
//     int ans=0;
//     stack<Node*> s1, s2;
//     Node *a=root1, *b=root2;
//     while(true) {
//         while(a) {
//             // normal inorder traversal
//             s1.push(a);
//             a=a->left;
//         }
//         while(b) {
//             // reverse inorder traversal
//             s2.push(b);
//             b=b->right;
//         }
//         if(s1.empty() || s2.empty())
//             break;
//         auto a_top = s1.top();
//         auto b_top = s2.top();
//         int sum = a_top->data + b_top->data;
//         if(sum == x) {
//             ++ans;
//             s1.pop(); s2.pop();
//             a=a_top->right;
//             b=b_top->left;
//         }
//         else if(sum < x) {
//             s1.pop();
//             a=a_top->right;
//         }
//         else {
//             s2.pop();
//             b=b_top->left;
//         }
//     }
//     return ans;
// }
// experiment : printing all the pairs which sum is equal to x
vector<pair<int, int>> count_pairs(Node* root1, Node* root2, int x) {
    vector<pair<int, int>> p;
    stack<Node*> s1, s2;
    Node *a=root1, *b=root2;
    while(true) {
        while(a) {
            // normal inorder traversal
            s1.push(a);
            a=a->left;
        }
        while(b) {
            // reverse inorder traversal
            s2.push(b);
            b=b->right;
        }
        if(s1.empty() || s2.empty())
            break;
        auto a_top = s1.top();
        auto b_top = s2.top();
        int sum = a_top->data + b_top->data;
        if(sum == x) {
            p.push_back({a_top->data, b_top->data});
            s1.pop(); s2.pop();
            a=a_top->right;
            b=b_top->left;
        }
        else if(sum < x) {
            s1.pop();
            a=a_top->right;
        }
        else {
            s2.pop();
            b=b_top->left;
        }
    }
    return p;
}

int main() {
    // Node* root = nullptr;
    // create_BST(root);
    // cout << "printing level order traversal :" << endl;
    // level_order_traversal(root);

    // Node* x;
    // int test_case;
    // cout << "enter test cases : ";
    // cin >> test_case;
    // while(test_case--) {
    //     cout << "enter the node : ";
    //     cin >> x->data;
    //     Node* succ = inorder_successor(root, x);
    //     cout << "the successor of the given node is : " << succ->data << endl;
    //     Node* pred = inorder_predecessor(root, x);
    //     cout << "the successor of the given node is : " << pred->data << endl;
    // }
    // cin >> x->data;
    // Node* ans = morris_inorder_successor(root, x);
    // cout << ans->data << endl;

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> preorder(n);
    // for(int i=0; i<n; ++i) 
    //     cin >> preorder[i];
    // int i=0, min=INT_MIN, max=INT_MAX;
    // Node* ans = build_BST_from_pre(i, min, max, preorder);
    // cout << "printing BST : " << endl;
    // level_order_traversal(ans);

    // vector<int> in;
    // inorder(in, root);
    // Node* ans = build_tree(in, 0, in.size()-1);
    // cout << "printing the balanced BST : " << endl;
    // level_order_traversal(ans);

    // int node_count = find_count(root);
    // cout << "the median of given binary search tree is : " << find_actual_median(root, node_count) << endl;
    // cout << "the median of given binary search tree is : " << find_median(root) << endl;

    // bool ans=0;
    // unordered_map<int, bool> visited;
    // if(is_dead_end(root, visited, ans))
    //     cout << "the dead end is found" << endl;
    // else    
    //     cout << "the dead end isn't found" << endl;

    // int low, high;
    // cout << "enter the [low] or [high] range : ";
    // cin >> low >> high;
    // cout << "total range sum of given BST : " << range_sum(root, low, high) << endl;

    // Node* ans = flatter(root);
    // cout << "printing a Linked List from a Binary Search Tree structure" << endl;
    // print_LL(ans);

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> arr(n);
    // for(int i=0; i<n; ++i)
    //     cin >> arr[i];
    // vector<int>final_ans = least_greatest_element(arr, n);
    // cout << "[ ";
    // for(int x:final_ans)
    //     cout << x << " ";
    // cout << "]" << endl;

    // int n, i=0;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> tree(n);
    // for(int i=0; i<n; ++i)
    //     cin >> tree[i];
    // if(check_BST(tree, INT_MIN, INT_MAX, i))
    //     cout << "it's a valid BST :)" << endl;
    // else 
    //     cout << "it's an invalid BST :(" << endl;

    // BST1
    // Node* root1 = nullptr;
    // create_BST(root1);
    // cout << "printing level order traversal :" << endl;
    // level_order_traversal(root1);
    // // BST2
    // Node* root2 = nullptr;
    // create_BST(root2);
    // cout << "printing level order traversal :" << endl;
    // level_order_traversal(root2);
    // vector<int> ans = merge(root1, root2);
    // cout << "[ ";
    // for(int x:ans)
    //     cout << x << " ";
    // cout << "]";

    // BST1
    // Node* root1 = nullptr;
    // create_BST(root1);
    // cout << "printing level order traversal :" << endl;
    // level_order_traversal(root1);
    // // BST2
    // Node* root2 = nullptr;
    // create_BST(root2);
    // cout << "printing level order traversal :" << endl;
    // level_order_traversal(root2);
    // int x;
    // cout << "enter the value of [x] : ";
    // cin >> x;
    // // printing the number of pairs
    // // cout << "the number of pairs that meet their sum value to " << x << " are : " << count_pairs(root1, root2, x) << endl;
    // // printing the actual pairs
    // vector<pair<int, int>> ans = count_pairs(root1, root2, x);
    // // this is the way to print all the pairs that are stored in a vector
    // for(auto &[x, y] : ans)
    //     cout << "[ " << x << " " << y << " ]";
    // cout << endl;
    // // this is another way to print the pairs
    // for(auto &pair:ans)
    //     cout << "[ " << pair.first << " " << pair.second << " ]";

    return 0;
}