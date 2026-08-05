#include <iostream>
#include "matrix.h"
#include <filesystem>
namespace fs = std::filesystem;
#include "gemm_simple.h"
#include "gemm_blocking.h"
#include "make_csr.h"
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int choice;

    cout << "======================================" << endl;
    cout << "1. Matrix Multiplication" << endl;
    cout << "2. CSR Representation" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    if (choice == 1)
    {
        int dim[3];
        vector<fs::path> files;

        for (const auto &entry : fs::directory_iterator("Test_Cases/INPUT_FILES"))
            files.push_back(entry.path());

        sort(files.begin(), files.end());

        for (const auto &a : files)
        {
            FILE *input_fp = fopen(a.string().c_str(), "r");
            if (input_fp == NULL)
            {
                cout << "[ERROR] Could'nt open the file" << endl;
                return 1;
            }

            fscanf(input_fp, "%d %d %d", &dim[0], &dim[1], &dim[2]);

            matrix m1(dim[0], dim[1]), m2(dim[1], dim[2]);

            m1.populate_mat(input_fp);
            m2.populate_mat(input_fp);

            fclose(input_fp);

            string output_name =
                "Test_Cases/OUTPUT_FILES/" +
                a.stem().string() +
                "_output.txt";

            FILE *output_fp = fopen(output_name.c_str(), "w");
            if (output_fp == NULL)
            {
                cout << "[ERROR] Could'nt open the file" << endl;
                return 1;
            }

            fprintf(output_fp, "Input File: %s\n",
                    a.filename().string().c_str());

            /************* SIMPLE MULTIPLICATION *************/

            matrix m3(m1.rows, m2.cols);

            long long exec_time =
                simple_multiplication(m1, m2, m3);

            string algo_name = "SIMPLE_ALGO";

            fprintf(output_fp, "Algorithm: %s\n", algo_name.c_str());
            fprintf(output_fp, "Execution Time: %lld microseconds\n", exec_time);
            fprintf(output_fp, "Resultant Matrix:\n");
            m3.print_to_file(output_fp);

            fprintf(output_fp, "\n");

            /************* BLOCKING MULTIPLICATION *************/

            matrix m4(m1.rows, m2.cols);

            exec_time =
                blocking_multiplication(m1, m2, m4);

            algo_name = "BLOCKING_ALGO";

            fprintf(output_fp, "Algorithm: %s\n", algo_name.c_str());
            fprintf(output_fp, "Execution Time: %lld microseconds\n", exec_time);
            fprintf(output_fp, "Resultant Matrix:\n");
            m4.print_to_file(output_fp);

            fclose(output_fp);
        }

        cout << "\nOutput files generated successfully." << endl;
    }
    else if (choice == 2)
    {
        make_csr();
    }
    else
    {
        cout << "[ERROR] Invalid Choice." << endl;
    }

    return 0;
}