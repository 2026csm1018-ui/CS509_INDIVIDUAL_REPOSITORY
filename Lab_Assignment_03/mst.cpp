#include "mst.h"

#include <algorithm>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

class DSU
{
private:
    vector<int> parent;
    vector<int> rank_value;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank_value.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank_value[a] < rank_value[b])
            swap(a, b);

        parent[b] = a;

        if (rank_value[a] == rank_value[b])
            rank_value[a]++;

        return true;
    }
};



MSTResult kruskal(const CSR &G)
{
    MSTResult result;

    vector<MSTEdge> edges;


    edges.reserve(G.E);

    for (int u = 0; u < G.V; u++)
    {
        for (int p = G.row_ptr[u]; p < G.row_ptr[u + 1]; p++)
        {
            int v = G.col_idx[p];
            int w = G.values[p];

            if (u < v)
            {
                MSTEdge e;
                e.u = u;
                e.v = v;
                e.weight = w;
                edges.push_back(e);
            }
        }
    }

    sort(edges.begin(), edges.end(),
         [](const MSTEdge &a, const MSTEdge &b)
         {
             if (a.weight != b.weight)
                 return a.weight < b.weight;

             if (a.u != b.u)
                 return a.u < b.u;

             return a.v < b.v;
         });

    DSU dsu(G.V);

    for (size_t i = 0; i < edges.size(); i++)
    {
        if (dsu.unite(edges[i].u, edges[i].v))
        {
            result.edges.push_back(edges[i]);
            result.total_weight += edges[i].weight;

            if ((int)result.edges.size() == G.V - 1)
                break;
        }
    }

    result.connected = ((int)result.edges.size() == G.V - 1);

    return result;
}

MSTResult prim(const CSR &G)
{
    MSTResult result;

    if (G.V == 0)
        return result;

    const long long INF = 9223372036854775807LL;

    vector<long long> key(G.V, INF);
    vector<int> parent(G.V, -1);
    vector<char> in_mst(G.V, 0);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    key[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty())
    {
        pair<long long, int> current = pq.top();
        pq.pop();

        int u = current.second;

        if (in_mst[u])
            continue;

        in_mst[u] = 1;

        if (parent[u] != -1)
        {
            MSTEdge e;
            e.u = parent[u];
            e.v = u;
            e.weight = (int)key[u];

            result.edges.push_back(e);
            result.total_weight += e.weight;
        }

        for (int p = G.row_ptr[u]; p < G.row_ptr[u + 1]; p++)
        {
            int v = G.col_idx[p];
            int w = G.values[p];

            if (!in_mst[v] && (long long)w < key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    result.connected = ((int)result.edges.size() == G.V - 1);

    return result;
}
