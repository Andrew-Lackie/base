#include <graph.h>
#include <stdint.h>
#include <logger.h>
#include <ll.h>

/*
 * Create graph
 */

Graph* create_graph(size_t n_vertices, bool is_dir)
{
    Graph* graph = m_allocate(sizeof(Graph), MEMORY_TAG_GRAPH);

    VECTOR_INIT(adj_list, n_vertices);

    graph->adj_list = adj_list;
    graph->is_dir = is_dir;

    return graph;
}

/*
 * Insert vertices
 */

Vertex* insert_graph_vertex(Graph *graph, void* data)
{
    size_t v_total = vector_total(&graph->adj_list);
    size_t v_capacity = vector_capacity(&graph->adj_list);

    Vertex* vertex = m_allocate(sizeof(Vertex), MEMORY_TAG_GRAPH);

    vertex->data = data;

    List* list = ll_init();

    if (v_total < v_capacity) {
        ll_insert_begin(list, (void*) vertex);
        vector_set(&graph->adj_list, v_total, (void*) list);
        vertex->index = v_total;
    }
    else {
        ll_insert_begin(list, (void*) vertex);
        vector_push_back(&graph->adj_list, (void*) list);
        vertex->index = v_total;
    }

    return vertex;
}

/*
 * Insert edge
 */

void insert_graph_edge(Graph* graph, Vertex* v1, Vertex* v2)
{
    size_t v1_index = v1->index;
    size_t v2_index = v2->index;

    List* list_1 = (List*) vector_get(&graph->adj_list, v1_index);
    List* list_2 = (List*) vector_get(&graph->adj_list, v2_index);

    if (list_1 != NULL)
        ll_insert_end(list_1, v2);

    if (!graph->is_dir) {
        if (list_2 != NULL)
            ll_insert_end(list_2, v1);
    }
}

/*
 * Remove vertex
 */

i32 remove_graph_vertex(Graph *graph, size_t index)
{
    Vertex* vertex = (Vertex*) vector_get(&graph->adj_list, index);
    m_free(vertex, sizeof(vertex), MEMORY_TAG_GRAPH);

    return 0;
}

/*
 * Remove edge
 */

i32 remove_graph_edge(Graph *graph, size_t v_index, size_t ll_index)
{
    if (graph != NULL) {
        List* list = (List*) vector_get(&graph->adj_list, v_index);
        ll_remove_index(list, ll_index);
        return 0;
    }
    else {
        return -1;
    }
}

/*
 * Remove adjacency list
 */

i32 remove_graph_adj_list(Graph *graph)
{
    return vector_free(&graph->adj_list);
}

/*
 * Remove graph
 */

i32 remove_graph(Graph *graph)
{
    i32 status = 0;

    if (graph == NULL) {
        status = -1;
    }
    else {
        m_free(graph, sizeof(graph), MEMORY_TAG_GRAPH);
    }
    return status;
}
