#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll INF = 1e9 + 13;

bool check(vector<vector<ll>> &dp, int i, int j, int k)
{
    if (dp[i][j] > dp[i][k] + dp[k][j] && dp[i][k] != INF && dp[k][j] != INF)
    {
        return true;
    }
    return false;
}

int main()
{
    cout << "Enter the number of nodes and edges of graph: " << endl;
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> v(n, vector<ll>(n, INF));

    cout << "Enter the edges and their weights: " << endl;
    for (int i = 0; i < m; i++)
    {
        int s, e, w;
        cin >> s >> e >> w;
        v[s][e] = w;
    }

    cout << "Enter the 2 nodes between which you want the shortest distance: " << endl;
    int x, y;
    cin >> x >> y;

    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = v[i][j];
        }
    }

    // iterating the value of k:
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (check(dp, i, j, k))
                {
                    dp[i][j] = dp[i][k] + dp[j][k];
                }
            }
        }
    }

    cout << "Answer: " << dp[x][y] << endl;
    return 0;
}
