Testing Framework
=================

The STM32 DevOps Template uses the Unity testing framework to ensure code quality and reliability through comprehensive unit testing.

Unity Testing Framework
-----------------------

Unity is a lightweight, C-based unit testing framework designed for embedded systems. It provides:

* **Minimal Dependencies**: Pure C implementation with no external dependencies
* **Cross-Platform**: Runs on both host systems and embedded targets
* **Rich Assertions**: Comprehensive set of assertion macros
* **Test Organization**: Structured test suites and runners

Test Structure
--------------

Each data structure has its own dedicated test file:

.. code-block:: text

   test/
   ├── test_queue.c           # Regular queue tests
   ├── test_circular_queue.c  # Circular queue tests
   ├── test_priority_queue.c  # Priority queue tests
   └── test_linked_list.c     # Linked list tests

Test Organization
~~~~~~~~~~~~~~~~~

Each test file follows a consistent structure:

.. code-block:: c

   #include "../lib/Unity/src/unity.h"
   #include "../src/data/queue.h"
   
   // Global test variables
   queue_t test_queue;
   
   void setUp(void) {
       // Initialize before each test
       queue_init(&test_queue);
   }
   
   void tearDown(void) {
       // Cleanup after each test
   }
   
   void resetTest(void) {
       tearDown();
       setUp();
   }
   
   // Individual test functions
   void test_queue_init(void) {
       // Test implementation
   }
   
   int main(void) {
       UNITY_BEGIN();
       RUN_TEST(test_queue_init);
       // ... more tests
       return UNITY_END();
   }

Running Tests
-------------

**Host-Based Testing (Recommended for Development)**

.. code-block:: bash

   # Configure for host testing
   mkdir build && cd build
   cmake -DHOST=ON ..
   
   # Build all tests
   make
   
   # Run all tests
   ctest
   
   # Run specific test
   ./test_queue
   
   # Run tests with verbose output
   ctest --verbose

**Manual Test Execution**

.. code-block:: bash

   # Run individual test files
   cd build
   ./test_queue
   ./test_circular_queue
   ./test_priority_queue
   ./test_linked_list

Test Coverage
-------------

The test suite provides comprehensive coverage for all implemented functionality:

Regular Queue Tests
~~~~~~~~~~~~~~~~~~~

* Initialization and state validation
* Enqueue/dequeue operations
* FIFO order verification
* Boundary conditions (empty/full)
* Error handling for invalid inputs
* Queue size tracking

.. code-block:: c

   void test_queue_dequeue_fifo_order(void) {
       char* data1 = "first";
       char* data2 = "second";
       char* data3 = "third";
       char* dequeued_data;
       
       queue_enqueue(&test_queue, data1);
       queue_enqueue(&test_queue, data2);
       queue_enqueue(&test_queue, data3);
       
       // Verify FIFO order
       queue_dequeue(&test_queue, (void**)&dequeued_data);
       TEST_ASSERT_EQUAL_STRING(data1, dequeued_data);
       
       queue_dequeue(&test_queue, (void**)&dequeued_data);
       TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);
   }

Circular Queue Tests
~~~~~~~~~~~~~~~~~~~~

* Wrap-around behavior validation
* Mixed enqueue/dequeue operations
* Full buffer handling
* Size calculation accuracy

.. code-block:: c

   void test_circular_queue_wrap_around(void) {
       // Fill partially, remove some, add more
       circular_queue_enqueue(&test_queue, data1);
       circular_queue_enqueue(&test_queue, data2);
       
       circular_queue_dequeue(&test_queue, (void**)&dequeued_data);
       
       // This should wrap around in the buffer
       circular_queue_enqueue(&test_queue, data3);
       
       // Verify correct order maintained
       circular_queue_dequeue(&test_queue, (void**)&dequeued_data);
       TEST_ASSERT_EQUAL_STRING(data2, dequeued_data);
   }

Priority Queue Tests
~~~~~~~~~~~~~~~~~~~~

* Priority-based ordering
* Binary heap property maintenance
* Dynamic priority operations
* Edge cases with equal priorities

.. code-block:: c

   void test_priority_queue_dequeue_priority_order(void) {
       // Add in mixed priority order
       priority_queue_enqueue(&test_queue, low_data, 1);
       priority_queue_enqueue(&test_queue, high_data, 10);
       priority_queue_enqueue(&test_queue, medium_data, 5);
       
       // Should dequeue highest priority first
       priority_queue_dequeue(&test_queue, (void**)&data, &priority);
       TEST_ASSERT_EQUAL(10, priority);
       TEST_ASSERT_EQUAL_STRING(high_data, data);
   }

