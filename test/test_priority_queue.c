#include "../lib/Unity/src/unity.h"
#include "../src/data/priority_queue.h"

// Global priority queue variable
priority_queue_t test_priority_queue;

void setUp(void)
{
    priority_queue_init(&test_priority_queue);
}

void tearDown(void)
{}

void resetTest(void)
{
    tearDown();
    setUp();
}

void test_priority_queue_init(void)
{
    priority_queue_t queue;

    TEST_ASSERT_EQUAL(SUCCESS, priority_queue_init(&queue));
    TEST_ASSERT_EQUAL(0, priority_queue_size(&queue));
    TEST_ASSERT_TRUE(priority_queue_is_empty(&queue));
    TEST_ASSERT_FALSE(priority_queue_is_full(&queue));
}

void test_priority_queue_init_null(void)
{
    TEST_ASSERT_EQUAL(FAILURE, priority_queue_init(NULL));
}

void test_priority_queue_enqueue(void)
{
    resetTest();
    char* test_data = "test_data";
    int priority = 5;
    TEST_ASSERT_EQUAL(SUCCESS, priority_queue_enqueue(&test_priority_queue, test_data, priority));
    TEST_ASSERT_EQUAL(1, priority_queue_size(&test_priority_queue));
    TEST_ASSERT_FALSE(priority_queue_is_empty(&test_priority_queue));
}

void test_priority_queue_enqueue_multiple(void)
{
    resetTest();
    char* data1 = "data1";
    char* data2 = "data2";
    char* data3 = "data3";

    TEST_ASSERT_EQUAL(SUCCESS, priority_queue_enqueue(&test_priority_queue, data1, 1));
    TEST_ASSERT_EQUAL(SUCCESS, priority_queue_enqueue(&test_priority_queue, data2, 2));
    TEST_ASSERT_EQUAL(SUCCESS, priority_queue_enqueue(&test_priority_queue, data3, 3));
    TEST_ASSERT_EQUAL(3, priority_queue_size(&test_priority_queue));
}

void test_priority_queue_dequeue(void)
{
    resetTest();
    char* test_data = "test_data";
    char* dequeued_data;
    int test_priority = 5;
    int dequeued_priority;

    priority_queue_enqueue(&test_priority_queue, test_data, test_priority);
    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(test_data, dequeued_data);
    TEST_ASSERT_EQUAL(test_priority, dequeued_priority);
    TEST_ASSERT_EQUAL(0, priority_queue_size(&test_priority_queue));
    TEST_ASSERT_TRUE(priority_queue_is_empty(&test_priority_queue));
}

void test_priority_queue_dequeue_priority_order(void)
{
    resetTest();
    char* low_priority = "low";
    char* medium_priority = "medium";
    char* high_priority = "high";
    char* dequeued_data;
    int dequeued_priority;

    // Add elements in mixed order
    priority_queue_enqueue(&test_priority_queue, medium_priority, 5);
    priority_queue_enqueue(&test_priority_queue, low_priority, 1);
    priority_queue_enqueue(&test_priority_queue, high_priority, 10);

    // Should dequeue in priority order (highest first)
    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(high_priority, dequeued_data);
    TEST_ASSERT_EQUAL(10, dequeued_priority);

    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(medium_priority, dequeued_data);
    TEST_ASSERT_EQUAL(5, dequeued_priority);

    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(low_priority, dequeued_data);
    TEST_ASSERT_EQUAL(1, dequeued_priority);
}

