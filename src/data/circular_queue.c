#include <stddef.h>

#include "circular_queue.h"

status_t circular_queue_init(circular_queue_t* queue)
{
    if (queue == NULL) {
        return FAILURE;
    }

    queue->front = 0;
    queue->rear = 0;
    queue->is_full = 0;

    return SUCCESS;
}

int circular_queue_is_empty(const circular_queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return (!queue->is_full && (queue->front == queue->rear));
}

int circular_queue_is_full(const circular_queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return queue->is_full;
}

status_t circular_queue_enqueue(circular_queue_t* queue, void* data)
{
    if (queue == NULL || circular_queue_is_full(queue)) {
        return FAILURE;
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % CIRCULAR_QUEUE_MAX_SIZE;

    if (queue->rear == queue->front) {
        queue->is_full = 1;
    }

    return SUCCESS;
}

status_t circular_queue_dequeue(circular_queue_t* queue, void** data)
{
    if (queue == NULL || data == NULL || circular_queue_is_empty(queue)) {
        return FAILURE;
    }

    *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % CIRCULAR_QUEUE_MAX_SIZE;
    queue->is_full = 0;

    return SUCCESS;
}

status_t circular_queue_peek(const circular_queue_t* queue, void** data)
{
    if (queue == NULL || data == NULL || circular_queue_is_empty(queue)) {
        return FAILURE;
    }

    *data = queue->data[queue->front];

    return SUCCESS;
}

int circular_queue_size(const circular_queue_t* queue)
{
    if (queue == NULL) {
        return 0;
    }

    if (circular_queue_is_full(queue)) {
        return CIRCULAR_QUEUE_MAX_SIZE;
    }

    if (circular_queue_is_empty(queue)) {
        return 0;
    }

    if (queue->rear >= queue->front) {
        return queue->rear - queue->front;
    } else {
        return CIRCULAR_QUEUE_MAX_SIZE - queue->front + queue->rear;
    }
}