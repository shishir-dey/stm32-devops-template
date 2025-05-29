#include "../lib/Unity/src/unity.h"
#include "../src/data/circular_queue.h"

// Global circular queue variable
circular_queue_t test_circular_queue;

void setUp(void)
{
    circular_queue_init(&test_circular_queue);
}

void tearDown(void)
{}

void resetTest(void)
{
    tearDown();
    setUp();
}

void test_circular_queue_init(void)
{
    circular_queue_t queue;

    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_init(&queue));
    TEST_ASSERT_EQUAL(0, circular_queue_size(&queue));
    TEST_ASSERT_TRUE(circular_queue_is_empty(&queue));
    TEST_ASSERT_FALSE(circular_queue_is_full(&queue));
}

void test_circular_queue_init_null(void)
{
    TEST_ASSERT_EQUAL(FAILURE, circular_queue_init(NULL));
}

void test_circular_queue_enqueue(void)
{
    resetTest();
    char* test_data = "test_data";
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, test_data));
    TEST_ASSERT_EQUAL(1, circular_queue_size(&test_circular_queue));
    TEST_ASSERT_FALSE(circular_queue_is_empty(&test_circular_queue));
}

void test_circular_queue_enqueue_multiple(void)
{
    resetTest();
    char* data1 = "data1";
    char* data2 = "data2";
    char* data3 = "data3";

    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, data1));
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, data2));
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, data3));
    TEST_ASSERT_EQUAL(3, circular_queue_size(&test_circular_queue));
}

void test_circular_queue_dequeue(void)
{
    resetTest();
    char* test_data = "test_data";
    char* dequeued_data;

    circular_queue_enqueue(&test_circular_queue, test_data);
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(test_data, dequeued_data);
    TEST_ASSERT_EQUAL(0, circular_queue_size(&test_circular_queue));
    TEST_ASSERT_TRUE(circular_queue_is_empty(&test_circular_queue));
}

void test_circular_queue_dequeue_fifo_order(void)
{
    resetTest();
    char* data1 = "first";
    char* data2 = "second";
    char* data3 = "third";
    char* dequeued_data;

    circular_queue_enqueue(&test_circular_queue, data1);
    circular_queue_enqueue(&test_circular_queue, data2);
    circular_queue_enqueue(&test_circular_queue, data3);

    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data1, dequeued_data);

    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);

    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data3, dequeued_data);
}

void test_circular_queue_dequeue_empty(void)
{
    resetTest();
    char* dequeued_data;
    TEST_ASSERT_EQUAL(FAILURE, circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data));
}

void test_circular_queue_peek(void)
{
    resetTest();
    char* test_data = "test_data";
    char* peeked_data;

    circular_queue_enqueue(&test_circular_queue, test_data);
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_peek(&test_circular_queue, (void**)&peeked_data));
    TEST_ASSERT_EQUAL_STRING(test_data, peeked_data);
    TEST_ASSERT_EQUAL(1, circular_queue_size(&test_circular_queue)); // Size should not change
}

void test_circular_queue_peek_empty(void)
{
    resetTest();
    char* peeked_data;
    TEST_ASSERT_EQUAL(FAILURE, circular_queue_peek(&test_circular_queue, (void**)&peeked_data));
}

void test_circular_queue_full(void)
{
    resetTest();
    char data[10];

    // Fill the queue to capacity
    for (int i = 0; i < CIRCULAR_QUEUE_MAX_SIZE; i++) {
        TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, &data[i % 10]));
    }

    TEST_ASSERT_TRUE(circular_queue_is_full(&test_circular_queue));
    TEST_ASSERT_EQUAL(CIRCULAR_QUEUE_MAX_SIZE, circular_queue_size(&test_circular_queue));

    // Try to add one more - should fail
    TEST_ASSERT_EQUAL(FAILURE, circular_queue_enqueue(&test_circular_queue, &data[0]));
}

void test_circular_queue_wrap_around(void)
{
    resetTest();
    char* data1 = "data1";
    char* data2 = "data2";
    char* data3 = "data3";
    char* data4 = "data4";
    char* dequeued_data;

    // Add some elements
    circular_queue_enqueue(&test_circular_queue, data1);
    circular_queue_enqueue(&test_circular_queue, data2);
    circular_queue_enqueue(&test_circular_queue, data3);

    // Remove some elements
    circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data);
    TEST_ASSERT_EQUAL_STRING(data1, dequeued_data);
    circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data);
    TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);

    // Add more elements (this tests wrap-around)
    TEST_ASSERT_EQUAL(SUCCESS, circular_queue_enqueue(&test_circular_queue, data4));

    // Verify remaining elements are in correct order
    circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data);
    TEST_ASSERT_EQUAL_STRING(data3, dequeued_data);
    circular_queue_dequeue(&test_circular_queue, (void**)&dequeued_data);
    TEST_ASSERT_EQUAL_STRING(data4, dequeued_data);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_circular_queue_init);
    RUN_TEST(test_circular_queue_init_null);
    RUN_TEST(test_circular_queue_enqueue);
    RUN_TEST(test_circular_queue_enqueue_multiple);
    RUN_TEST(test_circular_queue_dequeue);
    RUN_TEST(test_circular_queue_dequeue_fifo_order);
    RUN_TEST(test_circular_queue_dequeue_empty);
    RUN_TEST(test_circular_queue_peek);
    RUN_TEST(test_circular_queue_peek_empty);
    RUN_TEST(test_circular_queue_full);
    RUN_TEST(test_circular_queue_wrap_around);

    return UNITY_END();
}