/**
 * @file queue.c
 * @brief Implementation of regular queue (FIFO) operations
 * @details This file contains the implementation of all regular queue operations
 *          using circular array indexing for efficient memory utilization.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Implementation Details:
 *      - Uses circular array with front/rear pointers
 *      - Count variable tracks current number of elements
 *      - Efficient O(1) operations for all queue functions
 *      - Prevents buffer overflow through proper bounds checking
 *
 * @note All functions include proper error checking and boundary validation
 * @see queue.h for API documentation
 */

#include <stddef.h>

#include "queue.h"

status_t queue_init(queue_t* queue)
{
    if (queue == NULL) {
        return FAILURE;
    }

    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;

    return SUCCESS;
}

int queue_is_empty(const queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return queue->count == 0;
}

int queue_is_full(const queue_t* queue)
{
    if (queue == NULL) {
        return 1;
    }

    return queue->count == QUEUE_MAX_SIZE;
}

status_t queue_enqueue(queue_t* queue, void* data)
{
    if (queue == NULL || queue_is_full(queue)) {
        return FAILURE;
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % QUEUE_MAX_SIZE;
    queue->count++;

    return SUCCESS;
}

status_t queue_dequeue(queue_t* queue, void** data)
{
    if (queue == NULL || data == NULL || queue_is_empty(queue)) {
        return FAILURE;
    }

    *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_MAX_SIZE;
    queue->count--;

    return SUCCESS;
}

status_t queue_peek(const queue_t* queue, void** data)
{
    if (queue == NULL || data == NULL || queue_is_empty(queue)) {
        return FAILURE;
    }

    *data = queue->data[queue->front];

    return SUCCESS;
}

int queue_size(const queue_t* queue)
{
    if (queue == NULL) {
        return 0;
    }

    return queue->count;
}