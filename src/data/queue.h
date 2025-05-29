/**
 * @file queue.h
 * @brief Regular Queue (FIFO) implementation for embedded systems
 * @details This header provides a First-In-First-Out (FIFO) queue implementation
 *          using static memory allocation. The queue is suitable for embedded
 *          systems where dynamic memory allocation should be avoided.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Key Features:
 *      - Static memory allocation (no malloc/free)
 *      - FIFO (First-In-First-Out) behavior
 *      - Circular array implementation for efficiency
 *      - Configurable maximum size via QUEUE_MAX_SIZE
 *      - Thread-safe operations (when used with proper locking)
 *
 * @par Performance Characteristics:
 *      - Enqueue: O(1)
 *      - Dequeue: O(1)
 *      - Peek: O(1)
 *      - Size check: O(1)
 *
 * @note Include this header to use the regular queue functionality
 * @warning Ensure QUEUE_MAX_SIZE is appropriate for your memory constraints
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "common_types.h"

/**
 * @defgroup RegularQueue Regular Queue (FIFO) Implementation
 * @brief Static memory FIFO queue for embedded systems
 *
 * This module provides a regular queue implementation that follows the
 * First-In-First-Out (FIFO) principle. It's designed for embedded systems
 * where predictable memory usage and no dynamic allocation are required.
 *
 * @par Use Cases:
 *      - UART receive buffers
 *      - Task scheduling queues
 *      - Event processing systems
 *      - Command queues for protocols
 *      - Data logging buffers
 *
 * @{
 */

/**
 * @brief Maximum number of elements the queue can hold
 * @details This compile-time constant defines the maximum capacity of the queue.
 *          It can be modified based on system memory constraints and requirements.
 *
 * @note Increasing this value will increase memory usage proportionally
 * @warning Must be greater than 0 and should fit within available RAM
 */
#define QUEUE_MAX_SIZE 100

/**
 * @brief Queue data structure
 * @details This structure maintains the queue state including the data array,
 *          front and rear pointers, and element count. The implementation uses
 *          circular indexing for efficient memory utilization.
 *
 * @par Structure Layout:
 *      - data[]: Array to store queue elements
 *      - front: Index of the first element to be dequeued
 *      - rear: Index where the next element will be enqueued
 *      - count: Current number of elements in the queue
 *
 * @note All members should be considered private and accessed only through API functions
 * @warning Direct modification of structure members may lead to undefined behavior
 */
typedef struct {
    void* data[QUEUE_MAX_SIZE];
    int front;
    int rear;
    int count;
} queue_t;

/**
 * @brief Initializes the queue to an empty state
 * @details Sets up the queue structure with initial values. Must be called
 *          before any other queue operations.
 *
 * @param[out] queue Pointer to the queue structure to initialize
 * @return status_t SUCCESS if initialization successful, FAILURE if queue pointer is NULL
 *
 * @par Example:
 * @code
 * queue_t my_queue;
 * if (queue_init(&my_queue) == SUCCESS) {
 *     // Queue is ready to use
 * }
 * @endcode
 *
 * @note This function must be called before any other queue operations
 * @warning Passing a NULL pointer will result in FAILURE return value
 */
status_t queue_init(queue_t* queue);

/**
 * @brief Checks if the queue is empty
 * @details Determines whether the queue contains any elements.
 *
 * @param[in] queue Pointer to the queue to check
 * @return int 1 if queue is empty or NULL, 0 if queue contains elements
 *
 * @par Example:
 * @code
 * if (queue_is_empty(&my_queue)) {
 *     // Queue has no elements
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 */
int queue_is_empty(const queue_t* queue);

/**
 * @brief Checks if the queue is full
 * @details Determines whether the queue has reached its maximum capacity.
 *
 * @param[in] queue Pointer to the queue to check
 * @return int 1 if queue is full or NULL, 0 if queue has available space
 *
 * @par Example:
 * @code
 * if (!queue_is_full(&my_queue)) {
 *     // Safe to enqueue more elements
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 */
int queue_is_full(const queue_t* queue);

/**
 * @brief Adds an element to the rear of the queue
 * @details Inserts a new element at the rear of the queue following FIFO principles.
 *          The element will be the last to be dequeued.
 *
 * @param[in,out] queue Pointer to the queue structure
 * @param[in] data Pointer to the data to be enqueued
 * @return status_t SUCCESS if enqueue successful, FAILURE if queue is full or NULL
 *
 * @par Example:
 * @code
 * char* message = "Hello World";
 * if (queue_enqueue(&my_queue, message) == SUCCESS) {
 *     // Message added to queue
 * }
 * @endcode
 *
 * @note The queue stores void pointers, so any data type can be enqueued
 * @warning Enqueueing to a full queue will result in FAILURE
 * @warning The caller is responsible for data lifetime management
 */
status_t queue_enqueue(queue_t* queue, void* data);

/**
 * @brief Removes and returns the element from the front of the queue
 * @details Removes the oldest element from the queue following FIFO principles.
 *          The removed element is returned through the data parameter.
 *
 * @param[in,out] queue Pointer to the queue structure
 * @param[out] data Pointer to store the dequeued data pointer
 * @return status_t SUCCESS if dequeue successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * char* received_message;
 * if (queue_dequeue(&my_queue, (void**)&received_message) == SUCCESS) {
 *     // Process received_message
 * }
 * @endcode
 *
 * @note The dequeued element is removed from the queue
 * @warning Dequeueing from an empty queue will result in FAILURE
 * @warning Both queue and data parameters must be non-NULL
 */
status_t queue_dequeue(queue_t* queue, void** data);

/**
 * @brief Returns the front element without removing it from the queue
 * @details Allows inspection of the next element to be dequeued without
 *          actually removing it from the queue.
 *
 * @param[in] queue Pointer to the queue structure
 * @param[out] data Pointer to store the front data pointer
 * @return status_t SUCCESS if peek successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * char* next_message;
 * if (queue_peek(&my_queue, (void**)&next_message) == SUCCESS) {
 *     // Inspect next_message without removing it
 * }
 * @endcode
 *
 * @note The peeked element remains in the queue
 * @warning Peeking at an empty queue will result in FAILURE
 * @warning Both queue and data parameters must be non-NULL
 */
status_t queue_peek(const queue_t* queue, void** data);

/**
 * @brief Returns the current number of elements in the queue
 * @details Provides the current element count for monitoring queue usage.
 *
 * @param[in] queue Pointer to the queue structure
 * @return int Current number of elements (0 to QUEUE_MAX_SIZE), or 0 if queue is NULL
 *
 * @par Example:
 * @code
 * int current_size = queue_size(&my_queue);
 * printf("Queue contains %d elements\n", current_size);
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 0)
 * @note Return value is always between 0 and QUEUE_MAX_SIZE inclusive
 */
int queue_size(const queue_t* queue);

/** @} */ // End of RegularQueue group

#endif // QUEUE_H