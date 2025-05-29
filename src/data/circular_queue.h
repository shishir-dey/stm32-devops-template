/**
 * @file circular_queue.h
 * @brief Circular Queue (Ring Buffer) implementation for embedded systems
 * @details This header provides a circular queue implementation using static memory
 *          allocation. The circular queue is particularly useful for streaming data
 *          and fixed-size buffers where memory efficiency is crucial.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Key Features:
 *      - Static memory allocation (no malloc/free)
 *      - Circular buffer behavior with wrap-around
 *      - Memory efficient reuse of buffer space
 *      - Configurable maximum size via CIRCULAR_QUEUE_MAX_SIZE
 *      - Distinction between full and empty states
 *
 * @par Performance Characteristics:
 *      - Enqueue: O(1)
 *      - Dequeue: O(1)
 *      - Peek: O(1)
 *      - Size check: O(1)
 *
 * @par Difference from Regular Queue:
 *      Unlike regular queues, circular queues reuse the buffer space by wrapping
 *      around to the beginning when reaching the end. This makes them ideal for
 *      continuous data streaming applications.
 *
 * @note Include this header to use the circular queue functionality
 * @warning Ensure CIRCULAR_QUEUE_MAX_SIZE is appropriate for your memory constraints
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>

#include "common_types.h"

/**
 * @defgroup CircularQueue Circular Queue (Ring Buffer) Implementation
 * @brief Static memory circular queue for embedded systems
 *
 * This module provides a circular queue implementation that efficiently reuses
 * buffer space by wrapping around when the end is reached. It's designed for
 * embedded systems where continuous data flow and memory efficiency are required.
 *
 * @par Use Cases:
 *      - Audio streaming buffers
 *      - Sensor data sampling
 *      - Communication protocol buffers
 *      - Real-time data logging
 *      - Producer-consumer scenarios
 *
 * @par Ring Buffer Concept:
 *      The circular queue maintains two pointers (front and rear) that wrap around
 *      the buffer. When the rear pointer reaches the end, it wraps to the beginning,
 *      creating a circular data flow pattern.
 *
 * @{
 */

/**
 * @brief Maximum number of elements the circular queue can hold
 * @details This compile-time constant defines the maximum capacity of the circular
 *          queue. It can be modified based on system memory constraints and requirements.
 *
 * @note Increasing this value will increase memory usage proportionally
 * @warning Must be greater than 0 and should fit within available RAM
 */
#define CIRCULAR_QUEUE_MAX_SIZE 100

/**
 * @brief Circular queue data structure
 * @details This structure maintains the circular queue state including the data array,
 *          front and rear pointers, and a full indicator. The circular nature is
 *          achieved through modulo arithmetic on the pointers.
 *
 * @par Structure Layout:
 *      - data[]: Array to store queue elements
 *      - front: Index of the first element to be dequeued
 *      - rear: Index where the next element will be enqueued
 *      - is_full: Flag to distinguish between full and empty states
 *
 * @par Full vs Empty Detection:
 *      Since front == rear can mean both empty and full, the is_full flag
 *      is used to distinguish between these states.
 *
 * @note All members should be considered private and accessed only through API functions
 * @warning Direct modification of structure members may lead to undefined behavior
 */
typedef struct {
    void* data[CIRCULAR_QUEUE_MAX_SIZE];  /**< Array of void pointers to store any data type */
    int front;                            /**< Index of the front element (next to dequeue) */
    int rear;                             /**< Index of the rear position (next enqueue location) */
    int is_full;                          /**< Flag indicating if the queue is full (1) or not (0) */
} circular_queue_t;

/**
 * @brief Initializes the circular queue to an empty state
 * @details Sets up the circular queue structure with initial values. Must be called
 *          before any other circular queue operations.
 *
 * @param[out] queue Pointer to the circular queue structure to initialize
 * @return status_t SUCCESS if initialization successful, FAILURE if queue pointer is NULL
 *
 * @par Example:
 * @code
 * circular_queue_t sensor_buffer;
 * if (circular_queue_init(&sensor_buffer) == SUCCESS) {
 *     // Circular queue is ready to use
 * }
 * @endcode
 *
 * @note This function must be called before any other circular queue operations
 * @warning Passing a NULL pointer will result in FAILURE return value
 */
status_t circular_queue_init(circular_queue_t* queue);

/**
 * @brief Checks if the circular queue is empty
 * @details Determines whether the circular queue contains any elements by checking
 *          both the is_full flag and pointer positions.
 *
 * @param[in] queue Pointer to the circular queue to check
 * @return int 1 if queue is empty or NULL, 0 if queue contains elements
 *
 * @par Example:
 * @code
 * if (circular_queue_is_empty(&sensor_buffer)) {
 *     // No sensor data available
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 * @note Empty condition: !is_full && (front == rear)
 */
int circular_queue_is_empty(const circular_queue_t* queue);

