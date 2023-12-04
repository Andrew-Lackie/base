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

    Vector* adj_list = vector_init(n_vertices);

    if (graph == NULL) {
        LOG_WARN("create_graph: graph could not be allocated");
        return NULL;
    }

    graph->adj_list = *adj_list;
    graph->is_dir = is_dir;

    return graph;
}

/*
 * Insert/get vertices
 */

Vertex* insert_graph_vertex(Graph *graph, void* data)
{
    if (graph == NULL) {
        LOG_WARN("get_graph_vertex: graph is NULL");
        return NULL;
    }
    size_t v_total = vector_total(&graph->adj_list);

    Vertex* vertex = m_allocate(sizeof(Vertex), MEMORY_TAG_GRAPH);

    vertex->data = data;

    List* list = ll_init();

    ll_insert_begin(list, (void*) vertex);
    vertex->index = v_total;

    vector_add_next(&graph->adj_list, VOIDPTR(*list));

    return vertex;
}

Vertex* get_graph_vertex(Graph *graph, size_t index)
{
    if (graph == NULL) {
        LOG_WARN("get_graph_vertex: graph is NULL");
        return NULL;
    }

    return vector_get(&graph->adj_list, index);
}

/*
 * Insert/get edge
 */

i32 insert_graph_edge(Graph* graph, Vertex* v1, Vertex* v2)
{
    if (graph == NULL) {
        LOG_WARN("get_graph_vertex: graph is NULL");
        return -1;
    }
    else if (v1 == NULL || v2 == NULL) {
        LOG_WARN("insert_graph_edge: vertex is NULL");
        return -1;
    }
    else {
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
        return 0;
    }
}

/*
 * Remove vertex
 */

i32 remove_graph_vertex(Graph *graph, size_t index)
{
    i32 status;

    if (graph == NULL) {
        LOG_WARN("Attempting to remove vertex at position %lu in NULL graph", index);
        status = -1;
    }
    else {
        List* list = (List*) vector_get(&graph->adj_list, index);
        status = ll_remove_list(list);

        if (status != -1) {
            status = vector_set(&graph->adj_list, index, NULL);
        }
    }

    return status;
}

/*
 * Remove edge
 */

i32 remove_graph_edge(Graph *graph, size_t v_index, size_t ll_index)
{
    i32 status;
    if (graph == NULL) {
        LOG_WARN("Attempting to remove edge at position %lu,%lu in NULL graph.", v_index, ll_index);
        status = -1;
    }
    else {
        List* list = (List*) vector_get(&graph->adj_list, v_index);
        ll_remove_index(list, ll_index);
        status = 0;
    }
    return status;
}

/*
 * Remove graph
 */

i32 remove_graph(Graph *graph)
{
    i32 status;

    if (graph == NULL) {
        LOG_WARN("Attempting to remove NULL graph.");
        status = -1;
    }
    else {
        m_free(graph, sizeof(graph), MEMORY_TAG_GRAPH);
        status = vector_free(&graph->adj_list);
    }
    return status;
}
