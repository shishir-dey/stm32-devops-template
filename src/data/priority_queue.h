/**
 * @file priority_queue.h
 * @brief Priority Queue (Binary Max-Heap) implementation for embedded systems
 * @details This header provides a priority queue implementation using a binary max-heap
 *          with static memory allocation. Higher priority elements are served first,
 *          making it ideal for task scheduling and resource management in embedded systems.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Key Features:
 *      - Static memory allocation (no malloc/free)
 *      - Binary max-heap implementation for efficient priority ordering
 *      - Higher numbers indicate higher priority
 *      - Configurable maximum size via PRIORITY_QUEUE_MAX_SIZE
 *      - O(log n) insertion and deletion operations
 *
 * @par Performance Characteristics:
 *      - Enqueue: O(log n) - heap insertion with bubble-up
 *      - Dequeue: O(log n) - heap removal with bubble-down
 *      - Peek: O(1) - access to highest priority element
 *      - Size check: O(1)
 *
 * @par Binary Heap Properties:
 *      - Complete binary tree structure stored in array
 *      - Parent node always has higher priority than children
 *      - Automatic rebalancing maintains heap property
 *      - Efficient array-based representation
 *
 * @note Include this header to use the priority queue functionality
 * @warning Ensure PRIORITY_QUEUE_MAX_SIZE is appropriate for your memory constraints
 * @warning Higher numbers indicate higher priority in this implementation
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

#include "common_types.h"

/**
 * @defgroup PriorityQueue Priority Queue (Binary Max-Heap) Implementation
 * @brief Static memory priority queue for embedded systems
 *
 * This module provides a priority queue implementation using a binary max-heap
 * data structure. Elements are automatically ordered by priority, with higher
 * priority elements always served first. Designed for embedded systems where
 * deterministic priority-based processing is required.
 *
 * @par Use Cases:
 *      - Real-time task scheduling
 *      - Interrupt handling prioritization
 *      - Event processing by importance
 *      - Resource allocation management
 *      - Error handling (critical errors first)
 *
 * @par Heap Structure:
 *      The binary heap is stored as an array where for element at index i:
 *      - Parent is at index (i-1)/2
 *      - Left child is at index 2*i+1
 *      - Right child is at index 2*i+2
 *
 * @{
 */

/**
 * @brief Maximum number of elements the priority queue can hold
 * @details This compile-time constant defines the maximum capacity of the priority
 *          queue. It can be modified based on system memory constraints and requirements.
 *
 * @note Increasing this value will increase memory usage proportionally
 * @warning Must be greater than 0 and should fit within available RAM
 */
#define PRIORITY_QUEUE_MAX_SIZE 100

/**
 * @brief Priority queue element structure
 * @details Each element in the priority queue contains both data and its associated
 *          priority value. This allows the heap to maintain proper ordering.
 *
 * @par Priority Semantics:
 *      Higher numerical values indicate higher priority. For example:
 *      - Priority 10 will be processed before priority 5
 *      - Priority 1 will be processed last among priorities 1, 5, 10
 *
 * @note Both data and priority are stored together for efficiency
 * @warning Priority values should be chosen carefully to avoid overflow
 */
typedef struct {
    void* data;      /**< Pointer to the actual data element */
    int priority;    /**< Priority value (higher numbers = higher priority) */
} priority_queue_element_t;

/**
 * @brief Priority queue data structure
 * @details This structure maintains the priority queue state including the heap array
 *          and current size. The heap property is maintained through specialized
 *          insertion and deletion algorithms.
 *
 * @par Structure Layout:
 *      - elements[]: Array implementing the binary heap
 *      - size: Current number of elements in the heap
 *
 * @par Heap Property:
 *      For any element at index i:
 *      elements[i].priority >= elements[2*i+1].priority (left child)
 *      elements[i].priority >= elements[2*i+2].priority (right child)
 *
 * @note All members should be considered private and accessed only through API functions
 * @warning Direct modification of structure members will break heap property
 */
typedef struct {
    priority_queue_element_t elements[PRIORITY_QUEUE_MAX_SIZE];  /**< Heap array of elements */
    int size;                                                     /**< Current number of elements */
} priority_queue_t;

/**
 * @brief Initializes the priority queue to an empty state
 * @details Sets up the priority queue structure with initial values. Must be called
 *          before any other priority queue operations.
 *
 * @param[out] queue Pointer to the priority queue structure to initialize
 * @return status_t SUCCESS if initialization successful, FAILURE if queue pointer is NULL
 *
 * @par Example:
 * @code
 * priority_queue_t task_scheduler;
 * if (priority_queue_init(&task_scheduler) == SUCCESS) {
 *     // Priority queue is ready for task scheduling
 * }
 * @endcode
 *
 * @note This function must be called before any other priority queue operations
 * @warning Passing a NULL pointer will result in FAILURE return value
 */
status_t priority_queue_init(priority_queue_t* queue);

/**
 * @brief Checks if the priority queue is empty
 * @details Determines whether the priority queue contains any elements.
 *
 * @param[in] queue Pointer to the priority queue to check
 * @return int 1 if queue is empty or NULL, 0 if queue contains elements
 *
 * @par Example:
 * @code
 * if (priority_queue_is_empty(&task_scheduler)) {
 *     // No tasks scheduled
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 */
int priority_queue_is_empty(const priority_queue_t* queue);

