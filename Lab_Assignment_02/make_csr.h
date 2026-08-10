#ifndef MAKE_CSR_H
#define MAKE_CSR_H

#include <iostream>
#include <vector>

using namespace std;

struct edge
{
    int source;
    int destination;
    int weight;
};

struct CSRGraph
{
    int V;
    int E;
    int source;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;

    CSRGraph()
    {
        V = 0;
        E = 0;
        source = 0;
    }
};

bool make_csr(string input_path, CSRGraph &g);

#endif