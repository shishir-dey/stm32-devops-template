#include <stdlib.h>
#include "linked_list.h"

Node *InitList()
{
    Node *list = malloc(sizeof(Node));
    list->data = NULL;
    list->next = NULL;
    return list;
}

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