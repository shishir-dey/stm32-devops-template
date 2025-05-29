#include "data/circular_queue.h"
#include "data/linked_list.h"
#include "data/priority_queue.h"
#include "data/queue.h"

// Queue data structures
queue_t regular_queue;
circular_queue_t circular_queue;
priority_queue_t priority_queue;

// Test data
char* task1 = "Task 1";
char* task2 = "Task 2";
char* task3 = "Task 3";
char* task4 = "Task 4";

// Function to demonstrate regular queue
void demonstrate_regular_queue(void){
    char* dequeued_data;

    // Initialize and test regular queue
    queue_init(&regular_queue);

    // Enqueue some tasks
    queue_enqueue(&regular_queue, task1);
    queue_enqueue(&regular_queue, task2);
    queue_enqueue(&regular_queue, task3);

    // Dequeue tasks (FIFO order)
    while (!queue_is_empty(&regular_queue)) {
        queue_dequeue(&regular_queue, (void**)&dequeued_data);
        // Process dequeued data (in embedded system, you might trigger GPIO, etc.)
    }
}

// Function to demonstrate circular queue
void demonstrate_circular_queue(void){
    char* dequeued_data;

    // Initialize circular queue
    circular_queue_init(&circular_queue);

    // Enqueue some tasks
    circular_queue_enqueue(&circular_queue, task1);
    circular_queue_enqueue(&circular_queue, task2);

    // Dequeue one task
    circular_queue_dequeue(&circular_queue, (void**)&dequeued_data);

    // Add more tasks (demonstrating circular nature)
    circular_queue_enqueue(&circular_queue, task3);
    circular_queue_enqueue(&circular_queue, task4);

    // Process remaining tasks
    while (!circular_queue_is_empty(&circular_queue)) {
        circular_queue_dequeue(&circular_queue, (void**)&dequeued_data);
        // Process dequeued data
    }
}

// Function to demonstrate priority queue
void demonstrate_priority_queue(void){
    char* dequeued_data;
    int dequeued_priority;

    // Initialize priority queue
    priority_queue_init(&priority_queue);

    // Enqueue tasks with different priorities
    priority_queue_enqueue(&priority_queue, task1, 1);  // Low priority
    priority_queue_enqueue(&priority_queue, task2, 10); // High priority
    priority_queue_enqueue(&priority_queue, task3, 5);  // Medium priority
    priority_queue_enqueue(&priority_queue, task4, 15); // Highest priority

    // Process tasks in priority order (highest first)
    while (!priority_queue_is_empty(&priority_queue)) {
        priority_queue_dequeue(&priority_queue, (void**)&dequeued_data, &dequeued_priority);
        // Process high-priority task first
    }
}

// Original linked list demonstration (keeping for compatibility)
void demonstrate_linked_list(void){
    node_t node1, node2, node3, node4;
    char* str1 = "Node 1";
    char* str2 = "Node 2";
    char* str3 = "Node 3";
    char* str4 = "Node 4";

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
}

int main()
{
    // Demonstrate all data structures
    demonstrate_linked_list();
    demonstrate_regular_queue();
    demonstrate_circular_queue();
    demonstrate_priority_queue();

    return 0;
}