#include <iostream>
#include "matrix.h"
#include "gem_simple.h"
using namespace std;

int main(int argc, char **argv)
{

    int dim[3];
    FILE *input_fp = fopen(argv[1], "r");
    if(input_fp==NULL){
       cout<<"[ERROR] Could'nt open the file"<<endl;
       return 1;
    }

    fscanf(input_fp, "%d %d %d", &dim[0], &dim[1], &dim[2]);
    matrix m1(dim[0], dim[1]), m2(dim[1], dim[2]);
    m1.populate_mat(input_fp);
    m2.populate_mat(input_fp);
    fclose(input_fp);
    
    matrix m3(m1.rows, m2.cols);
   long long exec_time = simple_multiplication(m1,m2,m3);
   FILE *output_fp = fopen("output.txt","a");
   if(output_fp==NULL){
       cout<<"[ERROR] Could'nt open the file"<<endl;
       return 1;
    }
    fprintf(output_fp,"Alogrithm: %s\n",argv[2]);
    fprintf(output_fp,"Resultant Matrix:\n");
    m3.print_to_file(output_fp);
    fprintf(output_fp,"Execution Time: %lld microseconds",exec_time);
    fclose(output_fp);
    
}