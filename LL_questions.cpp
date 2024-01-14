#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node* curr;

    Node() : data(0), next(nullptr), prev(nullptr), curr(nullptr) {}
    Node(int dataue) : data(dataue), next(nullptr), prev(nullptr), curr(nullptr) {}
};

void insert_at_head(Node* &head, Node* &tail, int data) {
    if(head == nullptr) {
        Node* new_node = new Node(data);
        head = new_node;
        tail = new_node;
    }
    else {
        Node* new_node = new Node(data);
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

Node* reverse_LL(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while(curr != nullptr) {
        Node* new_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = new_node;
    }
    return prev;
}

void print_LL(Node* head) {
    Node* temp = head;
    while(temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL";
    cout << endl;
}

Node* add_two_numbers(Node* l1, Node* l2) {
    l1 = reverse_LL(l1);
    l2 = reverse_LL(l2);
    Node* ans = new Node(-1);
    Node* it = ans;
    int carry = 0;

    while(l1 || l2 || carry) {
        int a = l1 ? l1->data : 0;
        int b = l2 ? l2->data : 0;

        int sum = a + b + carry;
        int digit = sum % 10;
        carry = sum / 10;

        it->next = new Node(digit);
        it = it->next;

        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
    }

    Node* final_ans = ans->next;
    delete ans;
    final_ans = reverse_LL(final_ans);
    return final_ans;
}

void Link_delete(Node* head, int m, int n) {
    if(!head) return;
    Node* it = head;
    for(int i=1; i<m; ++i) {
        if(!it) return;
        it = it->next;
    }

    if(!it) return;

    Node* M_th_node = it;
    it = M_th_node->next;
    for(int i=0; i<n; ++i) {
        if(!it) break;
        Node* temp = it->next;
        delete it;
        it = temp;
    }
    M_th_node->next = it;
    Link_delete(it, m, n);
}

Node* merge_two_lists(Node* list1, Node* list2) {
    if(list1 == nullptr) return list2;
    if(list2 == nullptr) return list1;
    Node* ans = new Node(-1);
    Node* mptr = ans;
    while(list1 && list2) {
        if(list1->data <= list2->data) {
            mptr->next = list1;
            mptr = list1;
            list1 = list1->next;
        }
        else {
            mptr->next = list2;
            mptr = list2;
            list2 = list2->next;
        }
    }
    if(list1) mptr->next = list1;
    if(list2) mptr->next = list2;
    return ans->next;
}

void get_node(Node* head, int &position, int &ans) {
    if(head == 0) return;
    get_node(head->next, position, ans);
    if(position == 0) {
        ans = head->data;
    }
    position--;
}

Node *getIntersectionNode(Node *headA, Node *headB) {
    Node* a = headA;
    Node* b = headB;

    while(a->next && b->next) {
    if(a==b) return a;
        a=a->next;
        b=b->next;
    }

    if(a->next==0 && b->next==0 && a != b) return 0;

    if(a->next == 0) {
        // if I'm here that means (b>=a) now we've to find how much big it is
        int b_length=0;
        while(b->next) {
            b_length++;
            b=b->next;
        }
        while(b_length--) {
            headB = headB->next;
        }
    } 
    else {
        // if I'm here that means (a>=b) now we've to find how much big it is
        int a_length=0;
        while(a->next) {
            a_length++;
            a=a->next;
        }
        while(a_length--) {
            headA = headA->next;
        }
    }

    while(headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    // here both head are on the same position you can return anyone...
    return headA;
}

Node* intersect_head_A(Node* headA, Node* intersection_list) {
    while(headA->next != nullptr) {
        headA = headA->next;
    }
    headA->next = intersection_list;
    return headA;
}

Node* intersect_head_B(Node* headB, Node* intersection_list) {
    while(headB->next != nullptr) {
        headB = headB->next;
    }
    headB->next = intersection_list;
    return headB;
}

Node* find_mid(Node* head) {
    Node* slow = head;
    Node* fast = head->next;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* sort_list(Node* head) {
    if(head == 0 || head->next == 0) {
        return head;
    }

    // break LL into two part using mid node
    Node* mid = find_mid(head);
    Node* left = head;
    Node* right = mid->next;
    mid->next = nullptr;

    // sort using recursion
    left = sort_list(left);
    right = sort_list(right);

    // merge both left and right LL
    Node* merged_LL = merge_two_lists(left, right);
    return merged_LL;
}

int get_length(Node* head) {
        int len=0; 
        Node* temp = head;
        while(temp) {
            len++;
            temp = temp->next;
        }
        return len;
}
Node* rotateRight(Node* head, int k) {
        if(!head) return 0;

        int len = get_length(head);
        int actual_rotate_K = (k % len);
        
        if(actual_rotate_K == 0) return head;
        int new_LastNode_pos = len - actual_rotate_K - 1;

        Node* new_LastNode = head;
        for(int i=0; i<new_LastNode_pos; ++i) {
            new_LastNode = new_LastNode->next;
        }
        Node* new_head = new_LastNode->next;
        new_LastNode->next = 0;

        Node* it = new_head;
        while(it->next) {
            it=it->next;
        }
        it->next = head;
        return new_head;
}

Node* mergeNodes(Node* head) {
        if(!head) return 0;
        Node* slow=head, *fast=head->next, *new_last_node=0;
        int sum=0; 

        while(fast) {
            if(fast->data != 0) {
                sum += fast->data;
            }
            else {
                slow->data = sum;
                new_last_node = slow;
                slow = slow->next;
                sum = 0;
            }
            fast = fast->next;
        }
        // Node* temp = slow;
        new_last_node->next = 0;

        // deleting the remaining list
        // while(temp) {
        //     Node* nxt = temp->next;
        //     delete temp;
        //     temp = nxt;
        // }
        return head;
}

vector<int> nodesBetweenCriticalPoints(Node* head) {
        vector<int> ans = {-1, -1};
        Node* prev = head;
        if(!prev) return ans;
        Node* curr = head->next;
        if(!curr) return ans;
        Node* nxt = head->next->next;
        if(!nxt) return ans;
        int first_CP = -1, last_CP = -1;
        int min_dist = INT_MAX;
        int i=1;

        while(nxt) {
            bool is_CP = ((curr->data > prev->data && curr->data > nxt->data) || 
                            (curr->data < prev->data && curr->data < nxt->data)) ? true : false;

            if(is_CP && first_CP == -1) {
                first_CP = i;
                last_CP = i;
            }
            else if(is_CP) {
                min_dist = min(min_dist, i-last_CP);
                last_CP = i;
            }
            ++i;
            prev = prev->next;
            curr = curr->next;
            nxt = nxt->next;
        }

        if(last_CP == first_CP) {
            return ans;
        }
        else {
            ans[0] = min_dist;
            ans[1] = last_CP - first_CP;
        }
        return ans;
}

void print_vector(vector<int> &ans) {
    cout << "[ ";
    for(int i=0; i<ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "]";
    cout << endl;
}

int main() {

    Node* head = nullptr;
    Node* tail = nullptr;

    // add two numbers in a linked list
    // Node* l1 = nullptr;
    // Node* l2 = nullptr;
    // insert_at_head(l1, tail, 9);
    // insert_at_head(l1, tail, 9);
    // insert_at_head(l1, tail, 9);
    // insert_at_head(l2, tail, 8);
    // insert_at_head(l2, tail, 8);
    // insert_at_head(l2, tail, 5);
    // cout << "first node :-" << endl;
    // print_LL(l1);
    // cout << "second node :-" << endl;
    // print_LL(l2);
    // Node* ans = add_two_numbers(l1, l2);
    // cout << "sum of two numbers :-" << endl;
    // print_LL(ans);

    // delete N nodes after M nodes
    // for(int i=10; i>0; --i) {
    //     insert_at_head(head, tail, i);
    // }
    // cout << "linked list before deleting N nodes :-" << endl;
    // print_LL(head);
    // cout << "linked list after deleting N nodes :-" << endl;
    // Link_delete(head, 1, 2);
    // print_LL(head);

    // merge two sorted lists
    // Node* list1 = nullptr;
    // Node* list2 = nullptr;
    // insert_at_head(list1, tail, 3);
    // insert_at_head(list1, tail, 2);
    // insert_at_head(list1, tail, 1);
    // insert_at_head(list2, tail, 6);
    // insert_at_head(list2, tail, 5);
    // insert_at_head(list2, tail, 4);
    // cout << "list 1: ";
    // print_LL(list1);
    // cout << "list 2: ";
    // print_LL(list2);
    // Node* ans = merge_two_lists(list1, list2);
    // cout << "merging two linked lists :-" << endl;
    // print_LL(ans);

    // Kth node from the end
    // insert_at_head(head, tail, 0);
    // insert_at_head(head, tail, 1);
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 3);
    // print_LL(head);
    // int ans = -1;
    // int position = 2;
    // get_node(head, position, ans);
    // cout << ans << endl;

    // intersection of two linked lists
    // Node* headA = nullptr;
    // Node* headB = nullptr;
    // Node* intersection_list = nullptr;
    // insert_at_head(headA, tail, 1);
    // insert_at_head(headA, tail, 4);
    // cout << "head A: ";
    // print_LL(headA);
    // insert_at_head(headB, tail, 1);
    // insert_at_head(headB, tail, 6);
    // insert_at_head(headB, tail, 5);
    // cout << "head B: ";
    // print_LL(headB);
    // insert_at_head(intersection_list, tail, 5);
    // insert_at_head(intersection_list, tail, 4);
    // insert_at_head(intersection_list, tail, 8);
    // cout << "this is the list which soon be intersected: " << endl;
    // print_LL(intersection_list);

    // Node* head_A = intersect_head_A(headA, intersection_list);
    // Node* head_B = intersect_head_B(headB, intersection_list);
    // cout << "new head A: ";
    // print_LL(headA);
    // cout << "new head B: ";
    // print_LL(headB);
    // Node* ans = getIntersectionNode(headA, headB);
    // cout << "this is the point that the two of the linked list are intersected: " << ans->data << endl;

    // sort list using merge sort
    // insert_at_head(head, tail, 3);
    // insert_at_head(head, tail, 1);
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 4);
    // cout << "linked list before sorting :-" << endl;
    // print_LL(head);
    // cout << "linked list after sorting :-" << endl;
    // Node* ans = sort_list(head);
    // print_LL(ans);

    // rotate list
    // insert_at_head(head, tail, 5);
    // insert_at_head(head, tail, 4);
    // insert_at_head(head, tail, 3);
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 1);
    // cout << "present linked list: ";
    // print_LL(head);
    // int k;
    // cout << "how many times do you want to rotate this linked list: ";
    // cin >> k;
    // Node* ans = rotateRight(head, k);
    // cout << "this is your rotated linked list: ";
    // print_LL(ans);

    // merging nodes in between zeroes
    // insert_at_head(head, tail, 0);
    // insert_at_head(head, tail, 1);
    // insert_at_head(head, tail, 3);
    // insert_at_head(head, tail, 0);
    // insert_at_head(head, tail, 4);
    // insert_at_head(head, tail, 5);
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 0);
    // print_LL(head);
    // cout << "after merging nodes between the zeroes :-" << endl;
    // Node* ans = mergeNodes(head);
    // print_LL(ans);

    // leetcode - 2058
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 1);
    // insert_at_head(head, tail, 5);
    // insert_at_head(head, tail, 2);
    // insert_at_head(head, tail, 1);
    // insert_at_head(head, tail, 3);
    // insert_at_head(head, tail, 5);
    // print_LL(head);
    // cout << "max and min: ";
    // vector<int> ans = nodesBetweenCriticalPoints(head);
    // print_vector(ans); 

    return 0;
}