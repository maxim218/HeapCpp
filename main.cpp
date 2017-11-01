// Kolotovkin Maxim

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

// class for working with stack
class MyArray {
    private:
        // pointer to array
        int * arr;
        // number of existing elements in array
        int nowSize;
        // size of array
        int maxSize;

        // method for growing of array
        void makeArrayLonger(){
            // if is similar to "maxSize *= 2", but summa is faster
            maxSize = maxSize + maxSize;
            // create new array that is longer than previous array
            int * buffer = new int[maxSize];
            // copy elements from old array to new array
            for(int i = 0; i < nowSize; i++) buffer[i] = arr[i];
            // free memory of old array
            delete [] arr;
            // make pointer to new array
            arr = buffer;
        }

    public:
        // init fields of object and create new array
        MyArray(){
            nowSize = 0;
            maxSize = 5;
            arr = new int[maxSize];
        }

        // free memory of dinamic array
        ~MyArray(){
            delete [] arr;
        }

        // adding element to the end of array
        void push(int value) {
            // save value of element to array
            arr[nowSize] = value;
            // make size bigger to one position
            nowSize++;
            // if we have not place to push elements, we should make array bigger
            if(nowSize == maxSize) makeArrayLonger();
        }

        // try to delete last element of array
        int pop(bool &err) {
            // if array is empty
            if(nowSize == 0) {
                // set flag of error
                err = true;
                // return value
                return -1;
            }
            // if we have not error
            // do not set flag of error
            err = false;
            // get last value of array
            int value = arr[nowSize - 1];
            // drop last element
            nowSize--;
            // return value of last element
            return value;
        }

        // writin content of array from last element to first element
        void printContent(){
            cout << "\n";
            // vivsit all elements from last position to first position
            for(int i = nowSize - 1; i >= 0; i--){
                // print value of element
                cout << arr[i] << " ";
            }
            cout << "\n";
        }

        // getting number of existing elements in array
        int numberOfElements() {
            return nowSize;
        }

        // method for setting value of element
        void setElement(int number, int value){
            arr[number] = value;
        }

        // method for getting value of element
        int getElement(int number) {
            return arr[number];
        }

        // method for changing plases of two element in array
        void swapElements(int numberFirst, int numberSecond) {
            swap(arr[numberFirst], arr[numberSecond]);
        }
};

// class for working with heap
class MyHeap {
    private:
        // object that works like vector
        MyArray v;

    public:
        // method for getting number of values in heap
        int sizeOfHeap() {
            return v.numberOfElements();
        }

        // method for adding element to heap:  O(log2 K)
        void addNewElement(int value) {
            // save element to the last position of vector
            v.push(value);
            // get now position of element
            int nowElementIndex = sizeOfHeap() - 1;
            // get position of parent of the element
            int parent = (nowElementIndex - 1) / 2;
            // while element is not staying in his position
            while (nowElementIndex > 0 && v.getElement(parent) < v.getElement(nowElementIndex)) {
                // change values of element and his parent
                v.swapElements(parent, nowElementIndex);
                // change indexes
                nowElementIndex = parent;
                parent = (nowElementIndex - 1) / 2;
            }
        }

        // method for setting heap properties to array:  O(log2 K)
        void heapify(int number) {
            // variables for saving indexes
            int left, right, biggest;

            while(true) {
                // get position of left child
                left = number + number + 1;
                // get position of right child
                right = number + number + 2;
                // get postion of biggest child
                biggest = number;
                if (left < sizeOfHeap() && v.getElement(left) > v.getElement(biggest)) biggest = left;
                if (right < sizeOfHeap() && v.getElement(right) > v.getElement(biggest)) biggest = right;
                // if now element is the biggest -> stop
                if (biggest == number) break;
                v.swapElements(number, biggest);
                number = biggest;
            }
        }

        // get max element of the heap
        int getMaxValue() {
            return v.getElement(0);
        }

        // method for deleting max element of heap:  O(log2 K)
        int deleteMaxValue() {
            // get value of max element
            int value = getMaxValue();
            // set to zero position value of last element
            v.setElement(0, v.getElement(sizeOfHeap() - 1));
            // delete last element
            bool err = false;
            int droppedValue = v.pop(err);
            // method for setting heap properties to array:  O(log2 K)
            heapify(0);
            // return valur of last element
            return value;
        }
};

// function for reading integer value
int read(){
    int value = 0;
    cin >> value;
    return value;
}

// main function
int main() {
    // read number of all elements
    int n = read();
    // read number of first group of elements
    int k = read();

    // create object for working with heap
    MyHeap heap;

    // visit all elements
    for(int i = 0; i < n; ++i){
        // read element
        int x = read();
        // if heap is not full
        if(heap.sizeOfHeap() < k) {
            // add element to heap
            heap.addNewElement(x); // O(log2 K)
        } else {
            // get max element of heap
            int maxValue = heap.getMaxValue();
            // if this element is less than max element of heap
            if(maxValue > x) {
                // delete max element of heap
                heap.deleteMaxValue(); // O(log2 K)
                // push new element to heap
                heap.addNewElement(x); // O(log2 K)
            }
        }
    }

    // O = n * (O(log2 K) + O(log2 K)) = O(n * log2 K)

    // object for saving result and printing it
    MyArray arr;

    // save number of elements in heap
    int sizeOfHeap = heap.sizeOfHeap();
        // visit all elements of heap
        for(int i = 0; i < sizeOfHeap; ++i) {
            // get value of max element of heap and delete it after getting
            int value = heap.deleteMaxValue(); // O(log2 K)
            // push element to array
            arr.push(value);
        }

    // print content of array
    arr.printContent();

    // O(n * log2 K)

    return 0;
}
