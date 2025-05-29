#include "../lib/Unity/src/unity.h"
#include "../src/data/queue.h"

// Global queue variable
queue_t test_queue;

void setUp(void)
{
    queue_init(&test_queue);
}

void tearDown(void)
{}

void resetTest(void)
{
    tearDown();
    setUp();
}

void test_queue_init(void)
{
    queue_t queue;

    TEST_ASSERT_EQUAL(SUCCESS, queue_init(&queue));
    TEST_ASSERT_EQUAL(0, queue_size(&queue));
    TEST_ASSERT_TRUE(queue_is_empty(&queue));
    TEST_ASSERT_FALSE(queue_is_full(&queue));
}

void test_queue_init_null(void)
{
    TEST_ASSERT_EQUAL(FAILURE, queue_init(NULL));
}

void test_queue_enqueue(void)
{
    resetTest();
    char* test_data = "test_data";
    TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, test_data));
    TEST_ASSERT_EQUAL(1, queue_size(&test_queue));
    TEST_ASSERT_FALSE(queue_is_empty(&test_queue));
}

void test_queue_enqueue_multiple(void)
{
    resetTest();
    char* data1 = "data1";
    char* data2 = "data2";
    char* data3 = "data3";

    TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, data1));
    TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, data2));
    TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, data3));
    TEST_ASSERT_EQUAL(3, queue_size(&test_queue));
}

void test_queue_dequeue(void)
{
    resetTest();
    char* test_data = "test_data";
    char* dequeued_data;

    queue_enqueue(&test_queue, test_data);
    TEST_ASSERT_EQUAL(SUCCESS, queue_dequeue(&test_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(test_data, dequeued_data);
    TEST_ASSERT_EQUAL(0, queue_size(&test_queue));
    TEST_ASSERT_TRUE(queue_is_empty(&test_queue));
}

void test_queue_dequeue_fifo_order(void)
{
    resetTest();
    char* data1 = "first";
    char* data2 = "second";
    char* data3 = "third";
    char* dequeued_data;

    queue_enqueue(&test_queue, data1);
    queue_enqueue(&test_queue, data2);
    queue_enqueue(&test_queue, data3);

    TEST_ASSERT_EQUAL(SUCCESS, queue_dequeue(&test_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data1, dequeued_data);

    TEST_ASSERT_EQUAL(SUCCESS, queue_dequeue(&test_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);

    TEST_ASSERT_EQUAL(SUCCESS, queue_dequeue(&test_queue, (void**)&dequeued_data));
    TEST_ASSERT_EQUAL_STRING(data3, dequeued_data);
}

void test_queue_dequeue_empty(void)
{
    resetTest();
    char* dequeued_data;
    TEST_ASSERT_EQUAL(FAILURE, queue_dequeue(&test_queue, (void**)&dequeued_data));
}

void test_queue_peek(void)
{
    resetTest();
    char* test_data = "test_data";
    char* peeked_data;

    queue_enqueue(&test_queue, test_data);
    TEST_ASSERT_EQUAL(SUCCESS, queue_peek(&test_queue, (void**)&peeked_data));
    TEST_ASSERT_EQUAL_STRING(test_data, peeked_data);
    TEST_ASSERT_EQUAL(1, queue_size(&test_queue)); // Size should not change
}

void test_queue_peek_empty(void)
{
    resetTest();
    char* peeked_data;
    TEST_ASSERT_EQUAL(FAILURE, queue_peek(&test_queue, (void**)&peeked_data));
}

void test_queue_full(void)
{
    resetTest();
    char data[10];

    // Fill the queue to capacity
    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, &data[i % 10]));
    }

    TEST_ASSERT_TRUE(queue_is_full(&test_queue));
    TEST_ASSERT_EQUAL(QUEUE_MAX_SIZE, queue_size(&test_queue));

    // Try to add one more - should fail
    TEST_ASSERT_EQUAL(FAILURE, queue_enqueue(&test_queue, &data[0]));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_queue_init);
    RUN_TEST(test_queue_init_null);
    RUN_TEST(test_queue_enqueue);
    RUN_TEST(test_queue_enqueue_multiple);
    RUN_TEST(test_queue_dequeue);
    RUN_TEST(test_queue_dequeue_fifo_order);
    RUN_TEST(test_queue_dequeue_empty);
    RUN_TEST(test_queue_peek);
    RUN_TEST(test_queue_peek_empty);
    RUN_TEST(test_queue_full);

    return UNITY_END();
}