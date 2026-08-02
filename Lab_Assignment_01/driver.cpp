#include <iostream>
#include "matrix.h"
#include <filesystem>
namespace fs = std::filesystem;
#include "gemm_simple.h"
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
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

        matrix m3(m1.rows, m2.cols);
        argv[1]="SIMPLE MULTIPLICATION";
        long long exec_time = simple_multiplication(m1, m2, m3);

        string output_name =
            "Test_Cases/OUTPUT_FILES/" +
            a.stem().string() +
            "_output.txt";
        
        string algo_name = "SIMPLE_ALGO";
        FILE *output_fp = fopen(output_name.c_str(), "w");
        if (output_fp == NULL)
        {
            cout << "[ERROR] Could'nt open the file" << endl;
            return 1;
        }
        fprintf(output_fp, "Input File: %s\n",
                a.filename().string().c_str());

        fprintf(output_fp, "Alogrithm: %s\n", algo_name.c_str());
        fprintf(output_fp, "Execution Time: %lld microseconds", exec_time); 
        fprintf(output_fp, "Resultant Matrix:\n");
        m3.print_to_file(output_fp);
        fclose(output_fp);
    }
}