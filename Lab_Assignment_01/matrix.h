#ifndef MATRIX_H
#define MATRIX_H
#include<vector>

class matrix
{
public:
    int rows;
    int cols;
    std::vector<std::vector<int>> mat;
    matrix(int, int);
    void display();
    void populate_mat(FILE *fp);
    void print_to_file(FILE *);
};
#endif