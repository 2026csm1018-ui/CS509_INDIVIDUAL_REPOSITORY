#include "make_csr.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

bool make_csr(const char *input_path, CSR &G)
{
    FILE *fp = fopen(input_path, "r");

    if (fp == NULL)
    {
        cerr << "[ERROR] Cannot open input file: " << input_path << endl;
        return false;
    }

    int V, E;

    if (fscanf(fp, "%d %d", &V, &E) != 2)
    {
        cerr << "[ERROR] Invalid first line. Expected: V E" << endl;
        fclose(fp);
        return false;
    }

    if (V <= 0 || E < 0)
    {
        cerr << "[ERROR] Invalid V/E values." << endl;
        fclose(fp);
        return false;
    }

    G.V = V;
    G.E = E;

    G.row_ptr.clear();
    G.col_idx.clear();
    G.values.clear();

    G.row_ptr.push_back(0);

    /*
        Remove the remainder of the first line before using fgets().
    */
    char line[8192];
    fgets(line, sizeof(line), fp);

    for (int expected_vertex = 0; expected_vertex < V; expected_vertex++)
    {
        if (fgets(line, sizeof(line), fp) == NULL)
        {
            cerr << "[ERROR] Missing adjacency-list line for vertex "
                 << expected_vertex << endl;
            fclose(fp);
            return false;
        }

        char *token = strtok(line, " \t\r\n");

        if (token == NULL)
        {
            cerr << "[ERROR] Empty adjacency-list line for vertex "
                 << expected_vertex << endl;
            fclose(fp);
            return false;
        }

        int u = atoi(token);

        token = strtok(NULL, " \t\r\n");

        if (token == NULL)
        {
            cerr << "[ERROR] Missing degree for vertex " << u << endl;
            fclose(fp);
            return false;
        }

        int degree = atoi(token);

        if (u != expected_vertex || degree < 0)
        {
            cerr << "[ERROR] Invalid vertex/degree on line for vertex "
                 << expected_vertex << endl;
            fclose(fp);
            return false;
        }

        /*
            Each neighbour is represented by two integers:
                neighbour weight
        */
        for (int j = 0; j < degree; j++)
        {
            token = strtok(NULL, " \t\r\n");

            if (token == NULL)
            {
                cerr << "[ERROR] Missing neighbour for vertex " << u << endl;
                fclose(fp);
                return false;
            }

            int neighbour = atoi(token);

            token = strtok(NULL, " \t\r\n");

            if (token == NULL)
            {
                cerr << "[ERROR] Missing weight for vertex " << u << endl;
                fclose(fp);
                return false;
            }

            int weight = atoi(token);

            if (neighbour < 0 || neighbour >= V)
            {
                cerr << "[ERROR] Invalid neighbour " << neighbour
                     << " for vertex " << u << endl;
                fclose(fp);
                return false;
            }

            G.col_idx.push_back(neighbour);
            G.values.push_back(weight);
        }

        /*
            Any extra token means the declared degree did not match
            the number of neighbour/weight pairs.
        */
        token = strtok(NULL, " \t\r\n");

        if (token != NULL)
        {
            cerr << "[ERROR] Extra data on adjacency-list line for vertex "
                 << u << endl;
            fclose(fp);
            return false;
        }

        G.row_ptr.push_back((int)G.col_idx.size());
    }

    fclose(fp);

    /*
        For an undirected graph every edge appears twice in CSR.
        Therefore the number of CSR entries should be 2E.
    */
    if ((int)G.col_idx.size() != 2 * E)
    {
        cerr << "[ERROR] Edge count mismatch. Header E = " << E
             << ", adjacency entries = " << G.col_idx.size()
             << " (expected " << 2 * E << ")." << endl;
        return false;
    }

    return true;
}
