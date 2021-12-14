#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// 1 is the source node

void printShortestPaths(int *a, int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void Algo(bool *visited, vector<vector<pair<int, int>>> &graph, int *a)
{
    a[1] = 0;
    visited[1] = true;
    queue<int> q;
    q.push(1);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        visited[node] = true;
        for (int i = 0; i < graph[node].size(); i++)
        {
            int x = graph[node][i].first;
            int y = graph[node][i].second;
            if (!visited[x])
            {
                q.push(x);
            }

            a[x] = min(a[x], a[node] + y);
        }
    }
}

int main()
{
    // n: number of vertices; m: number of edges
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);
    int *a = new int[n + 1];
    bool *visited = new bool[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        a[i] = INT_MAX;
        visited[i] = false;
    }

    for (int i = 0; i < m; i++)
    {
        int s, e, w;
        cin >> s >> e >> w;
        pair<int, int> p(e, w);
        graph[s].push_back(p);
    }

    Algo(visited, graph, a);
    printShortestPaths(a, n);

    delete[] a;
    delete[] visited;
}

// FOR LONGEST PATH OF DAG, MULTIPLY EDGE WEIGHTS BY -1, FIND SHORTEST PATH, AND THEN MULTIPLY FINAL ANSWERS BY 1 AGAIN!
