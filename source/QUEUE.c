/******************************************************************************
 *  Includes
 *****************************************************************************/

#include <stdint.h>
#include "QUEUE.h"

/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  QUEUE_Init()
 */

queue_status_t QUEUE_Init(queue_struct_t *queue)
{
    uint8_t index = 0;
    // Init get, put indexes and queue size to be 0
    queue->get = 0;
    queue->put = 0;
    queue->size = 0;
    // Init data size values of all elements to be 0
    for (index = 0; index < QUEUE_ELEMENT_MAX; ++index)
    {
        queue->element[index].data_size = 0;
    }
    return E_QUEUE_SUCCESS;
}

/*
 *  QUEUE_WriteByte()
 */

queue_status_t QUEUE_WriteByte(queue_struct_t *queue, uint8_t byte)
{
    queue_status_t _queue_status;
    uint8_t index;
    
    _queue_status = E_QUEUE_SUCCESS;
    index = queue->element[queue->put].data_size;
    
    // If queue is full
    if (queue->size == QUEUE_ELEMENT_MAX)
    {
        _queue_status = E_QUEUE_FULL;
    }
    // If element is full
    else if (index == QUEUE_DATA_MAX)
    {
        _queue_status = E_QUEUE_ELEMENT_FULL;
    }
    // Element and queue are not full
    else
    {
        // Write the data into the rear byte of the element
        (queue->element[queue->put].data)[index] = byte;
        // Increase the size (move to next byte)
        (queue->element[queue->put].data_size)++;
    }
    return _queue_status;
}

/*
 *  QUEUE_Put()
 */

queue_status_t QUEUE_Put(queue_struct_t *queue)
{
    queue_status_t _queue_status;
    
    _queue_status = E_QUEUE_SUCCESS;
    
    // If queue is full
    if (queue->size == QUEUE_ELEMENT_MAX)
    {
        _queue_status = E_QUEUE_FULL;
    }
    // Queue is not full
    else
    {
        // Move to next element to put data
        queue->put = (queue->put+1) % QUEUE_ELEMENT_MAX;
        // Increase the size of the queue
        (queue->size)++;
        // If the current element is the last one
    }
    return _queue_status;
}

/*
 *  QUEUE_Read()
 */

queue_status_t QUEUE_Read(queue_struct_t *queue, uint8_t **data)
{
    queue_status_t _queue_status;
    
    _queue_status = E_QUEUE_SUCCESS;
    
    // If queue is empty
    if (queue->size == 0)
    {
        _queue_status = E_QUEUE_EMPTY;
    }
    // Queue is not empty
    else
    {
        // Return the data in element
        *data = queue->element[queue->get].data;
    }
    return _queue_status;
}

/*
 *  QUEUE_Get()
 */

queue_status_t QUEUE_Get(queue_struct_t *queue)
{
    queue_status_t _queue_status;
    
    _queue_status = E_QUEUE_SUCCESS;
    
    // If queue is empty
    if (queue->size == 0)
    {
        _queue_status = E_QUEUE_EMPTY;
    }
    // Queue is not empty
    else
    {
        // Clear data of current element
        queue->element[queue->get].data_size = 0;
        // Move to next element to get data
        queue->get = (queue->get+1) % QUEUE_ELEMENT_MAX;
        // Decrease the size of the queue
        --(queue->size);
    }
    return _queue_status;
}