#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct _Node {
    void* data;
    struct _Node* next;
};

typedef struct _Node node_t;

typedef enum {
    SUCCESS,
    FAILURE
} status_t;

/**
 * @brief Initializes the linked list.
 *
 * This function initializes the head of the linked list with NULL data and next pointer.
 *
 * @return status_t Returns SUCCESS if initialization is successful, FAILURE otherwise.
 */
status_t ll_init();

/**
 * @brief Inserts a new node at the head of the linked list.
 *
 * This function inserts a new node at the beginning of the linked list.
 *
 * @param new_node Pointer to the new node to be inserted.
 * @return status_t Returns SUCCESS if insertion is successful, FAILURE otherwise.
 */
status_t ll_insert_at_head(node_t* new_node);

/**
 * @brief Inserts a new node at the tail of the linked list.
 *
 * This function inserts a new node at the end of the linked list.
 *
 * @param new_node Pointer to the new node to be inserted.
 * @return status_t Returns SUCCESS if insertion is successful, FAILURE otherwise.
 */
status_t ll_insert_at_tail(node_t* new_node);

/**
 * @brief Deletes the node at the head of the linked list.
 *
 * This function removes the first node of the linked list.
 *
 * @return status_t Returns SUCCESS if deletion is successful, FAILURE otherwise.
 */
status_t ll_delete_at_head();

/**
 * @brief Deletes the node at the tail of the linked list.
 *
 * This function removes the last node of the linked list.
 *
 * @return status_t Returns SUCCESS if deletion is successful, FAILURE otherwise.
 */
status_t ll_delete_at_tail();

#endif