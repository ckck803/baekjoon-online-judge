#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll long long
const ll INF = 987654321;

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> dist = vector<vector<ll>>(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i < n + 1; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int start, end, weight;
        cin >> start >> end >> weight;

        if (dist[start][end] > weight) {
            dist[start][end] = weight;
        }
    }

    for (int k = 1; k < n + 1; k++) {
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (dist[i][j] == INF) {
                cout << 0 << ' ';
            } else {
                cout << dist[i][j] << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}