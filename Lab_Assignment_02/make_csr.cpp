#include "make_csr.h"
#include <cstdio>

bool make_csr(string input_path, CSRGraph &g)
{
    FILE *input_file;

    input_file = fopen(input_path.c_str(), "r");

    if (input_file == NULL)
    {
        cout << "[ERROR] Cannot open "
             << input_path << endl;

        return false;
    }

    if (fscanf(input_file,
               "%d %d %d",
               &g.V,
               &g.E,
               &g.source) != 3)
    {
        cout << "[ERROR] Invalid input file."
             << endl;

        fclose(input_file);

        return false;
    }

    if (g.V <= 0 || g.E < 0)
    {
        cout << "[ERROR] Invalid graph."
             << endl;

        fclose(input_file);

        return false;
    }

    if (g.source < 0 || g.source >= g.V)
    {
        cout << "[ERROR] Invalid source vertex."
             << endl;

        fclose(input_file);

        return false;
    }

    vector<edge> edges;

    edge e;

    for (int i = 0; i < g.E; i++)
    {
        if (fscanf(input_file,
                   "%d %d %d",
                   &e.source,
                   &e.destination,
                   &e.weight) != 3)
        {
            cout << "[ERROR] Invalid edge."
                 << endl;

            fclose(input_file);

            return false;
        }

        if (e.source < 0 ||
            e.source >= g.V ||
            e.destination < 0 ||
            e.destination >= g.V)
        {
            cout << "[ERROR] Invalid edge."
                 << endl;

            fclose(input_file);

            return false;
        }

        edges.push_back(e);
    }

    fclose(input_file);

    g.row_ptr.assign(g.V + 1, 0);

    vector<int> count(g.V, 0);

    for (int i = 0; i < edges.size(); i++)
    {
        count[edges[i].source]++;
    }

    for (int i = 1; i <= g.V; i++)
    {
        g.row_ptr[i] =
            g.row_ptr[i - 1] +
            count[i - 1];
    }

    g.col_idx.resize(g.E);
    g.values.resize(g.E);

    vector<int> position(
        g.row_ptr.begin(),
        g.row_ptr.end() - 1
    );

    for (int i = 0; i < edges.size(); i++)
    {
        int pos =
            position[edges[i].source];

        g.col_idx[pos] =
            edges[i].destination;

        g.values[pos] =
            edges[i].weight;

        position[edges[i].source]++;
    }

    return true;
}