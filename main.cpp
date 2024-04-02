#include "Queue.h"
#include <iostream>
#include <vector>
#include <limits> 

using namespace std;

//this function prints the queue 
//and helps with loading in the initial 10 numbers
void printQueue(Queue<int>& queue) {
    Queue<int> tempQueue; 
    cout << "Queue elements: ";
    while (!queue.empty()) {
        int frontElement = queue.front();
        cout << frontElement << " ";
        queue.pop();
        tempQueue.push(frontElement);
    }
    cout << endl;
    while (!tempQueue.empty()) {
        queue.push(tempQueue.front());
        tempQueue.pop();
    }
}

//this function is the backwards recursive search that goes from the 
//end of the queue to the beginning 
int searchRecursive(Queue<int>& queue, int target, int index) {
    if (queue.empty()) return -1; 
    int current = queue.front();
    queue.pop();
    int result = searchRecursive(queue, target, index - 1);
    queue.push(current); 
    if (current == target) return index;
    return result;
}

//also a part of the backwards recursive search to make it function
//this includes error checking so that you cannot enter numbers that arent valid or characters
void searchInQueue(Queue<int>& queue) {
    int target;
    cout << "Enter a number (1-10) to search for: ";
    while (!(cin >> target) || target < 1 || target > 10) {
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    int index = searchRecursive(queue, target, queue.size() - 1);
    if (index != -1) {
        cout << "Integer " << target << " was found at index " << index << " in the queue.\n";
    }
    else {
        cout << "Integer " << target << " was not found in the queue.\n";
    }
}

//this is the insertion sort function for step 3 of the instructions
void insertionSort(vector<int>& arr) {
    int i, j, key;
    bool insertionNeeded = false;
    for (j = 1; j < arr.size(); j++) {
        key = arr[j];
        insertionNeeded = false;
        for (i = j - 1; i >= 0 && arr[i] > key; i--) {
            arr[i + 1] = arr[i];
            insertionNeeded = true;
        }
        if (insertionNeeded) {
            arr[i + 1] = key;
        }
    }
}

//this also helps with the sort function that reorganizes the numbers in 
// numerical order if they are out of order
void sortQueue(Queue<int>& queue) {
    vector<int> tempVector;
    while (!queue.empty()) {
        tempVector.push_back(queue.front());
        queue.pop();
    }
    insertionSort(tempVector);
    for (int num : tempVector) {
        queue.push(num);
    }
    cout << "Queue sorted successfully.\n";
    printQueue(queue);
}

int main() {
    Queue<int> myQueue;
    for (int i = 1; i <= 10; ++i) { 
        //here is where it pushes the intial 10 intergers into the queue
        myQueue.push(i);
    }
    printQueue(myQueue);

    int choice = 0;

    //this is what drives the menu for the program to do whatever function you want at any time
    //this also calls all of the functions
    do {
        cout << "\nEnter 1 to move the first element of the queue to the rear of the queue\n";
        cout << "Enter 2 to search for a number in the queue\n";
        cout << "Enter 3 to sort the queue\n";
        cout << "Enter 4 to exit the program\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            myQueue.move_to_rear();
            printQueue(myQueue);
            break;
        case 2:
            searchInQueue(myQueue);
            break;
        case 3:
            sortQueue(myQueue);
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}
