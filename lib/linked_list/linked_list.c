#include <stdlib.h>
#include "linked_list.h"

/// @brief Initialize a new linked list
/// @return Pointer to the new list
Node *InitList()
{
    Node *list = malloc(sizeof(Node));
    list->data = NULL;
    list->next = NULL;
    return list;
}

/// @brief Add a new node to the list
/// @param list Pointer to the list
/// @param data Pointer to the data to add
void AddNode(Node *list, void *data)
{
    if (list->data == NULL)
    {
        list->data = data;
        list->next = NULL;
    }
    else
    {
        Node *node = list;
        while (node->next != NULL)
        {
            node = node->next;
        }
        node->next = malloc(sizeof(Node));
        node->next->data = data;
        node->next->next = NULL;
    }
}

/// @brief Delete the list
/// @param list Pointer to the list
void DeleteList(Node *list)
{
    Node *current = list;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    *list = (Node){NULL, NULL};
}