Data Structures API
===================

This section provides detailed API documentation for all data structures implemented in the STM32 DevOps Template.

Common Types
------------

All data structures use common return types and constants defined in `common_types.h`:

.. doxygenenum:: status_t
   :project: STM32DevOpsTemplate

.. doxygendefine:: SUCCESS
   :project: STM32DevOpsTemplate

.. doxygendefine:: FAILURE
   :project: STM32DevOpsTemplate

Queue API
---------

Regular FIFO Queue Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenstruct:: queue_t
   :project: STM32DevOpsTemplate
   :members:

.. doxygenfunction:: queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_peek
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: queue_size
   :project: STM32DevOpsTemplate

Circular Queue API
------------------

Ring Buffer Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenstruct:: circular_queue_t
   :project: STM32DevOpsTemplate
   :members:

.. doxygenfunction:: circular_queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_peek
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: circular_queue_size
   :project: STM32DevOpsTemplate

Priority Queue API
------------------

Binary Max-Heap Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenstruct:: priority_queue_element_t
   :project: STM32DevOpsTemplate
   :members:

.. doxygenstruct:: priority_queue_t
   :project: STM32DevOpsTemplate
   :members:

.. doxygenfunction:: priority_queue_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_enqueue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_dequeue
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_peek
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_is_empty
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_is_full
   :project: STM32DevOpsTemplate

.. doxygenfunction:: priority_queue_size
   :project: STM32DevOpsTemplate

Linked List API
---------------

Traditional Linked List Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenstruct:: node_t
   :project: STM32DevOpsTemplate
   :members:

.. doxygenfunction:: ll_init
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_insert_at_head
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_insert_at_tail
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_delete_at_head
   :project: STM32DevOpsTemplate

.. doxygenfunction:: ll_delete_at_tail
   :project: STM32DevOpsTemplate 