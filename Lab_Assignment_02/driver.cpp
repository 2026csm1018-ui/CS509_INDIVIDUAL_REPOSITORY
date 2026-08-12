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

    if (choice != 1 &&
        choice != 2 &&
        choice != 3)
    {
        cout << "[ERROR] Invalid Choice." << endl;
        return 1;
    }

    /*
     * Main directories
     */

    string input_dir = "testcases/input";
    string output_dir = "testcases/outputs";

    /*
     * Check input directory
     */

    if (!fs::exists(input_dir))
    {
        cout << "[ERROR] Input directory not found: "
             << input_dir
             << endl;

        return 1;
    }

    /*
     * Create output directories
     */

    fs::create_directories(output_dir + "/bellmanford");
    fs::create_directories(output_dir + "/floydwarsal");

    /*
     * Process Bellman-Ford test cases
     */

    if (choice == 1 ||
        choice == 3)
    {
        string bf_input_dir =
            input_dir + "/bellmanford";

        string bf_output_dir =
            output_dir + "/bellmanford";

        if (!fs::exists(bf_input_dir))
        {
            cout << "[ERROR] Bellman-Ford input directory not found: "
                 << bf_input_dir
                 << endl;
        }
        else
        {
            vector<fs::path> files;

            for (const auto &entry :
                 fs::directory_iterator(bf_input_dir))
            {
                if (entry.is_regular_file())
                {
                    files.push_back(entry.path());
                }
            }

            sort(files.begin(), files.end());

            cout << "\n======================================"
                 << endl;
            cout << "Running Bellman-Ford"
                 << endl;
            cout << "======================================"
                 << endl;

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
                    cout << "[ERROR] Couldn't create CSR for "
                         << a.filename().string()
                         << endl;

                    continue;
                }

                /*
                 * Output file
                 *
                 * bf_10.txt
                 *      ->
                 * bf_10_output.txt
                 */

                string output_name =
                    bf_output_dir + "/" +
                    a.stem().string() +
                    "_output.txt";

                /*
                 * Open output file
                 */

                FILE *output_fp =
                    fopen(output_name.c_str(), "w");

                if (output_fp == NULL)
                {
                    cout << "[ERROR] Couldn't open output file: "
                         << output_name
                         << endl;

                    perror("fopen");

                    continue;
                }

                /*
                 * Write input information
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
                 * Run Bellman-Ford
                 */

                bell_ford(G, output_fp);

                fprintf(output_fp, "\n");

                fclose(output_fp);

                cout << "Output generated: "
                     << output_name
                     << endl;
            }
        }
    }

    /*
     * Process Floyd-Warshall test cases
     */

    if (choice == 2 ||
        choice == 3)
    {
        string fw_input_dir =
            input_dir + "/floydwarsal";

        string fw_output_dir =
            output_dir + "/floydwarsal";

        if (!fs::exists(fw_input_dir))
        {
            cout << "[ERROR] Floyd-Warshall input directory not found: "
                 << fw_input_dir
                 << endl;
        }
        else
        {
            vector<fs::path> files;

            for (const auto &entry :
                 fs::directory_iterator(fw_input_dir))
            {
                if (entry.is_regular_file())
                {
                    files.push_back(entry.path());
                }
            }

            sort(files.begin(), files.end());

            cout << "\n======================================"
                 << endl;
            cout << "Running Floyd-Warshall"
                 << endl;
            cout << "======================================"
                 << endl;

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
                    cout << "[ERROR] Couldn't create CSR for "
                         << a.filename().string()
                         << endl;

                    continue;
                }

                /*
                 * Output file
                 *
                 * fw_10.txt
                 *      ->
                 * fw_10_output.txt
                 */

                string output_name =
                    fw_output_dir + "/" +
                    a.stem().string() +
                    "_output.txt";

                /*
                 * Open output file
                 */

                FILE *output_fp =
                    fopen(output_name.c_str(), "w");

                if (output_fp == NULL)
                {
                    cout << "[ERROR] Couldn't open output file: "
                         << output_name
                         << endl;

                    perror("fopen");

                    continue;
                }

                /*
                 * Write input information
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
                 * Run Floyd-Warshall
                 */

                floyd_warshall(G, output_fp);

                fprintf(output_fp, "\n");

                fclose(output_fp);

                cout << "Output generated: "
                     << output_name
                     << endl;
            }
        }
    }

    cout << "\n======================================"
         << endl;
    cout << "All selected test cases processed."
         << endl;
    cout << "======================================"
         << endl;

    return 0;
}