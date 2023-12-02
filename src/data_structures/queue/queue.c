#include <queue.h>
#include <memory.h>
#include <logger.h>

Queue* create_queue() {
    Queue* q = m_allocate(sizeof(struct Queue), MEMORY_TAG_QUEUE);
    if (q == NULL) {
      LOG_ERROR("create_queue: could not allocate queue");
      return NULL;
    }
    q->front = q->end = NULL;
    return q;
}

Node* enqueue(Queue* q, void *value) {

    Node* new_node = m_allocate(sizeof(Node), MEMORY_TAG_NODE);
    Node* curr = q->end;
    new_node->data = value;

    if (new_node == NULL) {
      LOG_ERROR("enqueue: could not allocate node");
      return NULL;
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
		LOG_INFO("dequeue: list is empty");
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