Test Assertions
---------------

Unity provides a rich set of assertion macros:

**Basic Assertions**

.. code-block:: c

   TEST_ASSERT_TRUE(condition);
   TEST_ASSERT_FALSE(condition);
   TEST_ASSERT_EQUAL(expected, actual);
   TEST_ASSERT_NOT_EQUAL(expected, actual);

**Pointer Assertions**

.. code-block:: c

   TEST_ASSERT_NULL(pointer);
   TEST_ASSERT_NOT_NULL(pointer);
   TEST_ASSERT_EQUAL_PTR(expected, actual);

**String Assertions**

.. code-block:: c

   TEST_ASSERT_EQUAL_STRING(expected, actual);
   TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, length);

**Numeric Assertions**

.. code-block:: c

   TEST_ASSERT_EQUAL_INT(expected, actual);
   TEST_ASSERT_EQUAL_UINT(expected, actual);
   TEST_ASSERT_GREATER_THAN(threshold, actual);

Continuous Integration
----------------------

Tests are automatically executed in the CI/CD pipeline:

**GitHub Actions Integration**

.. code-block:: yaml

   - name: Build and test
     run: |
       mkdir build && cd build
       cmake -DHOST=ON ..
       make
       ctest --output-on-failure

**Test Results**

* All tests must pass for pull request approval
* Test results are reported in GitHub Actions logs
* Coverage reports help identify untested code paths

Best Practices
--------------

**Test Design Principles**

* **Isolation**: Each test is independent and can run in any order
* **Repeatability**: Tests produce consistent results across runs
* **Clarity**: Test names clearly describe what is being tested
* **Coverage**: All public APIs and edge cases are tested

**Test Data Management**

.. code-block:: c

   // Use consistent test data
   static char* test_data_1 = "test_string_1";
   static char* test_data_2 = "test_string_2";
   static int test_priority_high = 10;
   static int test_priority_low = 1;

**Error Condition Testing**

.. code-block:: c

   void test_queue_enqueue_full(void) {
       // Fill queue to capacity
       for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
           TEST_ASSERT_EQUAL(SUCCESS, queue_enqueue(&test_queue, &data));
       }
       
       // Next enqueue should fail
       TEST_ASSERT_EQUAL(FAILURE, queue_enqueue(&test_queue, &data));
   }

Memory Testing
--------------

Since the project uses static allocation, memory testing focuses on:

* **Bounds Checking**: Ensure array access stays within bounds
* **State Consistency**: Verify internal state remains valid
* **Resource Management**: Check for proper initialization/cleanup

**Static Analysis Integration**

The project can be integrated with static analysis tools:

.. code-block:: bash

   # Example with Cppcheck
   cppcheck --enable=all --inconclusive src/
   
   # Example with PC-lint
   lint-nt -i"lib/Unity/src" src/*.c

Test-Driven Development
-----------------------

The project demonstrates TDD principles:

1. **Write Test First**: Define expected behavior through tests
2. **Implement Minimally**: Write just enough code to pass the test
3. **Refactor**: Improve code while maintaining test coverage

**Example TDD Workflow**

.. code-block:: c

   // 1. Write failing test
   void test_new_feature(void) {
       TEST_ASSERT_EQUAL(SUCCESS, new_feature_function());
   }
   
   // 2. Implement minimal functionality
   status_t new_feature_function(void) {
       return SUCCESS;  // Minimal implementation
   }
   
   // 3. Refactor with confidence
   status_t new_feature_function(void) {
       // Full implementation with error checking
       if (validate_input() != SUCCESS) {
           return FAILURE;
       }
       return perform_operation();
   }

Debugging Failed Tests
----------------------

**Common Debugging Techniques**

.. code-block:: c

   void test_with_debug_output(void) {
       printf("Test starting...\n");
       
       // Test operation
       status_t result = queue_enqueue(&test_queue, data);
       printf("Enqueue result: %d\n", result);
       
       // Assertion with context
       TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "Enqueue failed");
   }

**Using GDB with Tests**

.. code-block:: bash

   # Compile with debug info
   cmake -DHOST=ON -DCMAKE_BUILD_TYPE=Debug ..
   make
   
   # Debug specific test
   gdb ./test_queue
   (gdb) break test_specific_function
   (gdb) run 