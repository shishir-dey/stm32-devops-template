#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct _Node
{
    void *data;
    struct _Node *next;
};

typedef struct _Node Node;

Node *InitList();
void AddNode(Node *list, void *data);
void DeleteList(Node *list);

#endif