// Johnson.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"

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

int main()
{
    test1();
    test2();
    test3();
}
