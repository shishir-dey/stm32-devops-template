#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

#include "common_types.h"

#define PRIORITY_QUEUE_MAX_SIZE 100

typedef struct {
    void* data;
    int priority;
} priority_queue_element_t;

typedef struct {
    priority_queue_element_t elements[PRIORITY_QUEUE_MAX_SIZE];
    int size;
} priority_queue_t;

/**
 * @brief Initializes the priority queue.
 *
 * @param queue Pointer to the priority queue to be initialized.
 * @return status_t SUCCESS if initialization is successful, FAILURE otherwise.
 */
status_t priority_queue_init(priority_queue_t* queue);

/**
 * @brief Checks if the priority queue is empty.
 *
 * @param queue Pointer to the priority queue.
 * @return int 1 if empty, 0 otherwise.
 */
int priority_queue_is_empty(const priority_queue_t* queue);

/**
 * @brief Checks if the priority queue is full.
 *
 * @param queue Pointer to the priority queue.
 * @return int 1 if full, 0 otherwise.
 */
int priority_queue_is_full(const priority_queue_t* queue);

/**
 * @brief Enqueues an element with priority to the priority queue.
 *
 * @param queue Pointer to the priority queue.
 * @param data Pointer to the data to be enqueued.
 * @param priority Priority of the element (higher number = higher priority).
 * @return status_t SUCCESS if enqueue is successful, FAILURE otherwise.
 */
status_t priority_queue_enqueue(priority_queue_t* queue, void* data, int priority);

/**
 * @brief Dequeues the highest priority element from the priority queue.
 *
 * @param queue Pointer to the priority queue.
 * @param data Pointer to store the dequeued data.
 * @param priority Pointer to store the priority of the dequeued element.
 * @return status_t SUCCESS if dequeue is successful, FAILURE otherwise.
 */
status_t priority_queue_dequeue(priority_queue_t* queue, void** data, int* priority);

/**
 * @brief Peeks at the highest priority element without dequeuing it.
 *
 * @param queue Pointer to the priority queue.
 * @param data Pointer to store the front data.
 * @param priority Pointer to store the priority of the front element.
 * @return status_t SUCCESS if peek is successful, FAILURE otherwise.
 */
status_t priority_queue_peek(const priority_queue_t* queue, void** data, int* priority);

/**
 * @brief Gets the current size of the priority queue.
 *
 * @param queue Pointer to the priority queue.
 * @return int Current number of elements in the priority queue.
 */
int priority_queue_size(const priority_queue_t* queue);

#endif // PRIORITY_QUEUE_H