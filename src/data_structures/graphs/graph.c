#include <graph.h>
#include <logger.h>
#include <ll.h>

static Vertex* create_vertex(void *data, size_t weight, size_t dest)
{
    Vertex *vertex = m_allocate(sizeof(Vertex), MEMORY_TAG_GRAPH);

    vertex->dest = dest;
    vertex->weight = weight;
    vertex->data = data;

    return vertex;
}

static vector create_adj_list(size_t n_vertices)
{
    VECTOR_INIT(adj_list, n_vertices);

    for (size_t i = 0; i < n_vertices; i++) {
        VECTOR_ADD(adj_list, ll_init());
    }

    return adj_list;
}

Graph* create_graph(size_t n)
{
    Graph* graph = m_allocate(sizeof(Graph), MEMORY_TAG_GRAPH);

    graph->adj_list = create_adj_list(n);

    return graph;
}

void add_edge_undir(Graph *graph, void *data_src, void *data_dest, size_t weight_src, size_t weight_dest, size_t src, size_t dest)
{
    Vertex* vertex = create_vertex(data_dest, weight_dest, dest);
    ll_insert_end(VECTOR_GET(graph->adj_list, List*, src), vertex);

    if (!(graph->is_dir)) {
        Vertex* vertex = create_vertex(data_src, weight_src, src);
        ll_insert_end(VECTOR_GET(graph->adj_list, List*, dest), vertex);
    }
    else {
        LOG_WARN("Adding a directed edge to an undirected graph. Please use the function add_edge_undir or change the graph's state.");
    }

}

void add_edge_dir(Graph *graph, void *data_dest, size_t weight_dest, size_t src, size_t dest)
{
    vector adj_list = graph->adj_list;

    Vertex* vertex = create_vertex(data_dest, weight_dest, dest);
    ll_insert_end(VECTOR_GET(adj_list, List*, src), vertex);

    if (!(graph->is_dir)) {
        LOG_WARN("Adding an undirected edge to a directed graph. Please use the function add_edge_dir or change the graph's state.");
    }
}