void test_priority_queue_dequeue_empty(void)
{
    resetTest();
    char* dequeued_data;
    int dequeued_priority;
    TEST_ASSERT_EQUAL(
        FAILURE,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
}

void test_priority_queue_peek(void)
{
    resetTest();
    char* test_data = "test_data";
    char* peeked_data;
    int test_priority = 5;
    int peeked_priority;

    priority_queue_enqueue(&test_priority_queue, test_data, test_priority);
    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_peek(
            &test_priority_queue,
            (void**)&peeked_data,
            &peeked_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(test_data, peeked_data);
    TEST_ASSERT_EQUAL(test_priority, peeked_priority);
    TEST_ASSERT_EQUAL(1, priority_queue_size(&test_priority_queue)); // Size should not change
}

void test_priority_queue_peek_highest_priority(void)
{
    resetTest();
    char* low_priority = "low";
    char* high_priority = "high";
    char* peeked_data;
    int peeked_priority;

    priority_queue_enqueue(&test_priority_queue, low_priority, 1);
    priority_queue_enqueue(&test_priority_queue, high_priority, 10);

    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_peek(
            &test_priority_queue,
            (void**)&peeked_data,
            &peeked_priority
        )
    );
    TEST_ASSERT_EQUAL_STRING(high_priority, peeked_data);
    TEST_ASSERT_EQUAL(10, peeked_priority);
}

void test_priority_queue_peek_empty(void)
{
    resetTest();
    char* peeked_data;
    int peeked_priority;
    TEST_ASSERT_EQUAL(
        FAILURE,
        priority_queue_peek(
            &test_priority_queue,
            (void**)&peeked_data,
            &peeked_priority
        )
    );
}

void test_priority_queue_full(void)
{
    resetTest();
    char data[10];

    // Fill the queue to capacity
    for (int i = 0; i < PRIORITY_QUEUE_MAX_SIZE; i++) {
        TEST_ASSERT_EQUAL(SUCCESS, priority_queue_enqueue(&test_priority_queue, &data[i % 10], i));
    }

    TEST_ASSERT_TRUE(priority_queue_is_full(&test_priority_queue));
    TEST_ASSERT_EQUAL(PRIORITY_QUEUE_MAX_SIZE, priority_queue_size(&test_priority_queue));

    // Try to add one more - should fail
    TEST_ASSERT_EQUAL(FAILURE, priority_queue_enqueue(&test_priority_queue, &data[0], 1000));
}

void test_priority_queue_same_priority(void)
{
    resetTest();
    char* data1 = "first";
    char* data2 = "second";
    char* dequeued_data;
    int dequeued_priority;

    // Add elements with same priority
    priority_queue_enqueue(&test_priority_queue, data1, 5);
    priority_queue_enqueue(&test_priority_queue, data2, 5);

    // Both should be accessible (order may vary due to heap structure)
    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL(5, dequeued_priority);

    TEST_ASSERT_EQUAL(
        SUCCESS,
        priority_queue_dequeue(
            &test_priority_queue,
            (void**)&dequeued_data,
            &dequeued_priority
        )
    );
    TEST_ASSERT_EQUAL(5, dequeued_priority);
}

void test_priority_queue_dynamic_operations(void)
{
    resetTest();
    char* data1 = "task1";
    char* data2 = "task2";
    char* data3 = "task3";
    char* dequeued_data;
    int dequeued_priority;

    // Mix enqueue and dequeue operations
    priority_queue_enqueue(&test_priority_queue, data1, 3);
    priority_queue_enqueue(&test_priority_queue, data2, 1);

    // Dequeue highest priority
    priority_queue_dequeue(&test_priority_queue, (void**)&dequeued_data, &dequeued_priority);
    TEST_ASSERT_EQUAL_STRING(data1, dequeued_data);
    TEST_ASSERT_EQUAL(3, dequeued_priority);

    // Add another element
    priority_queue_enqueue(&test_priority_queue, data3, 5);

    // Dequeue highest priority again
    priority_queue_dequeue(&test_priority_queue, (void**)&dequeued_data, &dequeued_priority);
    TEST_ASSERT_EQUAL_STRING(data3, dequeued_data);
    TEST_ASSERT_EQUAL(5, dequeued_priority);

    // Dequeue last element
    priority_queue_dequeue(&test_priority_queue, (void**)&dequeued_data, &dequeued_priority);
    TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);
    TEST_ASSERT_EQUAL(1, dequeued_priority);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_priority_queue_init);
    RUN_TEST(test_priority_queue_init_null);
    RUN_TEST(test_priority_queue_enqueue);
    RUN_TEST(test_priority_queue_enqueue_multiple);
    RUN_TEST(test_priority_queue_dequeue);
    RUN_TEST(test_priority_queue_dequeue_priority_order);
    RUN_TEST(test_priority_queue_dequeue_empty);
    RUN_TEST(test_priority_queue_peek);
    RUN_TEST(test_priority_queue_peek_highest_priority);
    RUN_TEST(test_priority_queue_peek_empty);
    RUN_TEST(test_priority_queue_full);
    RUN_TEST(test_priority_queue_same_priority);
    RUN_TEST(test_priority_queue_dynamic_operations);

    return UNITY_END();
}