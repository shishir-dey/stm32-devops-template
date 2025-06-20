Function Reference
==================

This section provides a comprehensive reference of all functions organized by module.

Main Application Functions
--------------------------

.. doxygenfunction:: main
   :project: STM32DevOpsTemplate

.. doxygenfunction:: demonstrate_regular_queue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: demonstrate_circular_queue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: demonstrate_priority_queue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: demonstrate_linked_list
   :project: STM32DevOpsTemplate

Initialization Functions
------------------------

Functions for initializing data structures:

.. doxygenfunction:: queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_init
   :project: STM32DevOpsTemplate

Enqueue/Insert Functions
------------------------

Functions for adding elements to data structures:

.. doxygenfunction:: queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_insert_at_head
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_insert_at_tail
   :project: STM32DevOpsTemplate

Dequeue/Remove Functions
------------------------

Functions for removing elements from data structures:

.. doxygenfunction:: queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_delete_at_head
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_delete_at_tail
   :project: STM32DevOpsTemplate

Peek Functions
--------------

Functions for examining elements without removing them:

.. doxygenfunction:: queue_peek
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_peek
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_peek
   :project: STM32DevOpsTemplate

State Query Functions
---------------------

Functions for checking the state of data structures:

.. doxygenfunction:: queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_size
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_size
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_size
   :project: STM32DevOpsTemplate

Function Categories
-------------------

**Initialization Functions**
  Functions that initialize data structures to a valid initial state.

**Insertion Functions**
  Functions that add new elements to data structures.

**Removal Functions**
  Functions that remove elements from data structures.

**Query Functions**
  Functions that retrieve information about data structures without modifying them.

**State Functions**
  Functions that check the current state (empty, full, size) of data structures.

Error Handling
--------------

All functions follow consistent error handling patterns:

- Return `SUCCESS` (0) for successful operations
- Return `FAILURE` (-1) for failed operations
- Validate input parameters (NULL pointer checks)
- Check preconditions (empty/full state) before operations

**Common Error Conditions:**

- NULL pointer parameters
- Operations on full data structures (enqueue/insert)
- Operations on empty data structures (dequeue/remove/peek)
- Invalid state transitions 