#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <vectors.h>
#include <ll.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct test {
	i32 i;
	f32 f;
};

i32 i = 10;
i64 ii = 10;
f32 f = 10.0f;
f64 ff = 10.0f;
bool b = true;
struct test test = { .i = 0, .f = 10.0f };

size_t vector_size = 10;

Test(vector_tests, init) {

	Vector *v = vector_init(vector_size);

	cr_assert(eq(i32, v->vector_list.capacity, vector_size));
	cr_assert(eq(i32, v->vector_list.total, 0));
	cr_assert(v->vector_list.elements != NULL);
}

Test(vector_tests, push_back) {

	Vector *v = vector_init(vector_size);

	i32 x = 10;
	i32 capacity = v->vector_list.capacity;
	i32 total = v->vector_list.total;

	for (size_t i = 0; i < 11; i++) {

		capacity = v->vector_list.capacity;
		total = v->vector_list.total;

		vector_push_back(v, (void*)(uintptr_t) x);

		if (total == capacity) {
			cr_assert(eq(i32, v->vector_list.capacity, vector_size * 2));
		}
		else {
			cr_assert(eq(i32, v->vector_list.capacity, vector_size));
		}
		cr_assert(eq(i32, v->vector_list.total, i + 1));
	}
}

Test(vector_tests, types) {

	Vector *v = vector_init(vector_size);

	List* list = ll_init();

	vector_push_back(v, (void*)(uintptr_t) i);
	vector_push_back(v, (void*)(uintptr_t) ii);
	vector_push_back(v, VOIDPTR(f));
	vector_push_back(v, VOIDPTR(ff));
	vector_push_back(v, VOIDPTR(b));
	vector_push_back(v, VOIDPTR(test));
	vector_push_back(v, (void*) list);

	cr_assert(eq(i32, (i32)(uintptr_t) vector_get(v, 0), 10));
	cr_assert(eq(i64, (i64)(uintptr_t) vector_get(v, 1), 10));
	cr_assert(eq(flt, CAST(f32, vector_get(v, 2)), 10.0f));
	cr_assert(eq(dbl, CAST(f64, vector_get(v, 3)), 10.0f));
	cr_assert(eq(i32, CAST(bool, vector_get(v, 4)), true));
	cr_assert(eq(i32, (CAST(List, vector_get(v, 5))).size, 0));
}

Test(vector_tests, set) {

	Vector *v = vector_init(vector_size);

	for (size_t index = 0; index < vector_size; index++) {
		vector_push_back(v, (void*)(uintptr_t) i);
	}

	vector_set(v, 0, (void*)(uintptr_t) i);
	vector_set(v, 1, (void*)(uintptr_t) ii);
	vector_set(v, 2, VOIDPTR(f));
	vector_set(v, 3, VOIDPTR(ff));
	vector_set(v, 4, VOIDPTR(b));
	vector_set(v, 5, VOIDPTR(test));

	cr_assert(eq(i32, (i32)(uintptr_t) vector_get(v, 0), 10));
	cr_assert(eq(i64, (i64)(uintptr_t) vector_get(v, 1), 10));
	cr_assert(eq(flt, CAST(f32, vector_get(v, 2)), 10.0f));
	cr_assert(eq(dbl, CAST(f64, vector_get(v, 3)), 10.0f));
	cr_assert(eq(i32, CAST(bool, vector_get(v, 4)), true));
	cr_assert(eq(i32, (CAST(List, vector_get(v, 5))).size, 0));
}

Test(vector_tests, is_set) {

	Vector *v = vector_init(vector_size);

	vector_set(v, 0, (void*)(uintptr_t) i);
	cr_assert(eq(i32, vector_is_set(v, 0), true));
	cr_assert(eq(i32, vector_total(v), 1));
	vector_set(v, 0, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, vector_total(v), 1));

	vector_set(v, 1, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, vector_is_set(v, 0), true));
	cr_assert(eq(i32, vector_total(v), 2));
	vector_set(v, 1, (void*)(uintptr_t) i);
	cr_assert(eq(i32, vector_total(v), 2));
}

Test(vector_tests, get) {

	Vector *v = vector_init(vector_size);

	vector_push_back(v, (void*)(uintptr_t) i);
	vector_push_back(v, (void*)(uintptr_t) ii);
	vector_push_back(v, VOIDPTR(f));
	vector_push_back(v, VOIDPTR(ff));
	vector_push_back(v, VOIDPTR(b));
	vector_push_back(v, VOIDPTR(test));

	cr_assert(eq(i32, (i32)(uintptr_t) vector_get(v, 0), 10));
	cr_assert(eq(i64, (i64)(uintptr_t) vector_get(v, 1), 10));
	cr_assert(eq(flt, CAST(f32, vector_get(v, 2)), 10.0f));
	cr_assert(eq(dbl, CAST(f64, vector_get(v, 3)), 10.0f));
	cr_assert(eq(i32, CAST(bool, vector_get(v, 4)), true));
}

