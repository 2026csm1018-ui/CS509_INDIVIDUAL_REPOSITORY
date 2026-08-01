#include <iostream>
#include "matrix.h"
using namespace std;

int main(int argc, char **argv)
{

    int dim[3];
    FILE *input_fp = fopen(argv[1], "r");
    fscanf(input_fp, "%d %d %d", &dim[0], &dim[1], &dim[2]);
    matrix m1(dim[0], dim[1]), m2(dim[1], dim[2]);
    m1.populate_mat(input_fp);
    m2.populate_mat(input_fp);
    m1.display();
    m2.display();
    fclose(input_fp);
}