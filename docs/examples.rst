Usage Examples
==============

This section provides practical examples of using each data structure in the STM32 DevOps Template.

Regular Queue Example
---------------------

The regular queue implements First-In-First-Out (FIFO) behavior, perfect for task scheduling and buffer management.

.. code-block:: c

    #include "data/queue.h"
    
    void queue_example(void) {
        queue_t my_queue;
        char* task1 = "Process sensor data";
        char* task2 = "Update display";
        char* task3 = "Check buttons";
        char* dequeued_task;
        
        // Initialize the queue
        queue_init(&my_queue);
        
        // Add tasks to queue
        queue_enqueue(&my_queue, task1);
        queue_enqueue(&my_queue, task2);
        queue_enqueue(&my_queue, task3);
        
        // Process tasks in FIFO order
        while (!queue_is_empty(&my_queue)) {
            queue_dequeue(&my_queue, (void**)&dequeued_task);
            // Process the task
            printf("Processing: %s\n", dequeued_task);
        }
    }

**Use Cases:**
- UART receive buffer
- Command processing queue  
- Event handling system

Circular Queue Example
----------------------

The circular queue (ring buffer) is ideal for streaming data and fixed-size buffers with wrap-around behavior.

.. code-block:: c

    #include "data/circular_queue.h"
    
    void circular_queue_example(void) {
        circular_queue_t sensor_buffer;
        int sensor_readings[] = {23, 24, 25, 26, 27};
        int* reading;
        
        // Initialize the circular queue
        circular_queue_init(&sensor_buffer);
        
        // Fill buffer with sensor readings
        for (int i = 0; i < 5; i++) {
            circular_queue_enqueue(&sensor_buffer, &sensor_readings[i]);
        }
        
        // Process some readings (makes space)
        circular_queue_dequeue(&sensor_buffer, (void**)&reading);
        printf("Processed reading: %d\n", *reading);
        
        // Add new reading (demonstrates wrap-around)
        int new_reading = 28;
        circular_queue_enqueue(&sensor_buffer, &new_reading);
        
        // Process remaining readings
        while (!circular_queue_is_empty(&sensor_buffer)) {
            circular_queue_dequeue(&sensor_buffer, (void**)&reading);
            printf("Reading: %d\n", *reading);
        }
    }

**Use Cases:**
- Audio streaming buffers
- Sensor data sampling
- Communication protocol buffers

Priority Queue Example
----------------------

The priority queue processes items based on priority rather than insertion order, using a binary max-heap.

.. code-block:: c

    #include "data/priority_queue.h"
    
    typedef struct {
        char* name;
        int urgency;
    } system_task_t;
    
    void priority_queue_example(void) {
        priority_queue_t task_scheduler;
        system_task_t task1 = {"Update display", 3};
        system_task_t task2 = {"Handle interrupt", 10};
        system_task_t task3 = {"Read sensors", 5};
        system_task_t task4 = {"Emergency stop", 15};
        
        system_task_t* current_task;
        int priority;
        
        // Initialize priority queue
        priority_queue_init(&task_scheduler);
        
        // Add tasks with different priorities
        priority_queue_enqueue(&task_scheduler, &task1, task1.urgency);
        priority_queue_enqueue(&task_scheduler, &task2, task2.urgency);
        priority_queue_enqueue(&task_scheduler, &task3, task3.urgency);
        priority_queue_enqueue(&task_scheduler, &task4, task4.urgency);
        
        // Process tasks in priority order (highest first)
        while (!priority_queue_is_empty(&task_scheduler)) {
            priority_queue_dequeue(&task_scheduler, 
                                 (void**)&current_task, 
                                 &priority);
            printf("Executing [Priority %d]: %s\n", 
                   priority, current_task->name);
        }
    }

**Use Cases:**
- Interrupt handling prioritization
- Real-time task scheduling
- Error handling (critical errors first)

Linked List Example
-------------------

The linked list provides dynamic insertion and deletion capabilities with manual node management.

.. code-block:: c

    #include "data/linked_list.h"
    
    void linked_list_example(void) {
        node_t head_node, node1, node2, node3;
        char* msg1 = "First message";
        char* msg2 = "Second message";  
        char* msg3 = "Third message";
        
        // Initialize list with head node
        ll_init(&head_node);
        head_node.data = "Head node";
        
        // Prepare nodes
        node1.data = msg1;
        node1.next = NULL;
        
        node2.data = msg2;
        node2.next = NULL;
        
        node3.data = msg3;
        node3.next = NULL;
        
        // Insert at head (becomes new first)
        ll_insert_at_head(&node1);
        ll_insert_at_head(&node2);
        
        // Insert at tail (becomes last)
        ll_insert_at_tail(&node3);
        
        // List order is now: node2 -> node1 -> head_node -> node3
        
        // Remove from head and tail
        ll_delete_at_head();  // Removes node2
        ll_delete_at_tail();  // Removes node3
    }

**Use Cases:**
- Configuration parameter lists
- Event callback chains
- Dynamic task management

Error Handling
--------------

All data structures use consistent error handling with return codes:

.. code-block:: c

    #include "data/common_types.h"
    
    void error_handling_example(void) {
        queue_t my_queue;
        char* data = "test data";
        char* retrieved_data;
        
        // Always check return values
        if (queue_init(&my_queue) != SUCCESS) {
            // Handle initialization error
            return;
        }
        
        // Check for full queue before enqueuing
        if (!queue_is_full(&my_queue)) {
            if (queue_enqueue(&my_queue, data) != SUCCESS) {
                // Handle enqueue error
                return;
            }
        }
        
        // Check for empty queue before dequeuing
        if (!queue_is_empty(&my_queue)) {
            if (queue_dequeue(&my_queue, (void**)&retrieved_data) == SUCCESS) {
                // Successfully retrieved data
                printf("Retrieved: %s\n", retrieved_data);
            }
        }
    }

**Best Practices:**
- Always check return values
- Validate queue state before operations
- Handle NULL pointer cases
- Use size/empty/full functions for state checking

Integration with STM32
----------------------

Example integration with STM32 peripherals:

.. code-block:: c

    // UART receive buffer using circular queue
    circular_queue_t uart_rx_buffer;
    uint8_t uart_data_buffer[256];
    
    void UART_IRQHandler(void) {
        if (UART_RX_READY) {
            uint8_t received_byte = UART_READ_DATA();
            
            if (!circular_queue_is_full(&uart_rx_buffer)) {
                circular_queue_enqueue(&uart_rx_buffer, &received_byte);
            }
        }
    }
    
    // Task scheduler using priority queue
    priority_queue_t task_queue;
    
    void schedule_task(task_function_t task, int priority) {
        if (!priority_queue_is_full(&task_queue)) {
            priority_queue_enqueue(&task_queue, task, priority);
        }
    }
    
    void main_scheduler_loop(void) {
        task_function_t current_task;
        int priority;
        
        while (1) {
            if (!priority_queue_is_empty(&task_queue)) {
                priority_queue_dequeue(&task_queue, 
                                     (void**)&current_task, 
                                     &priority);
                current_task();  // Execute task
            }
            
            __WFI();  // Wait for interrupt
        }
    } 