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
 * @brief Initializes the linked list with an initial node.
 *
 * @param initial_node Pointer to the initial node to be added to the list.
 * @return status_t SUCCESS if initialization is successful, FAILURE otherwise.
 */
status_t ll_init(node_t* initial_node);

/**
 * @brief Inserts a new node at the head of the linked list.
 *
 * @param new_node Pointer to the new node to be inserted at the head.
 * @return status_t SUCCESS if insertion is successful, FAILURE otherwise.
 */
status_t ll_insert_at_head(node_t* new_node);

/**
 * @brief Inserts a new node at the tail of the linked list.
 *
 * @param new_node Pointer to the new node to be inserted at the tail.
 * @return status_t SUCCESS if insertion is successful, FAILURE otherwise.
 */
status_t ll_insert_at_tail(node_t* new_node);

/**
 * @brief Deletes the node at the head of the linked list.
 *
 * @return status_t SUCCESS if deletion is successful, FAILURE if the list is empty.
 */
status_t ll_delete_at_head();

/**
 * @brief Deletes the node at the tail of the linked list.
 *
 * @return status_t SUCCESS if deletion is successful, FAILURE if the list is empty.
 */
status_t ll_delete_at_tail();

#endif