#ifndef _DG_H
#define _DG_H

#include <stdbool.h>
#include <memory.h>
#include <vectors.h>
#include <stack.h>
#include <ll.h>

typedef struct Vertex Vertex;
typedef struct Adj_List Adj_List;
typedef struct Graph Graph;
typedef struct Node Edge;

struct Vertex {
    void* data;
    size_t index;
};

struct Graph {
    Vector adj_list;
    size_t edges;
    size_t vertices;
    bool is_dir;
};

/*
 * Create graph
 */

Graph* create_graph(size_t n_vertices, bool is_dir);

/*
 * Create/get vertex
 */

Vertex* insert_graph_vertex(Graph *graph, void* data);

Vertex* get_graph_vertex(Graph *graph, size_t index);

/*
 * Insert edges
 */

i32 insert_graph_edge(Graph *graph, Vertex* v1, Vertex* v2);

/*
 * Remove vertex
 */

i32 remove_graph_vertex(Graph *graph, size_t index);

/*
 * Remove edge
 */

i32 remove_graph_edge(Graph *graph, size_t src, size_t dest);

/*
 * Remove graph
 */

i32 remove_graph(Graph *graph);

/*
 * Searching algorithms
 */

Stack* dfs_graph(Graph* graph, size_t root, size_t nodes, IMPL_TYPE type);

#endif
