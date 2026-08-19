#include <cstdio>
#include <cstring>
#include <iostream>
#include <chrono>
#include <filesystem>

#include "make_csr.h"
#include "mst.h"

using namespace std;
namespace fs = std::filesystem;

void print_result(FILE *out,
                  const char *algorithm_name,
                  const MSTResult &result,
                  long long time_us)
{
    fprintf(out, "Algorithm: %s\n", algorithm_name);

    if (!result.connected)
    {
        fprintf(out, "Status: FAIL - graph is not connected\n\n");
        fprintf(out, "Execution time: %lld microseconds\n", time_us);
        return;
    }

    fprintf(out, "MST edges:\n");

    for (size_t i = 0; i < result.edges.size(); i++)
    {
        fprintf(out,
                "%d %d %d\n",
                result.edges[i].u,
                result.edges[i].v,
                result.edges[i].weight);
    }

    fprintf(out, "Total MST weight: %lld\n", result.total_weight);
    fprintf(out, "Execution time: %lld microseconds\n\n", time_us);
}

bool process_test_case(const fs::path &input_path, int choice)
{
    fs::path output_dir = "testcases/outputs/mst";

    fs::create_directories(output_dir);

    string filename = input_path.filename().string();

    string output_filename =
        input_path.stem().string() + "_output.txt";

    fs::path output_path =
        output_dir / output_filename;

    CSR G;

    if (!make_csr(input_path.string().c_str(), G))
    {
        cerr << "[SKIP] Invalid input: "
             << input_path << endl;
        return false;
    }

    FILE *out = fopen(output_path.string().c_str(), "w");

    if (out == NULL)
    {
        cerr << "[ERROR] Cannot open output file: "
             << output_path << endl;
        return false;
    }

    fprintf(out, "========================================\n");
    fprintf(out, "Test Case: %s\n", filename.c_str());
    fprintf(out, "Vertices: %d\n", G.V);
    fprintf(out, "Edges: %d\n", G.E);
    fprintf(out, "========================================\n\n");

    MSTResult kruskal_result;
    MSTResult prim_result;

    long long kruskal_time = 0;
    long long prim_time = 0;

    if (choice == 1 || choice == 3)
    {
        auto start = chrono::high_resolution_clock::now();

        kruskal_result = kruskal(G);

        auto finish = chrono::high_resolution_clock::now();

        kruskal_time =
            chrono::duration_cast<chrono::microseconds>
            (finish - start).count();

        print_result(out,
                     "Kruskal's MST",
                     kruskal_result,
                     kruskal_time);
    }

    if (choice == 2 || choice == 3)
    {
        auto start = chrono::high_resolution_clock::now();

        prim_result = prim(G);

        auto finish = chrono::high_resolution_clock::now();

        prim_time =
            chrono::duration_cast<chrono::microseconds>
            (finish - start).count();

        print_result(out,
                     "Prim's MST",
                     prim_result,
                     prim_time);
    }

    if (choice == 3)
    {
        fprintf(out, "Comparison:\n");
        fprintf(out, "----------------------------------------\n");

        if (kruskal_result.connected &&
            prim_result.connected)
        {
            fprintf(out,
                    "Kruskal MST Weight : %lld\n",
                    kruskal_result.total_weight);

            fprintf(out,
                    "Prim MST Weight    : %lld\n",
                    prim_result.total_weight);

            fprintf(out,
                    "Same MST Weight    : %s\n",
                    (kruskal_result.total_weight ==
                     prim_result.total_weight)
                        ? "YES"
                        : "NO");
        }
        else
        {
            fprintf(out, "MST could not be completed.\n");
        }

        fprintf(out, "\n");
    }

    fclose(out);

    cout << "[OK] "
         << input_path
         << " -> "
         << output_path
         << endl;

    return true;
}

int main()
{
    int choice;

    cout << "========================================\n";
    cout << "        CS509 - Assignment 3\n";
    cout << "        Minimum Spanning Tree\n";
    cout << "========================================\n\n";

    cout << "1. Kruskal's Algorithm\n";
    cout << "2. Prim's Algorithm\n";
    cout << "3. Both Algorithms\n";
    cout << "4. Exit\n\n";

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 4)
        return 0;

    if (choice < 1 || choice > 3)
    {
        cerr << "[ERROR] Invalid choice.\n";
        return 1;
    }

    fs::path input_dir = "testcases/input/mst";

    if (!fs::exists(input_dir) ||
        !fs::is_directory(input_dir))
    {
        cerr << "[ERROR] Input directory does not exist: "
             << input_dir << endl;
        return 1;
    }

    int processed = 0;

    for (const auto &entry : fs::directory_iterator(input_dir))
    {
        if (!entry.is_regular_file())
            continue;

        if (entry.path().extension() != ".txt")
            continue;

        if (process_test_case(entry.path(), choice))
            processed++;
    }

    cout << "\nProcessed "
         << processed
         << " MST test cases.\n";

    return 0;
}