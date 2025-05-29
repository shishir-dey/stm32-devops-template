/**
 * @file linked_list.h
 * @brief Linked List implementation for embedded systems
 * @details This header provides a traditional linked list implementation with
 *          head and tail operations. This was the original data structure in the
 *          template and demonstrates basic dynamic list operations.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Key Features:
 *      - Traditional linked list structure with void* data
 *      - Head and tail insertion/deletion operations
 *      - Manual memory management (user provides nodes)
 *      - Suitable for dynamic collections of varying sizes
 *
 * @par Performance Characteristics:
 *      - Insert at head: O(1)
 *      - Insert at tail: O(n) - requires traversal
 *      - Delete at head: O(1)
 *      - Delete at tail: O(n) - requires traversal
 *
 * @par Memory Management:
 *      Unlike the queue implementations, the linked list requires users to
 *      provide their own node structures. This gives more control but requires
 *      careful memory management.
 *
 * @note Include this header to use the linked list functionality
 * @warning User is responsible for node allocation and data lifetime management
 *
 * @see https://github.com/shishir-dey/stm32-devops-template
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common_types.h"

/**
 * @defgroup LinkedList Linked List Implementation
 * @brief Traditional linked list for embedded systems
 *
 * This module provides a classic linked list implementation where users
 * manage their own node allocation. It's useful for collections that need
 * to grow and shrink dynamically, but requires careful memory management.
 *
 * @par Use Cases:
 *      - Dynamic task lists
 *      - Configuration parameter storage
 *      - Event callback chains
 *      - Memory pool management
 *      - Variable-length data collections
 *
 * @par Design Philosophy:
 *      The linked list gives users full control over memory allocation,
 *      making it suitable for scenarios where precise memory management
 *      is required or when integrating with existing memory pools.
 *
 * @{
 */

/**
 * @brief Node structure for the linked list
 * @details Each node contains a void pointer to data and a pointer to the next node.
 *          Users must allocate and manage these structures themselves.
 *
 * @par Structure Layout:
 *      - data: Void pointer to user's data
 *      - next: Pointer to the next node in the list
 *
 * @par Usage Pattern:
 *      1. User allocates node_t structure
 *      2. User sets data pointer to their data
 *      3. User calls linked list functions to manage the node
 *      4. User is responsible for node cleanup
 *
 * @note The _Node prefix prevents naming conflicts with user structures
 * @warning Users must ensure proper initialization of both data and next pointers
 */
struct _Node {
    void* data;           /**< Pointer to user-provided data */
    struct _Node* next;   /**< Pointer to the next node in the list */
};

/**
 * @brief Type definition for linked list nodes
 * @details Provides a convenient typedef for the node structure to simplify
 *          declarations and function signatures.
 *
 * @par Example Declaration:
 * @code
 * node_t my_node;           // Single node
 * node_t* dynamic_node;     // Pointer to node
 * @endcode
 */
typedef struct _Node node_t;

/**
 * @brief Initializes the linked list with an initial node
 * @details Sets up the linked list by designating the first node. This node
 *          becomes the head of the list and must be provided by the user.
 *
 * @param[in,out] initial_node Pointer to the first node to be added to the list
 * @return status_t SUCCESS if initialization successful, FAILURE if node pointer is NULL
 *
 * @par Example:
 * @code
 * node_t head_node;
 * char* head_data = "First item";
 *
 * head_node.data = head_data;
 * head_node.next = NULL;
 *
 * if (ll_init(&head_node) == SUCCESS) {
 *     // List is initialized with head_node
 * }
 * @endcode
 *
 * @par Initialization Steps:
 *      1. Sets the provided node as the global head
 *      2. Clears the node's data pointer
 *      3. Sets the node's next pointer to NULL
 *
 * @note This function modifies the provided node's data and next pointers
 * @note Only one linked list can be active at a time (global head pointer)
 * @warning Passing a NULL pointer will result in FAILURE return value
 * @warning The initial node's original data pointer will be overwritten
 */
status_t ll_init(node_t* initial_node);

