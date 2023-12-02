#include <stack.h>
#include <memory.h>
#include <logger.h>

/*
 * Initialize stack
 */

Stack* stack_init(IMPL_TYPE type, size_t capacity)
{
	Stack* stack = m_allocate(sizeof(Stack), MEMORY_TAG_STACK);
	if (stack == NULL) {
		LOG_WARN("stack_init: could not allocate stack");
		return NULL;
	}

	if (type == LL) {
		stack->ll = ll_init();
		stack->impl_type = LL;
	}
	else if (type == VECTOR) {
		VECTOR_INIT(vec, capacity);
		stack->vec = vec;
		stack->impl_type = VECTOR;
	}
	else {
		LOG_ERROR("stack_init: invalid IMPL_TYPE flag");
		return NULL;
	}

	return stack;
}

i32 stack_push(Stack* stack, void* data)
{
	if (stack == NULL) {
		LOG_ERROR("stack_push: stack is NULL");
		return -1;
	}

	if (stack->impl_type == LL) {
		return ll_insert_begin(stack->ll, data) == NULL ? -1 : 0;
	}
	else if (stack->impl_type == VECTOR) {
    size_t v_total = vector_total(&stack->vec);
    size_t v_capacity = vector_capacity(&stack->vec);

    if (v_total < v_capacity) {
        return vector_set(&stack->vec, v_total, data);
    }
    else {
        return vector_push_back(&stack->vec, data);
    }
	}
	else {
		LOG_ERROR("stack_push: invalid IMPL_TYPE flag");
		return -1;
	}
}

i32 stack_pop(Stack* stack)
{
	if (stack == NULL) {
		LOG_ERROR("stack_pop: stack is NULL");
		return -1;
	}

	if (stack->impl_type == LL) {
		return ll_remove_begin(stack->ll);
	}
	else if (stack->impl_type == VECTOR)
		return vector_delete(&stack->vec, vector_total(&stack->vec) - 1);
	else {
		LOG_ERROR("stack_pop: invalid IMPL_TYPE flag");
		return -1;
	}
}

void* stack_show(Stack* stack)
{
	if (stack == NULL) {
		LOG_ERROR("stack_is_show: stack is NULL");
		return NULL;
	}
	if (stack->impl_type == LL)
		return stack_is_empty(stack) ? NULL : ((Node*)ll_get_begin(stack->ll))->data;
	else if (stack->impl_type == VECTOR)
		return stack_is_empty(stack) ? NULL : vector_get(&stack->vec, vector_total(&stack->vec) - 1);
	else {
		LOG_ERROR("stack_show: invalid IMPL_TYPE flag");
		return NULL;
	}
}

bool stack_is_empty(Stack* stack)
{
	if (stack == NULL) {
		LOG_ERROR("stack_is_empty: stack is NULL");
		return -1;
	}
	if (stack->impl_type == LL)
		return ll_total(stack->ll) == 0;
	else if (stack->impl_type == VECTOR)
		return vector_total(&stack->vec) == 0;
	else {
		LOG_ERROR("stack_is_empty: invalid IMPL_TYPE flag");
		return NULL;
	}
}

i32 stack_remove(Stack* stack)
{
	if (stack == NULL) {
		LOG_ERROR("stack_remove: stack is NULL");
		return -1;
	}
	if (stack->impl_type == LL) {
		m_free(stack,sizeof(Stack), MEMORY_TAG_STACK);
		return ll_remove_list(stack->ll);
	}
	else if (stack->impl_type == VECTOR) {
		m_free(stack,sizeof(Stack), MEMORY_TAG_STACK);
		return vector_free(&stack->vec);
	}
	else {
		LOG_ERROR("remove_stack: invalid IMPL_TYPE flag");
		return -1;
	}
}
