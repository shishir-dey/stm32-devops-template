#include "Unity.h"
#include "linked_list.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void testLinkedListAddNode(void)
{
    Node *list = InitList();
    TEST_ASSERT_NULL(list->data);
    TEST_ASSERT_NULL(list->next);
    AddNode(list, "test");
    TEST_ASSERT_EQUAL_STRING("test", list->data);
    TEST_ASSERT_NULL(list->next);
    AddNode(list, "test2");
    TEST_ASSERT_EQUAL_STRING("test2", list->next->data);
    TEST_ASSERT_NULL(list->next->next);
    DeleteList(list);
}

void testLinkedListDeleteList(void)
{
    Node *list = InitList();
    AddNode(list, 1);
    AddNode(list, 2);
    AddNode(list, 3);
    DeleteList(list);
    TEST_ASSERT_NULL(list->data);
}

void resetTest(void)
{
    tearDown();
    setUp();
}

int main(void)
{
    UnityBegin("test_linked_list.c");
    RUN_TEST(testLinkedListAddNode, 33);
    RUN_TEST(testLinkedListDeleteList, 44);
    UnityEnd();
}