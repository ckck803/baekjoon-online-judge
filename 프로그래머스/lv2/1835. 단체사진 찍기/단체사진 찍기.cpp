#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string alpa = "";
int total = 0;
vector<bool> check;
vector<vector<char>> cases;

void makeAllCase(int choice, int depth, vector<char>& onecase) {
    if (choice == depth) {
        cases.push_back(onecase);
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (check[i]) {
            continue;
        }
        check[i] = true;
        onecase[choice] = alpa[i];
        makeAllCase(choice + 1, depth, onecase);
        check[i] = false;
    }
}

int position(vector<char>& onecase, char c) {
    for (int i = 0; i < onecase.size(); i++) {
        if (onecase[i] == c) {
            return i;
        }
    }
    return -1;
}

bool inspectPhoto(int index, string& line) {
    char c1 = line[0];
    char c2 = line[2];
    char op = line[3];
    int dist = line[4] - '0' + 1;
    int p1 = 0;
    int p2 = 0;

    vector<char>& onecase = cases[index];
    p1 = position(onecase, c1);
    p2 = position(onecase, c2);

    if (op == '=') {
        return (abs(p1 - p2) == dist);
    } else if (op == '<') {
        return (abs(p1 - p2) < dist);
    } else {
        return (abs(p1 - p2) > dist);
    }
}

int solution(int n, vector<string> data) {
    int answer = 0;
    total = 0;
    alpa = "ACFJMNRT";

    cases.clear();
    vector<char> onecase = vector<char>(8);
    check = vector<bool>(8, false);
    makeAllCase(0, 8, onecase);

    cout << cases.size() << endl;

    for (int i = 0; i < cases.size(); i++) {
        bool allSatisfy = true;
        for (int j = 0; j < n; j++) {
            if (inspectPhoto(i, data[j]) == false) {
                allSatisfy = false;
                break;
            }
        }

        if (allSatisfy) {
            total++;
        }
    }
    answer = total;

    return answer;
}