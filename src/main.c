/**
 * @file main.c
 * @brief Main demonstration file for STM32 DevOps Template queue implementations
 * @details This file provides comprehensive examples of using three different queue
 *          implementations without dynamic memory allocation, suitable for embedded systems:
 *          - Regular Queue (FIFO)
 *          - Circular Queue (Ring Buffer)
 *          - Priority Queue (Binary Heap)
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @note All queue implementations use statically allocated arrays to avoid
 *       heap fragmentation issues common in embedded systems.
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#include "data/circular_queue.h"
#include "data/linked_list.h"
#include "data/priority_queue.h"
#include "data/queue.h"

/**
 * @defgroup DataStructures Data Structure Demonstrations
 * @brief Collection of static data structure demonstrations for embedded systems
 *
 * This group contains demonstrations of various data structures that can be used
 * in embedded systems without requiring dynamic memory allocation. All structures
 * are implemented using static arrays with compile-time size limits.
 * @{
 */

/** @brief Global regular queue instance for demonstration */
queue_t regular_queue;

/** @brief Global circular queue instance for demonstration */
circular_queue_t circular_queue;

/** @brief Global priority queue instance for demonstration */
priority_queue_t priority_queue;

/** @brief Test task 1 - Low priority task example */
char* task1 = "Task 1";

/** @brief Test task 2 - High priority task example */
char* task2 = "Task 2";

/** @brief Test task 3 - Medium priority task example */
char* task3 = "Task 3";

/** @brief Test task 4 - Critical priority task example */
char* task4 = "Task 4";

/**
 * @brief Demonstrates regular queue (FIFO) operations
 * @details Shows the basic First-In-First-Out behavior of a regular queue.
 *          This is useful for task scheduling, buffer management, and any
 *          scenario where processing order matters.
 *
 * @par Example Usage in Embedded Systems:
 *      - UART receive buffer
 *      - Task scheduling queue
 *      - Event processing queue
 *      - Command buffer for serial protocols
 *
 * @par Algorithm:
 *      1. Initialize the queue
 *      2. Enqueue several tasks
 *      3. Dequeue all tasks in FIFO order
 *
 * @note The queue uses circular indexing internally for efficient memory usage
 * @warning Ensure queue is not full before enqueuing to avoid data loss
 */
void demonstrate_regular_queue(void){
    char* dequeued_data;

    // Initialize and test regular queue
    queue_init(&regular_queue);

    // Enqueue some tasks
    queue_enqueue(&regular_queue, task1);
    queue_enqueue(&regular_queue, task2);
    queue_enqueue(&regular_queue, task3);

    // Dequeue tasks (FIFO order)
    while (!queue_is_empty(&regular_queue)) {
        queue_dequeue(&regular_queue, (void**)&dequeued_data);
        // Process dequeued data (in embedded system, you might trigger GPIO, etc.)
    }
}

/**
 * @brief Demonstrates circular queue (ring buffer) operations
 * @details Shows the circular nature of the ring buffer, where the queue
 *          wraps around when it reaches the end of the array. This is
 *          particularly useful for streaming data and fixed-size buffers.
 *
 * @par Example Usage in Embedded Systems:
 *      - Audio streaming buffers
 *      - Sensor data sampling
 *      - Communication protocol buffers
 *      - Real-time data logging
 *
 * @par Algorithm:
 *      1. Initialize the circular queue
 *      2. Add some elements
 *      3. Remove some elements (creating space)
 *      4. Add more elements (demonstrating wrap-around)
 *      5. Process remaining elements
 *
 * @note Circular queues are memory efficient as they reuse buffer space
 * @warning Distinguish between full and empty states using the is_full flag
 */
void demonstrate_circular_queue(void){
    char* dequeued_data;

    // Initialize circular queue
    circular_queue_init(&circular_queue);

    // Enqueue some tasks
    circular_queue_enqueue(&circular_queue, task1);
    circular_queue_enqueue(&circular_queue, task2);

    // Dequeue one task
    circular_queue_dequeue(&circular_queue, (void**)&dequeued_data);

    // Add more tasks (demonstrating circular nature)
    circular_queue_enqueue(&circular_queue, task3);
    circular_queue_enqueue(&circular_queue, task4);

    // Process remaining tasks
    while (!circular_queue_is_empty(&circular_queue)) {
        circular_queue_dequeue(&circular_queue, (void**)&dequeued_data);
        // Process dequeued data
    }
}