/**
 * @brief Checks if the priority queue is full
 * @details Determines whether the priority queue has reached its maximum capacity.
 *
 * @param[in] queue Pointer to the priority queue to check
 * @return int 1 if queue is full or NULL, 0 if queue has available space
 *
 * @par Example:
 * @code
 * if (!priority_queue_is_full(&task_scheduler)) {
 *     // Can schedule more tasks
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 1)
 */
int priority_queue_is_full(const priority_queue_t* queue);

/**
 * @brief Adds an element with priority to the priority queue
 * @details Inserts a new element into the priority queue maintaining the heap property.
 *          The element is placed according to its priority using the heapify-up algorithm.
 *
 * @param[in,out] queue Pointer to the priority queue structure
 * @param[in] data Pointer to the data to be enqueued
 * @param[in] priority Priority value for the element (higher = more important)
 * @return status_t SUCCESS if enqueue successful, FAILURE if queue is full or NULL
 *
 * @par Example:
 * @code
 * char* critical_task = "Handle critical error";
 * char* normal_task = "Update display";
 *
 * priority_queue_enqueue(&task_scheduler, critical_task, 100);  // High priority
 * priority_queue_enqueue(&task_scheduler, normal_task, 10);     // Lower priority
 * // critical_task will be processed first
 * @endcode
 *
 * @par Algorithm (Heapify-Up):
 *      1. Insert element at the end of the heap
 *      2. Compare with parent and swap if priority is higher
 *      3. Repeat until heap property is satisfied or root is reached
 *
 * @note Time complexity: O(log n) where n is the number of elements
 * @note The queue stores void pointers, so any data type can be enqueued
 * @warning Enqueueing to a full queue will result in FAILURE
 * @warning The caller is responsible for data lifetime management
 * @warning Higher priority values are processed first
 */
status_t priority_queue_enqueue(priority_queue_t* queue, void* data, int priority);

/**
 * @brief Removes and returns the highest priority element
 * @details Removes the element with the highest priority from the queue and
 *          restructures the heap to maintain the heap property using heapify-down.
 *
 * @param[in,out] queue Pointer to the priority queue structure
 * @param[out] data Pointer to store the dequeued data pointer
 * @param[out] priority Pointer to store the priority of the dequeued element
 * @return status_t SUCCESS if dequeue successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * char* task;
 * int task_priority;
 *
 * if (priority_queue_dequeue(&task_scheduler, (void**)&task, &task_priority) == SUCCESS) {
 *     printf("Executing task: %s (priority: %d)\n", task, task_priority);
 * }
 * @endcode
 *
 * @par Algorithm (Heapify-Down):
 *      1. Remove root element (highest priority)
 *      2. Move last element to root position
 *      3. Compare with children and swap with highest priority child
 *      4. Repeat until heap property is satisfied or leaf is reached
 *
 * @note Time complexity: O(log n) where n is the number of elements
 * @note The dequeued element is removed from the queue
 * @note Always returns the element with the highest priority value
 * @warning Dequeueing from an empty queue will result in FAILURE
 * @warning All parameters (queue, data, priority) must be non-NULL
 */
status_t priority_queue_dequeue(priority_queue_t* queue, void** data, int* priority);

/**
 * @brief Returns the highest priority element without removing it
 * @details Allows inspection of the element with the highest priority without
 *          actually removing it from the priority queue.
 *
 * @param[in] queue Pointer to the priority queue structure
 * @param[out] data Pointer to store the highest priority data pointer
 * @param[out] priority Pointer to store the priority of the highest priority element
 * @return status_t SUCCESS if peek successful, FAILURE if queue is empty or NULL
 *
 * @par Example:
 * @code
 * char* next_task;
 * int next_priority;
 *
 * if (priority_queue_peek(&task_scheduler, (void**)&next_task, &next_priority) == SUCCESS) {
 *     printf("Next task: %s (priority: %d)\n", next_task, next_priority);
 *     // Task remains in queue for later processing
 * }
 * @endcode
 *
 * @note Time complexity: O(1) - direct access to root element
 * @note The peeked element remains in the queue
 * @note Always returns the element with the highest priority value
 * @warning Peeking at an empty queue will result in FAILURE
 * @warning All parameters (queue, data, priority) must be non-NULL
 */
status_t priority_queue_peek(const priority_queue_t* queue, void** data, int* priority);

/**
 * @brief Returns the current number of elements in the priority queue
 * @details Provides the current element count for monitoring queue usage.
 *
 * @param[in] queue Pointer to the priority queue structure
 * @return int Current number of elements (0 to PRIORITY_QUEUE_MAX_SIZE), or 0 if queue is NULL
 *
 * @par Example:
 * @code
 * int pending_tasks = priority_queue_size(&task_scheduler);
 * printf("Tasks pending: %d\n", pending_tasks);
 *
 * // Check if queue is getting full
 * if (pending_tasks > PRIORITY_QUEUE_MAX_SIZE * 0.8) {
 *     printf("Warning: Task queue is 80%% full\n");
 * }
 * @endcode
 *
 * @note Safe to call with NULL pointer (returns 0)
 * @note Return value is always between 0 and PRIORITY_QUEUE_MAX_SIZE inclusive
 * @note Time complexity: O(1)
 */
int priority_queue_size(const priority_queue_t* queue);

/** @} */ // End of PriorityQueue group

#endif // PRIORITY_QUEUE_H