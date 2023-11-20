#include <ll.h>

List* ll_init() {
	List* new_list = (List*)m_allocate(sizeof(List), MEMORY_TAG_LINKED_LIST);
	new_list->size = 0;
	new_list->head = NULL;
	return new_list;
}

Node* ll_insert_begin(List* list, void *value) {

	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	new_node->data = value;

	if (new_node == NULL) {
		exit(1);
	}

	if (list == NULL) {
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

Node* ll_insert_end(List* list, void *value) {
	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	Node* curr = list->head;
	new_node->data = value;

	if (new_node == NULL) {
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

Node* ll_insert_index(List* list, void *value, int index) {
	Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
	Node* curr = list->head;
	new_node->data = value;

	if (new_node == NULL) {
		exit(1);
	}

	new_node->next = NULL;

	if (index == 0) {
		new_node->next = list->head;
		list->head = new_node;
		list->size += 1;
		return list->head;
	}

	else if (index > list->size - 1) {
		LOG_FATAL("index %d not found", index);
		free(new_node);
		return NULL;
	}

	else {
		for (size_t i = 0; i < index - 1; i++) {
			curr = curr->next;
		}

		new_node->next = curr->next;
		curr->next = new_node;
		list->size += 1;
		return curr->next;
	}
}

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

i32 ll_remove_index(List* list, int index) {

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
