#include <stddef.h>

#include "priority_queue.h"

// Helper functions for binary heap operations
static void swap_elements(priority_queue_element_t* a, priority_queue_element_t* b)
{
    priority_queue_element_t temp = *a;

    *a = *b;
    *b = temp;
}

static void heapify_up(priority_queue_t* queue, int index)
{
    if (index == 0){
        return;
    }

    int parent = (index - 1) / 2;

    if (queue->elements[index].priority > queue->elements[parent].priority) {
        swap_elements(&queue->elements[index], &queue->elements[parent]);
        heapify_up(queue, parent);
    }
}

static void heapify_down(priority_queue_t* queue, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->size && queue->elements[left].priority > queue->elements[largest].priority) {
        largest = left;
    }

    if (right < queue->size && queue->elements[right].priority > queue->elements[largest].priority) {
        largest = right;
    }

    if (largest != index) {
        swap_elements(&queue->elements[index], &queue->elements[largest]);
        heapify_down(queue, largest);
    }
}

status_t priority_queue_init(priority_queue_t* queue)
{
    if (queue == NULL) {
        return FAILURE;
    }

    queue->size = 0;

    return SUCCESS;
}

int priority_queue_is_empty(const priority_queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return queue->size == 0;
}

int priority_queue_is_full(const priority_queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return queue->size == PRIORITY_QUEUE_MAX_SIZE;
}

status_t priority_queue_enqueue(priority_queue_t* queue, void* data, int priority)
{
    if (queue == NULL || priority_queue_is_full(queue)) {
        return FAILURE;
    }

    // Add new element at the end
    queue->elements[queue->size].data = data;
    queue->elements[queue->size].priority = priority;
    queue->size++;

    // Maintain heap property
    heapify_up(queue, queue->size - 1);

    return SUCCESS;
}

status_t priority_queue_dequeue(priority_queue_t* queue, void** data, int* priority)
{
    if (queue == NULL || data == NULL || priority == NULL || priority_queue_is_empty(queue)) {
        return FAILURE;
    }

    // Get the highest priority element (root)
    *data = queue->elements[0].data;
    *priority = queue->elements[0].priority;

    // Move last element to root and decrease size
    queue->elements[0] = queue->elements[queue->size - 1];
    queue->size--;

    // Maintain heap property
    if (queue->size > 0) {
        heapify_down(queue, 0);
    }

    return SUCCESS;
}

status_t priority_queue_peek(const priority_queue_t* queue, void** data, int* priority)
{
    if (queue == NULL || data == NULL || priority == NULL || priority_queue_is_empty(queue)) {
        return FAILURE;
    }

    *data = queue->elements[0].data;
    *priority = queue->elements[0].priority;

    return SUCCESS;
}

int priority_queue_size(const priority_queue_t* queue)
{
    if (queue == NULL) {
        return 0;
    }

    return queue->size;
}