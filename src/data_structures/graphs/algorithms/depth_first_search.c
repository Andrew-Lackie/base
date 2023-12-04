#include <graph.h>
#include <stack.h>
#include <stdbool.h>
#include <logger.h>

static bool vertex_visited(Vector* visited, size_t index)
{
    return CAST(bool, vector_get(visited, index));
}

static Edge* edge_is_null(Graph* graph, Vector* visited)
{
    bool visit;
    List* list;
    Edge* edge;
    Vertex* vertex;
    for (size_t i = 0; i < vector_capacity(visited); i++) {
        list = (List*) vector_get(&graph->adj_list, i);
        edge = ll_get_begin(list);
        vertex = (Vertex*) edge->data;
        visit = vertex_visited(visited, vertex->index);
        if (!visit) {
            return edge;
        }
    }
    return NULL;
}

static Edge *dfs(Graph* graph, Vector* visited, Edge* edge, Stack* vertices)
{
    if (edge == NULL) return edge_is_null(graph, visited);

    bool visit;
    size_t index = ((Vertex*) edge->data)->index;
    visit = vertex_visited(visited, index);

    if (visit) {
        return ll_get_next(edge);
    }
    else {
        visit = true;

        size_t new_vertex_index = CAST(Vertex, edge->data).index;
        Node* new_list = vector_get(&graph->adj_list, new_vertex_index);

        vector_set(visited, new_vertex_index, VOIDPTR(visit));

        stack_push(vertices, edge->data);

        Edge* new_edge = ll_get_next((Edge*) new_list);

        if (new_edge == NULL) return edge_is_null(graph, visited);

        return new_edge;
    }
}

Stack* dfs_graph(Graph* graph, size_t root, size_t nodes, IMPL_TYPE type)
{
    Vector *visited = vector_init(nodes);
    for (size_t i = 0; i < nodes; i++) {
        bool state = false;
        vector_set(visited, i, VOIDPTR(state));
    }

    Stack *vertices = stack_init(type, nodes);

    Edge *edge = ll_get_begin((List*) vector_get(&graph->adj_list, root));

    while (edge != NULL) {
        edge = dfs(graph, visited, edge, vertices);
    }
    vector_free(visited);

    return vertices;
}
