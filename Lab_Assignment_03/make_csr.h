#ifndef MAKE_CSR_H
#define MAKE_CSR_H

#include <vector>

using namespace std;

/*
    CSR representation for a weighted graph.

    row_ptr:
        row_ptr[u]       -> first edge of vertex u
        row_ptr[u + 1]   -> one past the last edge of vertex u

    col_idx:
        destination/neighbour vertex for each CSR entry

    values:
        edge weight corresponding to col_idx
*/
class CSR
{
public:
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;

    CSR()
    {
        V = 0;
        E = 0;
    }
};

/*
    Reads the weighted undirected adjacency-list file and
    converts it into CSR.

    File handling deliberately uses C-style FILE/fopen/fgets/fscanf/fprintf
    as preferred for this assignment.
*/
bool make_csr(const char *input_path, CSR &G);

#endif
