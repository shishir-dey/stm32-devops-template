#include "../lib/Unity/src/unity.h"
#include "../src/data/linked_list.h"

// Global node variables
node_t test_node_initial;
node_t test_node1;
node_t test_node2;

void setUp(void)
{
    ll_init(&test_node_initial);
}

void tearDown(void)
{}

void resetTest(void)
{
    tearDown();
    setUp();
}

void test_ll_init(void)
{
    TEST_ASSERT_EQUAL(SUCCESS, ll_init(&test_node_initial));
}

void test_ll_insert_at_head(void)
{
    resetTest();
    test_node1.data = "test";
    test_node1.next = NULL;
    TEST_ASSERT_EQUAL(SUCCESS, ll_insert_at_head(&test_node1));
}

void test_ll_insert_at_tail(void)
{
    resetTest();
    test_node1.data = "test1";
    test_node1.next = NULL;
    test_node2.data = "test2";
    test_node2.next = NULL;
    TEST_ASSERT_EQUAL(SUCCESS, ll_insert_at_tail(&test_node1));
    TEST_ASSERT_EQUAL(SUCCESS, ll_insert_at_tail(&test_node2));
}

void test_ll_delete_at_head(void)
{
    resetTest();
    test_node1.data = "test";
    test_node1.next = NULL;
    ll_insert_at_head(&test_node1);
    TEST_ASSERT_EQUAL(SUCCESS, ll_delete_at_head());
}

void test_ll_delete_at_tail(void)
{
    resetTest();
    test_node1.data = "test1";
    test_node1.next = NULL;
    test_node2.data = "test2";
    test_node2.next = NULL;
    ll_insert_at_tail(&test_node1);
    ll_insert_at_tail(&test_node2);
    TEST_ASSERT_EQUAL(SUCCESS, ll_delete_at_tail());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ll_init);
    RUN_TEST(test_ll_insert_at_head);
    RUN_TEST(test_ll_insert_at_tail);
    RUN_TEST(test_ll_delete_at_head);
    RUN_TEST(test_ll_delete_at_tail);

    return UNITY_END();
}