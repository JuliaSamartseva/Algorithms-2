// Johnson.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"
#include <unordered_set>

//make test from the file

void test1() {
    std::cout << "\nTEST1";
    vector<vector<int>> input;
    vector<int> x;
    input.push_back({ 1, 2, 10 });
    input.push_back({ 1, 3, 10 });
    input.push_back({ 2, 3, -10 });
    input.push_back({ 3, 4, 20 });

    //
    Graph y(input, 4);
    y.Johnson();
}

void test2() {
    std::cout << "\nTEST2";
    vector<vector<int>> input;
    vector<int> x;
    input.push_back({ 1, 2, -1 });
    input.push_back({ 2, 3, -2 });
    input.push_back({ 3, 1, -1 });
    input.push_back({ 1, 4, 20 });

    //
    Graph y(input, 4);
    y.Johnson();
}

void test3() {
    std::cout << "\nTEST3";
    vector<vector<int>> input;
    vector<int> x;
    input.push_back({ 1, 2, -5 });
    input.push_back({ 2, 3, 4 });
    input.push_back({ 1, 3, 2 });
    input.push_back({ 1, 4, 3 });
    input.push_back({ 3, 4, 1 });

    //
    Graph y(input, 4);
    y.Johnson();
}

void test4() {
    std::cout << "\nTEST4";
    vector<vector<int>> input;
    vector<int> x;
    input.push_back({ 1, 2, 2 });
    input.push_back({ 2, 3, -3 });
    input.push_back({ 3, 1, 5 });
    input.push_back({ 3, 6, 1 });
    input.push_back({ 3, 4, 1 });
    input.push_back({ 6, 4, 2 });
    input.push_back({ 4, 5, 3 });
    input.push_back({ 1, 5, -6 });
    input.push_back({ 5, 6, 1 });
    input.push_back({ 1, 4, -2 });

    //
    Graph y(input, 6);
    y.Johnson();
}

void test5() {
    std::cout << "\nTEST5";
    std::fstream myfile("input.txt", std::ios_base::in);
    Graph y(myfile);
    y.Johnson();
}

void test6 (int verticesNumber, int edgeNumber) {
    std::cout << "\nTEST6";
    std::fstream myfile("test6.txt", std::ios_base::out);
    if (myfile.is_open())
    {
        unordered_set<int> set;
        myfile << verticesNumber << " ";
        myfile << edgeNumber << "\n";
        for (int source = 1; source <= verticesNumber; source++) {
            int edge_for_source = rand() % verticesNumber;
            for (int j = 0; j < edge_for_source; j++) {
                int destination = rand() % verticesNumber + 1;
                if (set.find(destination) == set.end()) {
                    int weight = rand() % 100;
                    myfile << source << " " << destination << " " << weight << "\n";
                    edgeNumber--;
                }
                if (edgeNumber == 0) break;
            }
            if (edgeNumber == 0) break;
        }
        myfile.close();
        std::fstream myfile("test6.txt", std::ios_base::in);
        Graph y(myfile);
        y.Johnson();
    } else cout << "Unable to open file";
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6(40, 2000);
}
