#include <iostream>
#include <vector>
#include <algorithm>

#include "make_csr.h"

using namespace std;

struct edge
{
    int source;
    int destination;
    int weight;
};

void make_csr()
{
    FILE *input_fp = fopen("input_csr.txt", "r");

    if (input_fp == NULL)
    {
        cout << "[ERROR] Couldn't open input_csr.txt" << endl;
        return;
    }

    int vertices;
    int edges_count;
    int source;

    fscanf(input_fp,
           "%d %d %d",
           &vertices,
           &edges_count,
           &source);

    vector<edge> edges(edges_count);

    for (int i = 0; i < edges_count; i++)
    {
        fscanf(input_fp,
               "%d %d %d",
               &edges[i].source,
               &edges[i].destination,
               &edges[i].weight);
    }

    fclose(input_fp);

    sort(edges.begin(),
         edges.end(),
         [](edge a, edge b)
         {
             if (a.source == b.source)
                 return a.destination < b.destination;

             return a.source < b.source;
         });

    vector<int> row_ptr(vertices + 1, 0);
    vector<int> col_idx;
    vector<int> values;

    for (int i = 0; i < edges_count; i++)
        row_ptr[edges[i].source + 1]++;

    for (int i = 1; i <= vertices; i++)
        row_ptr[i] += row_ptr[i - 1];

    for (int i = 0; i < edges_count; i++)
    {
        col_idx.push_back(edges[i].destination);
        values.push_back(edges[i].weight);
    }

    cout << "\nCSR Representation\n\n";

    cout << "Vertices : " << vertices << endl;
    cout << "Edges    : " << edges_count << endl;
    cout << "Source   : " << source << endl;

    cout << "\nRow Pointer\n";

    for (int x : row_ptr)
        cout << x << " ";

    cout << "\n\nColumn Index\n";

    for (int x : col_idx)
        cout << x << " ";

    cout << "\n\nValues\n";

    for (int x : values)
        cout << x << " ";

    cout << endl;
}

