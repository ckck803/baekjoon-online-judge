#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int numOfArea = 0;
int maxArea = 0;

vector<vector<bool>> check;
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void bfs(int y, int x, int color, int m, int n, vector<vector<int>> picture) {
    queue<pair<int, int>> q;
    check[y][x] = true;
    q.push({y, x});

    int count = 1;
    while (!q.empty()) {
        int cntY = q.front().first;
        int cntX = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cntY + dy[i];
            int nx = cntX + dx[i];

            if (0 > ny || ny >= m || 0 > nx || nx >= n) {
                continue;
            }

            if (check[ny][nx] == false && picture[ny][nx] == color) {
                check[ny][nx] = true;
                q.push({ny, nx});
                count++;
            }
        }
    }
    maxArea = max(maxArea, count);
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    numOfArea = 0;
    maxArea = 0;
    vector<int> answer;
    check = vector<vector<bool>>(m, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (check[i][j] == false && picture[i][j] != 0) {
                numOfArea++;
                bfs(i, j, picture[i][j], m, n, picture);
            }
        }
    }
    answer.push_back(numOfArea);
    answer.push_back(maxArea);

    return answer;
}