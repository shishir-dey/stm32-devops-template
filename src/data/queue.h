#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "common_types.h"

#define QUEUE_MAX_SIZE 100

typedef struct {
    void* data[QUEUE_MAX_SIZE];
    int front;
    int rear;
    int count;
} queue_t;

/**
 * @brief Initializes the queue.
 *
 * @param queue Pointer to the queue to be initialized.
 * @return status_t SUCCESS if initialization is successful, FAILURE otherwise.
 */
status_t queue_init(queue_t* queue);

/**
 * @brief Checks if the queue is empty.
 *
 * @param queue Pointer to the queue.
 * @return int 1 if empty, 0 otherwise.
 */
int queue_is_empty(const queue_t* queue);

/**
 * @brief Checks if the queue is full.
 *
 * @param queue Pointer to the queue.
 * @return int 1 if full, 0 otherwise.
 */
int queue_is_full(const queue_t* queue);

/**
 * @brief Enqueues an element to the rear of the queue.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the data to be enqueued.
 * @return status_t SUCCESS if enqueue is successful, FAILURE otherwise.
 */
status_t queue_enqueue(queue_t* queue, void* data);

/**
 * @brief Dequeues an element from the front of the queue.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to store the dequeued data.
 * @return status_t SUCCESS if dequeue is successful, FAILURE otherwise.
 */
status_t queue_dequeue(queue_t* queue, void** data);

/**
 * @brief Peeks at the front element without dequeuing it.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to store the front data.
 * @return status_t SUCCESS if peek is successful, FAILURE otherwise.
 */
status_t queue_peek(const queue_t* queue, void** data);

/**
 * @brief Gets the current size of the queue.
 *
 * @param queue Pointer to the queue.
 * @return int Current number of elements in the queue.
 */
int queue_size(const queue_t* queue);

#endif // QUEUE_H