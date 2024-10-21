#include "linked_list.h"
#include <stddef.h>

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