/**
 * @brief Checks if the circular queue is full
 * @details Determines whether the circular queue has reached its maximum capacity
 *          and cannot accept more elements without overwriting.
 *
 * @param[in] queue Pointer to the circular queue to check
 * @return int 1 if queue is full or NULL, 0 if queue has available space
 *
 * @par Example:
 * @code
 * if (!circular_queue_is_full(&sensor_buffer)) {
 *     // Safe to add more sensor readings
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 * @note Full condition: is_full flag is set to 1
 */
int circular_queue_is_full(const circular_queue_t* queue);

/**
 * @brief Adds an element to the circular queue
 * @details Inserts a new element at the rear of the circular queue. If the rear
 *          pointer reaches the end of the array, it wraps around to the beginning.
 *
 * @param[in,out] queue Pointer to the circular queue structure
 * @param[in] data Pointer to the data to be enqueued
 * @return status_t SUCCESS if enqueue successful, FAILURE if queue is full or NULL
 *
 * @par Example:
 * @code
 * int sensor_reading = 1024;
 * if (circular_queue_enqueue(&sensor_buffer, &sensor_reading) == SUCCESS) {
 *     // Sensor reading added to buffer
 * }
 * @endcode
 *
 * @par Wrap-around Behavior:
 *      When the rear pointer reaches CIRCULAR_QUEUE_MAX_SIZE-1, the next enqueue
 *      operation will place the element at index 0, creating the circular behavior.
 *
 * @note The queue stores void pointers, so any data type can be enqueued
 * @warning Enqueueing to a full queue will result in FAILURE (no overwrite)
 * @warning The caller is responsible for data lifetime management
 */
status_t circular_queue_enqueue(circular_queue_t* queue, void* data);

/**
 * @brief Removes and returns the element from the front of the circular queue
 * @details Removes the oldest element from the circular queue following FIFO principles.
 *          The front pointer wraps around when it reaches the end of the array.
 *
 * @param[in,out] queue Pointer to the circular queue structure
 * @param[out] data Pointer to store the dequeued data pointer
 * @return status_t SUCCESS if dequeue successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * int* sensor_reading;
 * if (circular_queue_dequeue(&sensor_buffer, (void**)&sensor_reading) == SUCCESS) {
 *     printf("Sensor reading: %d\n", *sensor_reading);
 * }
 * @endcode
 *
 * @par Wrap-around Behavior:
 *      When the front pointer reaches CIRCULAR_QUEUE_MAX_SIZE-1, the next dequeue
 *      operation will fetch the element from index 0.
 *
 * @note The dequeued element is removed from the queue
 * @note Automatically clears the is_full flag when an element is removed
 * @warning Dequeueing from an empty queue will result in FAILURE
 * @warning Both queue and data parameters must be non-NULL
 */
status_t circular_queue_dequeue(circular_queue_t* queue, void** data);

/**
 * @brief Returns the front element without removing it from the queue
 * @details Allows inspection of the next element to be dequeued without
 *          actually removing it from the circular queue.
 *
 * @param[in] queue Pointer to the circular queue structure
 * @param[out] data Pointer to store the front data pointer
 * @return status_t SUCCESS if peek successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * int* next_reading;
 * if (circular_queue_peek(&sensor_buffer, (void**)&next_reading) == SUCCESS) {
 *     // Inspect next_reading without removing it
 * }
 * @endcode
 *
 * @note The peeked element remains in the queue
 * @warning Peeking at an empty queue will result in FAILURE
 * @warning Both queue and data parameters must be non-NULL
 */
status_t circular_queue_peek(const circular_queue_t* queue, void** data);

/**
 * @brief Returns the current number of elements in the circular queue
 * @details Calculates the current element count by considering the front and rear
 *          pointers along with the full state. Handles wrap-around cases correctly.
 *
 * @param[in] queue Pointer to the circular queue structure
 * @return int Current number of elements (0 to CIRCULAR_QUEUE_MAX_SIZE), or 0 if queue is NULL
 *
 * @par Example:
 * @code
 * int buffer_usage = circular_queue_size(&sensor_buffer);
 * printf("Buffer is %d%% full\n", (buffer_usage * 100) / CIRCULAR_QUEUE_MAX_SIZE);
 * @endcode
 *
 * @par Size Calculation:
 *      - If full: returns CIRCULAR_QUEUE_MAX_SIZE
 *      - If empty: returns 0
 *      - If rear >= front: returns (rear - front)
 *      - If rear < front (wrapped): returns (CIRCULAR_QUEUE_MAX_SIZE - front + rear)
 *
 * @note Safe to call with NULL pointer (returns 0)
 * @note Return value is always between 0 and CIRCULAR_QUEUE_MAX_SIZE inclusive
 */
int circular_queue_size(const circular_queue_t* queue);

/** @} */ // End of CircularQueue group

#endif // CIRCULAR_QUEUE_H