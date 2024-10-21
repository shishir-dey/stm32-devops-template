#include "linked_list.h"
#include <stdlib.h>

static node_t* head;

status_t ll_init()
{
    status_t ret = FAILURE;
    head->data = NULL;
    head->next = NULL;
    ret = SUCCESS;
    return ret;
}

status_t ll_insert_at_head(node_t* new_node)
{
    status_t ret = FAILURE;
    new_node->next = head;
    head = new_node;
    ret = SUCCESS;
    return ret;
}

status_t ll_insert_at_tail(node_t* new_node)
{
    status_t ret = FAILURE;
    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    ret = SUCCESS;
    return ret;
}

status_t ll_delete_at_head()
{
    status_t ret = FAILURE;
    head = head->next;
    ret = SUCCESS;
    return ret;
}

status_t ll_delete_at_tail()
{
    status_t ret = FAILURE;
    node_t* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    current->next = NULL;
    ret = SUCCESS;
    return ret;
}
