#include <iostream>
#include <queue>

int breadthFirstSearch(int start, int end, int nodeCount, bool **edges);
void initBoolArray(bool *arr, size_t size);

int main()
{
    int n, m;
    std::cin >> m >> n;

    bool **edges = new bool *[m];
    if (edges == nullptr)
        return 1;

    for (int i = 0; i < m; ++i)
    {
        edges[i] = new bool[m];

        if (edges[i] == nullptr)
            return 1;

        initBoolArray(edges[i], m);
    }

    int x1, x2;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> x1 >> x2;
        edges[x1][x2] = true;
    }

    for (int i = 1; i < m; ++i)
    {
        std::cout << breadthFirstSearch(0, i, m, edges) << '\n';
    }
}

int breadthFirstSearch(int start, int end, int nodeCount, bool **edges)
{
    if (start == end)
        return 0;

    std::queue<int> q;
    bool *visited = new bool[nodeCount];
    initBoolArray(visited, nodeCount);

    q.push(start);

    int depth = 0;
    int nodesAtDepth = 1;
    int nodesAtNextDepth = 0;

    while (!q.empty())
    {
        int nextNode = q.front();
        q.pop();
        visited[nextNode] = true;
        --nodesAtDepth;

        for (int i = 0; i < nodeCount; ++i)
        {
            if (edges[nextNode][i] && !visited[i])
            {
                if (i == end)
                {
                    delete[] visited;
                    return depth + 1;
                }

                q.push(i);
                ++nodesAtNextDepth;
            }
        }

        if (nodesAtDepth == 0)
        {
            ++depth;
            nodesAtDepth = nodesAtNextDepth;
            nodesAtNextDepth = 0;
        }
    }

    return -1;
}

void initBoolArray(bool *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        arr[i] = false;
}