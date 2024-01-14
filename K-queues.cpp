#include<iostream>

using namespace std;

class Kqueues {
public:
    int n, k, freeSpot;
    int *arr, *front, *rear, *next;

    Kqueues(int _n, int _k) : n(_n), k(_k), freeSpot(0) {
        arr = new int[n];
        next = new int[n];
        front = new int[k];
        rear = new int[k];

        for(int i=0; i<k; ++i)
            front[i] = rear[i] = -1;

        for(int i=0; i<n; ++i) 
            next[i] = i+1;

        next[n-1] = -1;
    }

    // push x into [qi]th queue
    int push(int x, int qi) {
        // overflow
        if(freeSpot == -1) {
            return freeSpot;
        }

        // find the first free index
        int index = freeSpot;

        // update freespot
        freeSpot = next[index];

        // if first element is in qi
        if(front[qi] == -1) {
            front[qi] = index;
        }
        else {
            // link new element to that Q's rearest element
            next[rear[qi]] = index;
        }

        // cout << "index of next element = " << next[index] << endl;

        // update next
        next[index] = -1;

        // update rear
        rear[qi] = index;
        arr[index] = x;
        return arr[index];
    }

    // pop element from [qi]th queue
    int pop(int qi) {
        // underflow
        if(front[qi] == -1) {
            return -1;
        }

        // find index to pop
        int index = front[qi];

        // front update
        front[qi] = next[index];

        // update freespots
        next[index] = freeSpot;
        freeSpot = index;
        return arr[index];
    }

    ~Kqueues() {
        delete[] arr;
        delete[] front;
        delete[] rear;
        delete[] next;
    }
};

int main() {

    Kqueues kq(6,2);
    cout << kq.push(13, 0) << endl;
    
    cout << kq.push(64, 0) << endl;
    
    cout << kq.push(19, 0) << endl;
    
    cout << kq.push(6, 1) << endl;
    
    cout << kq.push(74, 1) << endl;
    
    cout << kq.push(7, 0) << endl;

    cout << kq.pop(0) << endl;

    cout << kq.pop(1) << endl;

    cout << kq.push(9, 1) << endl;

    return 0;
}