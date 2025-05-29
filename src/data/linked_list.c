/**
 * @file linked_list.c
 * @brief Implementation of linked list operations
 * @details This file contains the implementation of all linked list operations
 *          using a global head pointer and manual node management.
 *
 * @author Shishir Dey
 * @date 2025
 * @version 1.0.0
 *
 * @par Implementation Details:
 *      - Uses global static head pointer for list management
 *      - User-provided nodes with manual memory management
 *      - Traditional linked list traversal algorithms
 *      - Head operations are O(1), tail operations are O(n)
 *
 * @note All functions include proper error checking and NULL pointer validation
 * @note Only one linked list instance can be active at a time
 * @see linked_list.h for API documentation
 */

#include <stddef.h>

#include "linked_list.h"

/**
 * @brief Global head pointer for the linked list
 * @details Static variable that maintains the reference to the first node
 *          in the linked list. Only one list can be active at a time.
 *
 * @note This global state limits the implementation to a single list instance
 * @warning Direct access to this variable should be avoided
 */
static node_t* head = NULL;

status_t ll_init(node_t* initial_node)
{
    if (initial_node == NULL) {
        return FAILURE;
    }

    head = initial_node;
    head->data = NULL;
    head->next = NULL;

    return SUCCESS;
}

status_t ll_insert_at_head(node_t* new_node)
{
    if (new_node == NULL) {
        return FAILURE;
    }

    new_node->next = head;
    head = new_node;

    return SUCCESS;
}

status_t ll_insert_at_tail(node_t* new_node)
{
    if (new_node == NULL) {
        return FAILURE;
    }

    if (head == NULL) {
        head = new_node;
        head->next = NULL;

        return SUCCESS;
    }

    node_t* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    new_node->next = NULL;

    return SUCCESS;
}

status_t ll_delete_at_head()
{
    if (head == NULL) {
        return FAILURE;
    }

    head = head->next;

    return SUCCESS;
}

status_t ll_delete_at_tail()
{
    if (head == NULL) {
        return FAILURE;
    }

    if (head->next == NULL) {
        head = NULL;

        return SUCCESS;
    }

    node_t* current = head;

    while (current->next->next != NULL) {
        current = current->next;
    }

    current->next = NULL;

    return SUCCESS;
}