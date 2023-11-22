#ifndef _DG_H
#define _DG_H

#include <stdbool.h>
#include <memory.h>
#include <vectors.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Graph Graph;

// Data structure to store vertex information

struct Vertex {
    size_t dest;
    size_t weight;
    void* data;
};

// Data structure to store a graph
struct Graph {
    vector adj_list;
    bool is_dir;
};

// Function to create a graph

Graph* create_graph(size_t n);

void add_edge_undir(Graph* graph, void *data_src, void *data_dest, size_t weight_src, size_t weight_dest, size_t src, size_t dest);

void add_edge_dir(Graph* graph, void *data_dest, size_t weight_dest, size_t src, size_t dest);

// Functions to traverse a graph



#endif
