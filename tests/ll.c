#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <ll.h>
#include <stdio.h>

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

Test(ll_tests, init) {
	List* list = ll_init();
	cr_assert(list != NULL);
}

Test(ll_tests, insert_get_begin) {
	List* list = ll_init();

	ll_insert_begin(list, (void*)(uintptr_t) i);
	cr_assert(eq(i32, (i32)(uintptr_t) ll_get_begin(list)->data, 10)); // ERROR

	ll_insert_begin(list, (void*)(uintptr_t) ii);
	cr_assert(eq(i64, (i64)(uintptr_t) ll_get_begin(list)->data, 11));

	ll_insert_begin(list, (void*)(f32*) &f);
	cr_assert(eq(flt, *(f32*) ll_get_begin(list)->data, 12.0f));

	ll_insert_begin(list, (void*)(f64*) &ff);
	cr_assert(eq(i64, *(f64*) ll_get_begin(list)->data, 13.0f));

	ll_insert_begin(list, (void*)(bool*) &b);
	cr_assert(eq(i32, *(bool*) ll_get_begin(list)->data, true));

	ll_insert_begin(list, (void*) &test);
	cr_assert(eq(i32, (*(struct test*) ll_get_begin(list)->data).i, 14));
}

Test(ll_tests, insert_get_end) {
	List* list = ll_init();

	ll_insert_end(list, (void*)(uintptr_t) i);
	cr_assert(eq(i32, (i32)(uintptr_t) ll_get_end(list)->data, 10)); // ERROR

	ll_insert_end(list, (void*)(uintptr_t) ii);
	cr_assert(eq(i64, (i64)(uintptr_t) ll_get_end(list)->data, 11));

	ll_insert_end(list, (void*)(f32*) &f);
	cr_assert(eq(flt, *(f32*) ll_get_end(list)->data, 12.0f));

	ll_insert_end(list, (void*)(f64*) &ff);
	cr_assert(eq(i64, *(f64*) ll_get_end(list)->data, 13.0f));

	ll_insert_end(list, (void*)(bool*) &b);
	cr_assert(eq(i32, *(bool*) ll_get_end(list)->data, true));

	ll_insert_end(list, (void*) &test);
	cr_assert(eq(i32, (*(struct test*) ll_get_end(list)->data).i, 14));
}

Test(ll_tests, insert_get_index) {
	List* list = ll_init();

	ll_insert_index(list, (void*)(uintptr_t) i, 0);
	cr_assert(eq(i32, (i32)(uintptr_t) ll_get_index(list, 0)->data, 10)); // ERROR

	ll_insert_index(list, (void*)(uintptr_t) ii, 1);
	cr_assert(eq(i64, (i64)(uintptr_t) ll_get_index(list, 1)->data, 11));

	ll_insert_index(list, (void*)(f32*) &f, 2);
	cr_assert(eq(flt, *(f32*) ll_get_index(list, 2)->data, 12.0f));

	ll_insert_index(list, (void*)(f64*) &ff, 3);
	cr_assert(eq(i64, *(f64*) ll_get_index(list, 3)->data, 13.0f));

	ll_insert_index(list, (void*)(bool*) &b, 4);
	cr_assert(eq(i32, *(bool*) ll_get_index(list, 4)->data, true));

	ll_insert_index(list, (void*) &test, 5);
	cr_assert(eq(i32, (*(struct test*) ll_get_index(list, 5)->data).i, 14));
}
