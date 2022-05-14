#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int calDist(int a, int b, int y, int x) {
    return abs(a - y) + abs(b - x);
}

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int ddy[4] = {1, 1, -1, -1};
int ddx[4] = {1, -1, 1, -1};
// int dy2[8] = {1, 1, -1, -1, 2, -2, 0, 0};
// int dy2[8] = {1, -1, 1, -1, 0, 0, 2, -2};

bool position(int y, int x, int i, int dir, vector<string>& place) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];

    if (0 > ny || ny >= 5 || 0 > nx || nx >= 5) {
        return true;
    }

    if (place[ny][nx] == 'P') {
        return false;
    } else if (place[ny][nx] == 'X') {
        return true;
    } else {
        if (i < 2) {
            return position(ny, nx, i + 1, dir, place);
        } else {
            return true;
        }
    }

    return true;
}
bool positionDiagonal(int y, int x, int dir, vector<string>& place) {
    int ny = y + ddy[dir];
    int nx = x + ddx[dir];

    if (0 > ny || ny >= 5 || 0 > nx || nx >= 5) {
        return true;
    }

    if (place[ny][nx] == 'P') {
        int udy = y + ddy[dir];
        int udx = x;

        int rly = y;
        int rlx = x + ddx[dir];

        if (place[udy][udx] == 'X' && place[rly][rlx] == 'X') {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

bool verifyPosition(int y, int x, vector<string>& place) {
    bool isTrue = true;
    for (int i = 0; i < 4; i++) {
        if (!position(y, x, 1, i, place)) {
            return false;
        }
        if (!positionDiagonal(y, x, i, place)) {
            return false;
        }
    }
    return true;
}

bool isSatisfyPlace(vector<string>& place) {
    bool isSatisfied = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (place[i][j] == 'P') {
                isSatisfied = verifyPosition(i, j, place);
            }

            if (!isSatisfied) {
                return false;
            }
        }
    }

    return true;
}

// places의 행 길이(대기실 개수) = 5
// places의 각 행은 하나의 대기실 구조를 나타냅니다.
// places의 열 길이(대기실 세로 길이) = 5
// places의 원소는 P,O,X로 이루어진 문자열입니다.
// places 원소의 길이(대기실 가로 길이) = 5
// P는 응시자가 앉아있는 자리를 의미합니다.
// O는 빈 테이블을 의미합니다.
// X는 파티션을 의미합니다.
// 입력으로 주어지는 5개 대기실의 크기는 모두 5x5 입니다.

// 1차원 정수 배열에 5개의 원소를 담아서 return 합니다.
// places에 담겨 있는 5개 대기실의 순서대로, 거리두기 준수 여부를 차례대로 배열에 담습니다.
// 각 대기실 별로 모든 응시자가 거리두기를 지키고 있으면 1을, 한 명이라도 지키지 않고 있으면 0을 담습니다.
vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    for (vector<string> place : places) {
        if (isSatisfyPlace(place)) {
            answer.push_back(1);
        } else {
            answer.push_back(0);
        }
    }

    return answer;
}