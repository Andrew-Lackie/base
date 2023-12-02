#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stack.h>
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

Test(ll_stack_tests, init) {
	Stack* stack = stack_init(LL, 0);
	cr_assert(stack != NULL);
}

Test(ll_stack_tests, push) {
	Stack* stack = stack_init(LL, 0);
	i32 status;

	status = stack_push(stack, (void*)(uintptr_t) i);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, (i32)(uintptr_t) stack_show(stack), 10));

	status = stack_push(stack, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i64, (i64)(uintptr_t) stack_show(stack), 11));

	status = stack_push(stack, (void*)(f32*) &f);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(flt, *(f32*) stack_show(stack), 12.0f));

	status = stack_push(stack, (void*)(f64*) &ff);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i64, *(f64*) stack_show(stack), 13.0f));

	status = stack_push(stack, (void*)(bool*) &b);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, *(bool*) stack_show(stack), true));

	status = stack_push(stack, (void*) &test);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, (*(struct test*) stack_show(stack)).i, 14));
}

Test(ll_stack_tests, pop) {
	Stack* stack = stack_init(LL, 0);

	stack_push(stack, (void*)(uintptr_t) i);
	stack_push(stack, (void*)(uintptr_t) ii);
	stack_push(stack, (void*)(f32*) &f);
	stack_push(stack, (void*)(f64*) &ff);
	stack_push(stack, (void*)(bool*) &b);
	stack_push(stack, (void*) &test);


	cr_assert(eq(i32, (*(struct test*) stack_show(stack)).i, 14));

	stack_pop(stack);

	cr_assert(eq(i32, *(bool*) stack_show(stack), true));

	stack_pop(stack);
	cr_assert(eq(i64, *(f64*) stack_show(stack), 13.0f));

	stack_pop(stack);
	cr_assert(eq(flt, *(f32*) stack_show(stack), 12.0f));

	stack_pop(stack);
	cr_assert(eq(i64, (i64)(uintptr_t) stack_show(stack), 11));

	stack_pop(stack);
	cr_assert(eq(i32, (i32)(uintptr_t) stack_show(stack), 10));

	stack_pop(stack);
	cr_assert(stack_show(stack) == NULL);
}

Test(ll_stack_tests, is_empty) {
	Stack* stack = stack_init(LL, 0);

	stack_push(stack, (void*)(uintptr_t) i);
	stack_push(stack, (void*)(uintptr_t) ii);
	stack_push(stack, (void*)(f32*) &f);
	stack_push(stack, (void*)(f64*) &ff);
	stack_push(stack, (void*)(bool*) &b);
	stack_push(stack, (void*) &test);

	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 0));

	stack_pop(stack);
	cr_assert(eq(i32, stack_is_empty(stack), 1));
}

Test(v_stack_tests, init) {
	Stack* stack = stack_init(VECTOR, 10);
	cr_assert(stack != NULL);
}

Test(v_stack_tests, push) {
	Stack* stack = stack_init(VECTOR, 10);
	i32 status;

	status = stack_push(stack, (void*)(uintptr_t) i);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, (i32)(uintptr_t) stack_show(stack), 10));

	status = stack_push(stack, (void*)(uintptr_t) ii);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i64, (i64)(uintptr_t) stack_show(stack), 11));

	status = stack_push(stack, (void*)(f32*) &f);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(flt, *(f32*) stack_show(stack), 12.0f));

	status = stack_push(stack, (void*)(f64*) &ff);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(dbl, *(f64*) stack_show(stack), 13.0f));

	status = stack_push(stack, (void*)(bool*) &b);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, *(bool*) stack_show(stack), true));

	status = stack_push(stack, (void*) &test);
	cr_assert(eq(i32, status, 0));
	cr_assert(eq(i32, (*(struct test*) stack_show(stack)).i, 14));
}

Test(v_stack_tests, pop) {
	Stack* stack = stack_init(VECTOR, 10);

	stack_push(stack, (void*)(uintptr_t) i);
	stack_push(stack, (void*)(uintptr_t) ii);
	stack_push(stack, (void*)(f32*) &f);
	stack_push(stack, (void*)(f64*) &ff);
	stack_push(stack, (void*)(bool*) &b);
	stack_push(stack, (void*) &test);

	cr_assert(eq(i32, (*(struct test*) stack_show(stack)).i, 14));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 10));
	cr_assert(eq(i32, *(bool*) stack_show(stack), true));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 10));
	cr_assert(eq(dbl, *(f64*) stack_show(stack), 13.0f));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 10));
	cr_assert(eq(flt, *(f32*) stack_show(stack), 12.0f));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 5));
	cr_assert(eq(i64, (i64)(uintptr_t) stack_show(stack), 11));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 2));
	cr_assert(eq(i32, (i32)(uintptr_t) stack_show(stack), 10));

	stack_pop(stack);
	cr_assert(eq(i32, vector_capacity(&stack->vec), 2));
	cr_assert(stack_show(stack) == NULL);
}

/*Test(v_stack_tests, is_empty) {*/
	/*Stack* stack = stack_init(VECTOR, 10);*/

	/*stack_push(stack, (void*)(uintptr_t) i);*/
	/*stack_push(stack, (void*)(uintptr_t) ii);*/
	/*stack_push(stack, (void*)(f32*) &f);*/
	/*stack_push(stack, (void*)(f64*) &ff);*/
	/*stack_push(stack, (void*)(bool*) &b);*/
	/*stack_push(stack, (void*) &test);*/

	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 0));*/

	/*stack_pop(stack);*/
	/*cr_assert(eq(i32, stack_is_empty(stack), 1));*/
/*}*/
