#include "linked_list.h"

node_t node1, node2, node3, node4, node5, node6;
char* str1 = "Node 1";
char* str2 = "Node 2";
char* str3 = "Node 3";
char* str4 = "Node 4";

int main()
{
    ll_init(&node1);
    node1.data = str1;

    node2.data = str2;
    node3.data = str3;
    ll_insert_at_head(&node2);
    ll_insert_at_head(&node3);

    node4.data = str4;
    ll_insert_at_tail(&node4);

    ll_delete_at_head();
    ll_delete_at_tail();

    return 0;
}
