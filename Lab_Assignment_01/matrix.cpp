#include <iostream>
#include <vector>
using namespace std;

class matrix
{
public:
    int rows;
    int cols;
    vector<vector<int>> mat;
    matrix(int, int);
    void display();
    void populate_mat(FILE *fp);
    void print_to_file(FILE *);
};
matrix::matrix(int r, int c)
{
    rows = r;
    cols = c;
    mat = vector<vector<int>>(rows, vector<int>(cols, 0));
}

void matrix::display()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

void matrix::print_to_file(FILE *fp)
{
    for (int i = 0; i < rows; i++)
    {    for (int j = 0; j < cols; j++)
        {
            fprintf(fp, "%d ", mat[i][j]);
        }
        fprintf(fp,"\n");
    }
}

void matrix::populate_mat(FILE *fp)
{
    int buffer_size = rows * cols;
    int temp[buffer_size];
    int i = 0;
    while (i < buffer_size)
    {
        fscanf(fp, "%d", &temp[i++]);
    }
    i = 0;
    for (int p = 0; p < rows; p++)
        for (int q = 0; q < cols; q++)
            mat[p][q] = temp[i++];
}
