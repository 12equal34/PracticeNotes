#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> S(N + 1, vector<int>(M + 1));

    bool whiteCell = false;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            S[i][j] = S[i][j - 1] + S[i - 1][j] - S[i - 1][j - 1];

            char c;
            cin >> c;
            if ((c == 'W' && !whiteCell) || (c == 'B' && whiteCell)) {
                ++S[i][j];
            }

            whiteCell = !whiteCell;
        }
        if (M % 2 == 0) {
            whiteCell = !whiteCell;
        }
    }

    vector<int> P;
    P.reserve((N - K + 1) * (M - K + 1));
    for (int i = K; i <= N; i++) {
        for (int j = K; j <= M; j++) {
            P.push_back(S[i][j] - S[i][j - K] - S[i - K][j] + S[i - K][j - K]);
        }
    }

    int blackOnLeftTop = *min_element(P.begin(), P.end());
    int whiteOnLeftTop = K * K - *max_element(P.begin(), P.end());
    cout << min<int>(blackOnLeftTop, whiteOnLeftTop);
}