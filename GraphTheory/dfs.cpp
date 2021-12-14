#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> graph, int i, bool *visited)
{
    visited[i] = true;
    cout << i << endl;

    for (int x = 0; x < graph[i].size(); x++)
    {
        if (!visited[graph[i][x]])
        {
            dfs(graph, graph[i][x], visited);
        }
    }
}

int main()
{
    int n, m;

    cin >> n >> m; //vertices and edges

    vector<vector<int>> graph(n + 1);
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(graph, i, visited);
        }
    }

    //PRINTING THE GRAPH:
    for (int i = 1; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << i << "->" << graph[i][j] << ' ';
        }
        cout << endl;
    }

    delete[] visited;
}