Test(vector_tests, resize) {

	Vector *v = vector_init(1);

	vector_set(v, 0, (void*)(uintptr_t) i);

	cr_assert(eq(i32, vector_total(v), 1));
	cr_assert(eq(i32, vector_capacity(v), 1));

	vector_push_back(v, (void*)(uintptr_t) ii);

	cr_assert(eq(i32, vector_total(v), 2));
	cr_assert(eq(i32, vector_capacity(v), 2));

	vector_push_back(v, VOIDPTR(f));

	cr_assert(eq(i32, vector_total(v), 3));
	cr_assert(eq(i32, vector_capacity(v), 4));

	vector_push_back(v, VOIDPTR(ff));

	cr_assert(eq(i32, vector_total(v), 4));
	cr_assert(eq(i32, vector_capacity(v), 4));

	vector_push_back(v, VOIDPTR(b));

	cr_assert(eq(i32, vector_total(v), 5));
	cr_assert(eq(i32, vector_capacity(v), 8));

	vector_push_back(v, VOIDPTR(test));

	cr_assert(eq(i32, vector_total(v), 6));
	cr_assert(eq(i32, vector_capacity(v), 8));
}

Test(vector_tests, delete) {

	Vector *v = vector_init(vector_size);

	vector_push_back(v, (void*)(uintptr_t) i);
	vector_push_back(v, (void*)(uintptr_t) ii);
	vector_push_back(v, VOIDPTR(f));
	vector_push_back(v, VOIDPTR(ff));
	vector_push_back(v, VOIDPTR(b));
	vector_push_back(v, VOIDPTR(test));

	cr_assert(eq(i32, v->vector_list.total, 6));

	cr_assert(eq(i32, vector_delete(v, 5), 0));
	cr_assert(eq(i32, vector_delete(v, 4), 0));
	cr_assert(eq(i32, vector_delete(v, 3), 0));
	cr_assert(eq(i32, vector_delete(v, 2), 0));
	cr_assert(eq(i32, vector_delete(v, 1), 0));
	cr_assert(eq(i32, vector_delete(v, 0), 0));

	cr_assert(eq(i32, v->vector_list.total, 0));
}

Test(vector_tests, free) {

	Vector *v = vector_init(vector_size);

	vector_push_back(v, (void*)(uintptr_t) i);
	vector_push_back(v, (void*)(uintptr_t) ii);
	vector_push_back(v, VOIDPTR(f));
	vector_push_back(v, VOIDPTR(ff));
	vector_push_back(v, VOIDPTR(b));
	vector_push_back(v, VOIDPTR(test));

	cr_assert(eq(i32, vector_free(v), 0));
}

Test(vector_tests, total) {

	Vector *v = vector_init(vector_size);

	vector_push_back(v, (void*)(uintptr_t) i);
	cr_assert(eq(i32, vector_total(v), 1));

	vector_push_back(v, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, vector_total(v), 2));

	vector_push_back(v, VOIDPTR(f));
	cr_assert(eq(i32, vector_total(v), 3));

	vector_push_back(v, VOIDPTR(ff));
	cr_assert(eq(i32, vector_total(v), 4));

	vector_push_back(v, VOIDPTR(b));
	cr_assert(eq(i32, vector_total(v), 5));

	vector_push_back(v, VOIDPTR(test));
	cr_assert(eq(i32, vector_total(v), 6));
}

Test(vector_tests, zero_init) {

	Vector *v = vector_init(0);

	vector_push_back(v, (void*)(uintptr_t) i);
	cr_assert(eq(i32, vector_total(v), 1));

	vector_push_back(v, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, vector_total(v), 2));

	vector_push_back(v, VOIDPTR(f));
	cr_assert(eq(i32, vector_total(v), 3));

	vector_push_back(v, VOIDPTR(ff));
	cr_assert(eq(i32, vector_total(v), 4));

	vector_push_back(v, VOIDPTR(b));
	cr_assert(eq(i32, vector_total(v), 5));

	vector_push_back(v, VOIDPTR(test));
	cr_assert(eq(i32, vector_total(v), 6));
}
