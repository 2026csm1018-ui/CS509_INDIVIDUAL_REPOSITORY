#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdio>

#include "graph.h"
#include "make_csr.h"

namespace fs = std::filesystem;

using namespace std;

int main(int argc, char **argv)
{
    int choice;

    cout << "======================================" << endl;
    cout << "1. Bellman-Ford" << endl;
    cout << "2. Floyd-Warshall" << endl;
    cout << "3. Both Algorithms" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice : ";

    cin >> choice;

    if (choice == 1 ||
        choice == 2 ||
        choice == 3)
    {
        vector<fs::path> files;

        for (const auto &entry :
             fs::directory_iterator("testcase/input"))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path());
            }
        }

        sort(files.begin(), files.end());

        for (const auto &a : files)
        {
            cout << "\nProcessing: "
                 << a.filename().string()
                 << endl;

            /*
             * Build CSR
             */

            CSRGraph G;

            if (!make_csr(a.string(), G))
            {
                cout << "[ERROR] Could'nt create CSR for "
                     << a.filename().string()
                     << endl;

                continue;
            }

            /*
             * Create output file name
             *
             * test1.txt
             *      ->
             * test1_output.txt
             */

            string output_name =
                "testcase/output/" +
                a.stem().string() +
                "_output.txt";

            /*
             * Open output file
             */

            FILE *output_fp =
                fopen(output_name.c_str(), "w");

            if (output_fp == NULL)
            {
                cout << "[ERROR] Could'nt open output file: "
                     << output_name
                     << endl;

                perror("fopen");

                continue;
            }

            /*
             * Write input file information
             */

            fprintf(output_fp,
                    "Input File: %s\n",
                    a.filename().string().c_str());

            fprintf(output_fp,
                    "Vertices: %d\n",
                    G.V);

            fprintf(output_fp,
                    "Edges: %d\n",
                    G.E);

            fprintf(output_fp,
                    "Source: %d\n\n",
                    G.source);

            /*
             * BELLMAN-FORD
             */

            if (choice == 1 ||
                choice == 3)
            {
                bell_ford(G, output_fp);

                fprintf(output_fp, "\n");
            }

            /*
             * FLOYD-WARSHALL
             */

            if (choice == 2 ||
                choice == 3)
            {
                floyd_warshall(G, output_fp);

                fprintf(output_fp, "\n");
            }

            fclose(output_fp);

            cout << "Output generated: "
                 << output_name
                 << endl;
        }

        cout << "\nOutput files generated successfully."
             << endl;
    }
    else
    {
        cout << "[ERROR] Invalid Choice."
             << endl;
    }

    return 0;
}