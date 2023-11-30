#include <ll.h>
#include <memory.h>
#include <logger.h>

/*
 * Create list
 */

List* ll_init() {
	List* new_list = m_allocate(sizeof(List), MEMORY_TAG_LINKED_LIST);
	new_list->size = 0;
	new_list->head = NULL;
	return new_list;
}

/*
 * Insert Nodes
 */

Node* ll_insert_begin(List* list, void* value) {

	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	new_node->data = value;

	if (new_node == NULL) {
		LOG_ERROR("Linked list node could not be properly allocated in ll_insert_begin");
		exit(1);
	}
	else if (list == NULL) {
		list->head = new_node;
		list->size += 1;
		return new_node;
	}
	else {
		new_node->next = list->head;
		list->head = new_node;
		list->size += 1;
		return list->head;
	}
}

Node* ll_insert_end(List* list, void* value) {
	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	Node* curr = list->head;
	new_node->data = value;

	if (new_node == NULL) {
		LOG_ERROR("Linked list node could not be properly allocated in ll_insert_end");
		exit(1);
	}

	if (list->head == NULL) {
		list->head = new_node;
		list->size += 1;
		return new_node;
	}
	else {
		while(curr->next != NULL) {
			curr = curr->next;
		}

		curr->next = new_node;
		list->size += 1;

		return new_node;
	}
}

Node* ll_insert_index(List* list, void* value, size_t index) {
	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	Node* curr = list->head;
	new_node->data = value;

	if (new_node == NULL) {
		LOG_ERROR("Linked list node could not be properly allocated in ll_insert_index");
		exit(1);
	}

	new_node->next = NULL;

	if (index == 0) {
		return ll_insert_begin(list, value);
	}
	else if (index == list->size) {
		return ll_insert_end(list, value);
	}
	else if (index > list->size) {
		LOG_FATAL("index %d not found", index);
		free(new_node);
		return NULL;
	}
	else {
		for (size_t i = 0; i < index; i++) {
			curr = curr->next;
		}

		new_node->next = curr->next;
		curr->next = new_node;
		list->size += 1;
		return curr->next;
	}
}

/*
 * Get Nodes
 */

Node* ll_get_begin(List* list) {

	if (list == NULL) {
		LOG_WARN("List is null; returning null");
		return NULL;
	}

	return list->head;
}

Node* ll_get_end(List* list) {

	if (list == NULL) {
		LOG_WARN("List is null; returning null");
		return NULL;
	}
	else {
		Node* curr = ll_get_begin(list);

		while(curr->next != NULL) {
			curr = curr->next;
		}

		return curr;
	}
}

Node* ll_get_index(List* list, size_t index) {
	Node* curr = ll_get_begin(list);

	if (list == NULL) {
		LOG_WARN("List is null; returning null");
		curr = NULL;
	}
	else if (index > list->size - 1) {
		LOG_FATAL("index %d not found", index);
		curr = NULL;
	}
	else if (index == 0) {
		curr = ll_get_begin(list);
	}
	else if (index == list->size - 1) {
		curr = ll_get_end(list);
	}
	else {
		for (size_t i = 0; i < index; i++) {
			curr = curr->next;
		}
	}
	return curr;
}

/*
 * Remove Nodes
 */

i32 ll_remove_begin(List* list) {

	i32 status;

	Node *curr;

	if (list->head == NULL) {
		LOG_INFO("List is empty");
		status = -1;
	}
	else {
		curr = list->head;
		list->head = curr->next;
		free(curr);
		status = 0;
	}
	return status;
}

i32 ll_remove_end(List* list) {

	i32 status;

	Node *curr;
	Node *temp = list->head;

	if (temp == NULL) {
		LOG_INFO("List is empty");
		status = -1;
	}
	else if (temp->next == NULL) {
		list->head = NULL;
		LOG_INFO("List is empty");
		free(temp);
		status = -1;
	}
	else {

		while (temp->next != NULL) {
			curr = temp;
			temp = temp->next;
		}

		curr->next = NULL;
		free(temp);
		status = 0;
	}
	return status;
}

i32 ll_remove_index(List* list, size_t index) {

	i32 status;

	Node *curr = list->head;
	Node *temp;

	if (curr == NULL) {
		LOG_INFO("List is empty");
		status = -1;
	}
	else if (curr->next == NULL) {
		curr = NULL;
		LOG_INFO("List is empty");
		status = -1;
	}

	else {

		if (index == 0) {
			temp = curr;
			curr = curr->next;
			free(temp);
			status = 0;
		}
		else if (index > list->size - 1) {
			LOG_FATAL("index %d not found", index);
			status = -1;
		}
		else {
			for (size_t i = 0; i < index; i++) {
				temp = curr;
				curr = curr->next;
			}
			temp->next = curr->next;
			free(curr);
			status = 0;
		}
	}
	return status;
}

/*
 * Remove List
 */

i32 ll_remove_list(List* list) {

	i32 status = 0;

	Node* curr = ll_get_begin(list);
	Node* node;

	while(curr->next != NULL) {
		node = curr;
		curr = node->next;
		m_free(node, sizeof(node), MEMORY_TAG_NODE);
	}

	return status;
}
