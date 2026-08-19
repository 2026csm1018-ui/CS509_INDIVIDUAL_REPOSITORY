#ifndef MST_H
#define MST_H

#include "make_csr.h"
#include <vector>

using namespace std;

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    vector<MSTEdge> edges;
    long long total_weight;
    bool connected;

    MSTResult()
    {
        total_weight = 0;
        connected = false;
    }
};

/*
    Kruskal and Prim both receive the prepared CSR graph.

    No file reading is performed inside these functions.
*/
MSTResult kruskal(const CSR &G);
MSTResult prim(const CSR &G);

#endif
