#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

void heapBasedApproach(const vector<int> &numbers, string command)
{
    if (command == "max")
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : numbers)
        {
            minHeap.push(num);
            if (minHeap.size() > 10)
                minHeap.pop();
        }
        vector<int> top10;
        while (!minHeap.empty())
        {
            top10.push_back(minHeap.top());
            minHeap.pop();
        }
        sort(top10.begin(), top10.end());
        cout << "Heap Result: ";
        for (int num : top10)
            cout << num << " ";
        cout << endl;
    }
    else if (command == "min")
    {
        priority_queue<int> maxHeap;
        for (int num : numbers)
        {
            maxHeap.push(num);
            if (maxHeap.size() > 10)
                maxHeap.pop();
        }
        vector<int> top10;
        while (!maxHeap.empty())
        {
            top10.push_back(maxHeap.top());
            maxHeap.pop();
        }
        sort(top10.begin(), top10.end());
        cout << "Heap Result: ";
        for (int num : top10)
            cout << num << " ";
        cout << endl;
    }
    else
    {
        cerr << "Invalid command!" << endl;
        return;
    }
}

void quickSortBasedApproach(vector<int> &numbers, string command)
{
    sort(numbers.begin(), numbers.end());
    cout << "QSort Result: ";
    if (command == "max")
    {
        for (int i = 0; i < 10; ++i)
        {
            cout << numbers[numbers.size() - 1 - i] << " ";
        }
    }
    else if (command == "min")
    {
        for (int i = 0; i < 10; ++i)
        {
            cout << numbers[i] << " ";
        }
    }
    else
    {
        cerr << "Invalid command!" << endl;
        return;
    }
    cout << endl;
}

int main()
{
    vector<int> numbers;
    ifstream inputFile("mtest.dat");
    if (!inputFile.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int num;
    while (inputFile >> num)
    {
        numbers.push_back(num);
    }
    inputFile.close();

    if (numbers.size() < 5000)
    {
        cerr << "Error: The file should contain at least 5000 integers" << endl;
        return 1;
    }

    string command;
    cin >> command;

    auto start = chrono::high_resolution_clock::now();
    quickSortBasedApproach(numbers, command);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "QTime: *" << endl;

    start = chrono::high_resolution_clock::now();
    heapBasedApproach(numbers, command);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "HTime: *" << endl;

    return 0;
}