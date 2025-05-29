/**
 * @file priority_queue.c
 * @brief Implementation of priority queue (binary max-heap) operations
 * @details This file contains the implementation of all priority queue operations
 *          using binary heap algorithms for efficient priority-based ordering.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Implementation Details:
 *      - Uses array-based binary heap representation
 *      - Heapify-up algorithm for insertion
 *      - Heapify-down algorithm for deletion
 *      - Parent-child relationships: parent(i) = (i-1)/2, children(i) = 2*i+1, 2*i+2
 *
 * @note All functions include proper error checking and heap property maintenance
 * @see priority_queue.h for API documentation
 */

#include <stddef.h>

#include "priority_queue.h"

/**
 * @brief Swaps two priority queue elements
 * @details Helper function that exchanges the contents of two priority queue
 *          elements including both data and priority values.
 *
 * @param[in,out] a Pointer to the first element
 * @param[in,out] b Pointer to the second element
 *
 * @note This is an internal helper function used by heap operations
 * @note Time complexity: O(1)
 */
static void swap_elements(priority_queue_element_t* a, priority_queue_element_t* b)
{
    priority_queue_element_t temp = *a;

    *a = *b;
    *b = temp;
}

/**
 * @brief Restores heap property by moving element upward
 * @details Recursive function that compares an element with its parent and
 *          swaps if the element has higher priority. Continues until heap
 *          property is satisfied or root is reached.
 *
 * @param[in,out] queue Pointer to the priority queue
 * @param[in] index Index of the element to heapify upward
 *
 * @par Algorithm:
 *      1. Calculate parent index: (index - 1) / 2
 *      2. If current element has higher priority than parent, swap
 *      3. Recursively continue with parent index
 *      4. Stop when root is reached or heap property is satisfied
 *
 * @note This is an internal helper function used during insertion
 * @note Time complexity: O(log n) where n is the number of elements
 */
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

/**
 * @brief Restores heap property by moving element downward
 * @details Recursive function that compares an element with its children and
 *          swaps with the highest priority child if necessary. Continues until
 *          heap property is satisfied or leaf is reached.
 *
 * @param[in,out] queue Pointer to the priority queue
 * @param[in] index Index of the element to heapify downward
 *
 * @par Algorithm:
 *      1. Calculate left child: 2 * index + 1
 *      2. Calculate right child: 2 * index + 2
 *      3. Find the largest priority among current, left, and right
 *      4. If largest is not current, swap and continue recursively
 *      5. Stop when heap property is satisfied or leaf is reached
 *
 * @note This is an internal helper function used during deletion
 * @note Time complexity: O(log n) where n is the number of elements
 */
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