/**
 * @brief Inserts a new node at the head of the linked list
 * @details Adds a new node at the beginning of the list, making it the new head.
 *          The previous head becomes the second element.
 *
 * @param[in,out] new_node Pointer to the new node to be inserted at the head
 * @return status_t SUCCESS if insertion successful, FAILURE if node pointer is NULL
 *
 * @par Example:
 * @code
 * node_t new_head;
 * char* new_data = "New first item";
 *
 * new_head.data = new_data;
 * new_head.next = NULL;  // Will be set by the function
 *
 * if (ll_insert_at_head(&new_head) == SUCCESS) {
 *     // new_head is now the first element
 * }
 * @endcode
 *
 * @par Algorithm:
 *      1. Set new node's next pointer to current head
 *      2. Update global head pointer to new node
 *
 * @note Time complexity: O(1)
 * @note The new node becomes the head regardless of list size
 * @note User must ensure the node remains valid for the list's lifetime
 * @warning Passing a NULL pointer will result in FAILURE return value
 * @warning Node must be properly allocated and initialized by user
 */
status_t ll_insert_at_head(node_t* new_node);

/**
 * @brief Inserts a new node at the tail of the linked list
 * @details Adds a new node at the end of the list. Requires traversing the
 *          entire list to find the current tail.
 *
 * @param[in,out] new_node Pointer to the new node to be inserted at the tail
 * @return status_t SUCCESS if insertion successful, FAILURE if node pointer is NULL
 *
 * @par Example:
 * @code
 * node_t new_tail;
 * char* tail_data = "Last item";
 *
 * new_tail.data = tail_data;
 * new_tail.next = NULL;
 *
 * if (ll_insert_at_tail(&new_tail) == SUCCESS) {
 *     // new_tail is now the last element
 * }
 * @endcode
 *
 * @par Algorithm:
 *      1. If list is empty, make new node the head
 *      2. Otherwise, traverse to find the current tail
 *      3. Set current tail's next pointer to new node
 *      4. Set new node's next pointer to NULL
 *
 * @note Time complexity: O(n) where n is the number of nodes
 * @note Special handling for empty list (becomes head)
 * @note User must ensure the node remains valid for the list's lifetime
 * @warning Passing a NULL pointer will result in FAILURE return value
 * @warning More expensive than head insertion due to traversal requirement
 */
status_t ll_insert_at_tail(node_t* new_node);

/**
 * @brief Deletes the node at the head of the linked list
 * @details Removes the first node from the list and updates the head pointer
 *          to the second node. The removed node is not deallocated.
 *
 * @return status_t SUCCESS if deletion successful, FAILURE if list is empty
 *
 * @par Example:
 * @code
 * // Assuming list has elements
 * if (ll_delete_at_head() == SUCCESS) {
 *     // First element has been removed
 *     // User may need to handle the removed node's memory
 * }
 * @endcode
 *
 * @par Algorithm:
 *      1. Check if list is empty
 *      2. Update head pointer to second node
 *      3. Original head node is no longer part of the list
 *
 * @note Time complexity: O(1)
 * @note The removed node is not deallocated by this function
 * @note If list becomes empty, head pointer is set to the second node
 * @warning User is responsible for handling the removed node's memory
 * @warning Calling on empty list will result in FAILURE return value
 */
status_t ll_delete_at_head();

/**
 * @brief Deletes the node at the tail of the linked list
 * @details Removes the last node from the list. Requires traversing the list
 *          to find the second-to-last node and update its next pointer.
 *
 * @return status_t SUCCESS if deletion successful, FAILURE if list is empty
 *
 * @par Example:
 * @code
 * // Assuming list has elements
 * if (ll_delete_at_tail() == SUCCESS) {
 *     // Last element has been removed
 *     // User may need to handle the removed node's memory
 * }
 * @endcode
 *
 * @par Algorithm:
 *      1. Check if list is empty
 *      2. If only one node, set head to NULL
 *      3. Otherwise, traverse to find second-to-last node
 *      4. Set second-to-last node's next pointer to NULL
 *
 * @note Time complexity: O(n) where n is the number of nodes
 * @note Special handling for single-node list
 * @note The removed node is not deallocated by this function
 * @warning User is responsible for handling the removed node's memory
 * @warning More expensive than head deletion due to traversal requirement
 * @warning Calling on empty list will result in FAILURE return value
 */
status_t ll_delete_at_tail();

/** @} */ // End of LinkedList group

#endif