/**
 * @brief Demonstrates priority queue (max-heap) operations
 * @details Shows how tasks are processed based on priority rather than
 *          insertion order. Higher priority tasks are always processed first.
 *          Implemented as a binary max-heap for O(log n) operations.
 *
 * @par Example Usage in Embedded Systems:
 *      - Interrupt handling prioritization
 *      - Real-time task scheduling
 *      - Error handling (critical errors first)
 *      - Resource allocation management
 *
 * @par Algorithm:
 *      1. Initialize the priority queue
 *      2. Enqueue tasks with different priorities
 *      3. Dequeue tasks in priority order (highest first)
 *
 * @note Uses binary heap data structure for efficient priority management
 * @warning Higher numbers indicate higher priority in this implementation
 */
void demonstrate_priority_queue(void){
    char* dequeued_data;
    int dequeued_priority;

    // Initialize priority queue
    priority_queue_init(&priority_queue);

    // Enqueue tasks with different priorities
    priority_queue_enqueue(&priority_queue, task1, 1);  // Low priority
    priority_queue_enqueue(&priority_queue, task2, 10); // High priority
    priority_queue_enqueue(&priority_queue, task3, 5);  // Medium priority
    priority_queue_enqueue(&priority_queue, task4, 15); // Highest priority

    // Process tasks in priority order (highest first)
    while (!priority_queue_is_empty(&priority_queue)) {
        priority_queue_dequeue(&priority_queue, (void**)&dequeued_data, &dequeued_priority);
        // Process high-priority task first
    }
}

/**
 * @brief Demonstrates linked list operations (legacy compatibility)
 * @details Shows basic linked list operations including initialization,
 *          insertion at head/tail, and deletion operations. This demonstrates
 *          the original functionality that was extended with queue implementations.
 *
 * @par Example Usage in Embedded Systems:
 *      - Dynamic task lists
 *      - Configuration parameter storage
 *      - Event callback chains
 *      - Memory pool management
 *
 * @par Algorithm:
 *      1. Initialize with a head node
 *      2. Insert nodes at head and tail
 *      3. Delete nodes from head and tail
 *
 * @note This function maintains compatibility with the original template
 * @warning Manual memory management required for nodes
 */
void demonstrate_linked_list(void){
    node_t node1, node2, node3, node4;
    char* str1 = "Node 1";
    char* str2 = "Node 2";
    char* str3 = "Node 3";
    char* str4 = "Node 4";

    ll_init(&node1);
    node1.data = str1;

    node2.data = str2;
    node3.data = str3;
    ll_insert_at_head(&node2);
    ll_insert_at_head(&node3);

    node4.data = str4;
    ll_insert_at_tail(&node4);

    ll_delete_at_head();
    ll_delete_at_tail();
}

/** @} */ // End of DataStructures group

/**
 * @brief Main entry point for the STM32 DevOps Template demonstration
 * @details Executes demonstrations of all implemented data structures to
 *          showcase their usage in embedded systems. Each demonstration
 *          is independent and can be used as a reference implementation.
 *
 * @return int Always returns 0 for successful execution
 *
 * @par Execution Flow:
 *      1. Linked list demonstration (original functionality)
 *      2. Regular queue demonstration (FIFO behavior)
 *      3. Circular queue demonstration (ring buffer)
 *      4. Priority queue demonstration (priority-based processing)
 *
 * @note All data structures use static allocation suitable for embedded systems
 * @note This code is designed to run on STM32 microcontrollers but can be
 *       compiled for host testing as well
 *
 * @see demonstrate_linked_list()
 * @see demonstrate_regular_queue()
 * @see demonstrate_circular_queue()
 * @see demonstrate_priority_queue()
 */
int main()
{
    // Demonstrate all data structures
    demonstrate_linked_list();
    demonstrate_regular_queue();
    demonstrate_circular_queue();
    demonstrate_priority_queue();

    return 0;
}