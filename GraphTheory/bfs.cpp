#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//directed unweighted graph

void bfs(int i, bool *visited, vector<vector<int>> graph)
{
    queue<int> q;
    q.push(i);
    visited[i] = true;

    while (!q.empty())
    {
        int node = q.front();
        cout << node << ' ';
        q.pop();
        visited[node] = true;

        for (int x = 0; x < graph[node].size(); x++)
        {
            if (!visited[graph[node][x]])
            {
                q.push(graph[node][x]);
                visited[graph[node][x]] = true;
            }
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

    //queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            bfs(i, visited, graph);
        }
    }

    //PRINTING THE GRAPH:
    // for (int i = 1; i < graph.size(); i++)
    // {
    //     for (int j = 0; j < graph[i].size(); j++)
    //     {
    //         cout << i << "->" << graph[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    delete[] visited;
}