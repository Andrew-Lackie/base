#include <queue.h>

Queue* create_queue() {
    Queue* q = m_allocate(sizeof(struct Queue), MEMORY_TAG_QUEUE);
    q->front = q->end = NULL;
    return q;
}

Node* enqueue(Queue* q, void *value) {

    Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
    Node* curr = q->end;
    new_node->data = value;

    if (new_node == NULL) {
      exit(1);
    }

    if (q->end == NULL) {
      q->end = new_node;
      q->size += 1;
      return new_node;
    }
    else {
      while(curr->next != NULL) {
        curr = curr->next;
      }

      curr->next = new_node;
      q->size += 1;
      q->front = q->end = new_node;
    }

	return new_node;
}

void dequeue(Queue* q) {
	Node *curr = q->front;

	if (curr == NULL) {
		LOG_INFO("List is empty");
	}
  else if (q->front == q->end) {
    q->front = q->end = NULL;
    free(curr);
  }
	else {
		q->front = curr->next;
		free(curr);
	}
}
