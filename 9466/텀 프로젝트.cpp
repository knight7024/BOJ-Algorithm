#include <iostream>
#include <vector>

using namespace std;

int visited[100001];

int cycleDFS(const int constStart, int start, vector<vector<int>> &node, int depth)
{
    visited[start] = 1;
    int next = node[start][0];
    if (next == start)
    {
        visited[start] = 2;
        return -1;
    }
    if (!visited[next])
    {
        int result = cycleDFS(constStart, next, node, depth + 1);
        visited[start] = !depth && !result ? -1 : result;
        return result;
    }
    else if (visited[next] == 1)
    {
        int result = next == constStart;
        visited[start] = !depth && !result ? -1 : result;
        return result;
    }
    visited[start] = -1;
    return -1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<vector<int>> node(n + 1);

        int ns;
        for (int i = 1; i <= n; i++)
        {
            cin >> ns;
            node[i].push_back(ns);
        }

        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                cycleDFS(i, i, node, 0);
            }
        }

        int answer = 0;
        for (int i = 1; i <= n; i++)
        {
            if (visited[i] <= 0)
                answer++;
            visited[i] = 0;
        }
        cout << answer << "\n";
    }
    return 0;
}
