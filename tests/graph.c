#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <graph.h>

struct test {
	i32 i;
	f32 f;
};

i32 i = 10;
i64 ii = 11;
f32 f = 12.0f;
f64 ff = 13.0f;
bool b = true;
struct test test = { .i = 14, .f = 15.0f };

Test(graph_tests, init) {
	Graph* graph = create_graph(5, true);
	cr_assert(graph != NULL);
}

Test(graph_tests, set_vertices) {
	Graph* graph = create_graph(10, true);

	Vertex* node_1 = insert_graph_vertex(graph, (void*)(uintptr_t) i);
	Vertex* node_2 = insert_graph_vertex(graph, (void*)(uintptr_t) ii);
	Vertex* node_3 = insert_graph_vertex(graph, (void*)(f32*) &f);
	Vertex* node_4 = insert_graph_vertex(graph, (void*)(f64*) &ff);
	Vertex* node_5 = insert_graph_vertex(graph, (void*)(bool*) &b);

	cr_assert(eq(i32, (i32)(uintptr_t) node_1->data, 10));
	cr_assert(eq(i64, (i64)(uintptr_t) node_2->data, 11));
	cr_assert(eq(flt, *(f32*) node_3->data, 12.0f));
	cr_assert(eq(dbl, *(f64*)node_4->data, 13.0f));
	cr_assert(eq(i32, *(bool*)node_5->data, true));

	cr_assert(eq(i32, node_1->index, 0));
	cr_assert(eq(i32, node_2->index, 1));
	cr_assert(eq(i32, node_3->index, 2));
	cr_assert(eq(i32, node_4->index, 3));
	cr_assert(eq(i32, node_5->index, 4));
}

Test(graph_tests, push_back_vertices) {
	Graph* graph = create_graph(3, true);

	Vertex* node_1 = insert_graph_vertex(graph, (void*)(uintptr_t) i);
	Vertex* node_2 = insert_graph_vertex(graph, (void*)(uintptr_t) ii);
	Vertex* node_3 = insert_graph_vertex(graph, (void*)(f32*) &f);
	Vertex* node_4 = insert_graph_vertex(graph, (void*)(f64*) &ff);
	Vertex* node_5 = insert_graph_vertex(graph, (void*)(bool*) &b);

	cr_assert(eq(i32, (i32)(uintptr_t) node_1->data, 10));
	cr_assert(eq(i64, (i64)(uintptr_t) node_2->data, 11));
	cr_assert(eq(flt, *(f32*) node_3->data, 12.0f));
	cr_assert(eq(dbl, *(f64*)node_4->data, 13.0f));
	cr_assert(eq(i32, *(bool*)node_5->data, true));

	cr_assert(eq(i32, node_1->index, 0));
	cr_assert(eq(i32, node_2->index, 1));
	cr_assert(eq(i32, node_3->index, 2));
	cr_assert(eq(i32, node_4->index, 3));
	cr_assert(eq(i32, node_5->index, 4));
}


Test(graph_tests, insert_edges) {
	Graph* graph = create_graph(5, true);

	Vertex* node_1 = insert_graph_vertex(graph, (void*)(uintptr_t) i);
	Vertex* node_2 = insert_graph_vertex(graph, (void*)(uintptr_t) ii);
	Vertex* node_3 = insert_graph_vertex(graph, (void*)(f32*) &f);
	Vertex* node_4 = insert_graph_vertex(graph, (void*)(f64*) &ff);
	Vertex* node_5 = insert_graph_vertex(graph, (void*)(bool*) &b);

	insert_graph_edge(graph, node_1, node_2);
	insert_graph_edge(graph, node_2, node_3);
	insert_graph_edge(graph, node_3, node_4);
	insert_graph_edge(graph, node_4, node_1);
	insert_graph_edge(graph, node_5, node_1);

	cr_assert(eq(i32, node_1->index, 0));
	cr_assert(eq(i32, node_2->index, 1));
	cr_assert(eq(i32, node_3->index, 2));
	cr_assert(eq(i32, node_4->index, 3));
	cr_assert(eq(i32, node_5->index, 4));
}
