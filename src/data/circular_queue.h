#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>

#include "common_types.h"

#define CIRCULAR_QUEUE_MAX_SIZE 100

typedef struct {
    void* data[CIRCULAR_QUEUE_MAX_SIZE];
    int front;
    int rear;
    int is_full;
} circular_queue_t;

/**
 * @brief Initializes the circular queue.
 *
 * @param queue Pointer to the circular queue to be initialized.
 * @return status_t SUCCESS if initialization is successful, FAILURE otherwise.
 */
status_t circular_queue_init(circular_queue_t* queue);

/**
 * @brief Checks if the circular queue is empty.
 *
 * @param queue Pointer to the circular queue.
 * @return int 1 if empty, 0 otherwise.
 */
int circular_queue_is_empty(const circular_queue_t* queue);

/**
 * @brief Checks if the circular queue is full.
 *
 * @param queue Pointer to the circular queue.
 * @return int 1 if full, 0 otherwise.
 */
int circular_queue_is_full(const circular_queue_t* queue);

/**
 * @brief Enqueues an element to the circular queue.
 *
 * @param queue Pointer to the circular queue.
 * @param data Pointer to the data to be enqueued.
 * @return status_t SUCCESS if enqueue is successful, FAILURE otherwise.
 */
status_t circular_queue_enqueue(circular_queue_t* queue, void* data);

/**
 * @brief Dequeues an element from the circular queue.
 *
 * @param queue Pointer to the circular queue.
 * @param data Pointer to store the dequeued data.
 * @return status_t SUCCESS if dequeue is successful, FAILURE otherwise.
 */
status_t circular_queue_dequeue(circular_queue_t* queue, void** data);

/**
 * @brief Peeks at the front element without dequeuing it.
 *
 * @param queue Pointer to the circular queue.
 * @param data Pointer to store the front data.
 * @return status_t SUCCESS if peek is successful, FAILURE otherwise.
 */
status_t circular_queue_peek(const circular_queue_t* queue, void** data);

/**
 * @brief Gets the current size of the circular queue.
 *
 * @param queue Pointer to the circular queue.
 * @return int Current number of elements in the circular queue.
 */
int circular_queue_size(const circular_queue_t* queue);

#endif // CIRCULAR_QUEUE_H