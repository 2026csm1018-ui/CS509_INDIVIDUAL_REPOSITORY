#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdio>

#include "make_csr.h"

using namespace std;

long long bell_ford(CSRGraph &G, FILE *output_fp);

long long floyd_warshall(CSRGraph &G, FILE *output_fp);

#endif