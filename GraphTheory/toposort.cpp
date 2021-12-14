#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);
    for (int i = 1; i < n + 1; i++)
    {
        indegree[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;
    for (int i = 1; i < indegree.size(); i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << ' ';

        for (int i = 0; i < graph[node].size(); i++)
        {
            int x = graph[node][i];
            indegree[x]--;
            if (indegree[x] == 0)
            {
                q.push(x);
            }
        }
    }
    cout << endl;
}
