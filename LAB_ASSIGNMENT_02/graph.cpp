#include "graph.h"
#include <vector>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

long long bell_ford(CSRGraph &G, FILE *output_fp)
{
    const int INF = INT_MAX;

    vector<int> dist(G.V, INF);

    dist[G.source] = 0;

    auto start = high_resolution_clock::now();

    // Relax all edges V-1 times
    for (int k = 0; k < G.V - 1; k++)
    {
        bool updated = false;

        // Traverse every vertex
        for (int u = 0; u < G.V; u++)
        {
            if (dist[u] == INF)
                continue;

            // Traverse all outgoing edges of u using CSR
            for (int i = G.row_ptr[u];
                 i < G.row_ptr[u + 1];
                 i++)
            {
                int v = G.col_idx[i];
                int w = G.values[i];

                // Relaxation
                if (dist[u] + w < dist[v])
                {
                    dist[v] =
                        dist[u] + w;

                    updated = true;
                }
            }
        }

        // No update means shortest distances are already final
        if (!updated)
            break;
    }

    // Check for negative-weight cycle
    bool negative_cycle = false;

    for (int u = 0; u < G.V; u++)
    {
        if (dist[u] == INF)
            continue;

        for (int i = G.row_ptr[u];
             i < G.row_ptr[u + 1];
             i++)
        {
            int v = G.col_idx[i];
            int w = G.values[i];

            if (dist[u] + w < dist[v])
            {
                negative_cycle = true;
                break;
            }
        }

        if (negative_cycle)
            break;
    }

    auto end = high_resolution_clock::now();

    long long exec_time =
        duration_cast<microseconds>(
            end - start
        ).count();


    fprintf(output_fp,
            "Algorithm: BELLMAN_FORD\n");

    fprintf(output_fp,
            "Source: %d\n",
            G.source);

    fprintf(output_fp,
            "Execution Time: %lld microseconds\n",
            exec_time);


    if (negative_cycle)
    {
        fprintf(output_fp,
                "Negative Weight Cycle: YES\n");
    }
    else
    {
        fprintf(output_fp,
                "Negative Weight Cycle: NO\n");

        fprintf(output_fp,
                "Shortest Distances:\n");

        for (int v = 0; v < G.V; v++)
        {
            if (dist[v] == INF)
            {
                fprintf(output_fp,
                        "%d INF\n",
                        v);
            }
            else
            {
                fprintf(output_fp,
                        "%d %d\n",
                        v,
                        dist[v]);
            }
        }
    }

    return exec_time;
}

long long floyd_warshall(CSRGraph &G, FILE *output_fp)
{
    const int INF = INT_MAX;

    auto start = high_resolution_clock::now();

    // Distance matrix
    vector<vector<int>> dist(
        G.V,
        vector<int>(G.V, INF)
    );

    // Distance from a vertex to itself
    for (int i = 0; i < G.V; i++)
    {
        dist[i][i] = 0;
    }

    // Convert CSR edges into distance matrix
    for (int u = 0; u < G.V; u++)
    {
        for (int i = G.row_ptr[u];
             i < G.row_ptr[u + 1];
             i++)
        {
            int v = G.col_idx[i];
            int w = G.values[i];

            // In case multiple edges exist
            // between the same vertices
            if (w < dist[u][v])
            {
                dist[u][v] = w;
            }
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < G.V; k++)
    {
        for (int i = 0; i < G.V; i++)
        {
            if (dist[i][k] == INF)
                continue;

            for (int j = 0; j < G.V; j++)
            {
                if (dist[k][j] == INF)
                    continue;

                if (dist[i][k] + dist[k][j]
                    < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] +
                        dist[k][j];
                }
            }
        }
    }

    // Check for negative-weight cycle
    bool negative_cycle = false;

    for (int i = 0; i < G.V; i++)
    {
        if (dist[i][i] < 0)
        {
            negative_cycle = true;
            break;
        }
    }

    auto end = high_resolution_clock::now();

    long long exec_time =
        duration_cast<microseconds>(
            end - start
        ).count();


    fprintf(output_fp,
            "Algorithm: FLOYD_WARSHALL\n");

    fprintf(output_fp,
            "Execution Time: %lld microseconds\n",
            exec_time);


    if (negative_cycle)
    {
        fprintf(output_fp,
                "Negative Weight Cycle: YES\n");
    }
    else
    {
        fprintf(output_fp,
                "Negative Weight Cycle: NO\n");

        fprintf(output_fp,
                "Shortest Distance Matrix:\n");

        for (int i = 0; i < G.V; i++)
        {
            for (int j = 0; j < G.V; j++)
            {
                if (dist[i][j] == INF)
                {
                    fprintf(output_fp,
                            "INF ");
                }
                else
                {
                    fprintf(output_fp,
                            "%d ",
                            dist[i][j]);
                }
            }

            fprintf(output_fp, "\n");
        }
    }

    return exec_time;
}