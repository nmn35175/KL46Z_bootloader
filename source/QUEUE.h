/******************************************************************************
 *  Defines
 *****************************************************************************/

#define QUEUE_DATA_MAX        80
#define QUEUE_ELEMENT_MAX     4

/******************************************************************************
 *  Typedefs
 *****************************************************************************/

/*
 *  @struct         queue_element_struct_t
 *  @description    Struct of a queue element.
 *  @member         uint16_t  data_size :   Data array size
 *                  uint8_t  data[]     :   Array of data bytes
 */

typedef struct
{
    uint8_t data_size;
    uint8_t data[QUEUE_DATA_MAX];
}
queue_element_struct_t;

/*
 *  @struct         queue_struct_t
 *  @description    Struct of a queue.
 *  @member         uint8_t  get    :   Index of the front element
 *                  uint8_t  put    :   Index of the rear element
 *                  uint8_t  size   :   Queue size
 *                  queue_element_struct_t  element[]   :   Array of elements
 */

typedef struct
{
    uint8_t get;
    uint8_t put;
    uint8_t size;
    queue_element_struct_t element[QUEUE_ELEMENT_MAX];
}
queue_struct_t;

/*
 *  @emun           queue_status_t
 *  @description    Queue error status.
 *  @value          QUEUE_SUCCESS       :   No error
 *                  QUEUE_EMPTY         :   Queue is empty
 *                  QUEUE_FULL          :   Queue is full
 *                  QUEUE_ELEMENT_FULL  :   Element is full
 */

typedef enum
{
    E_QUEUE_SUCCESS         = 0,
    E_QUEUE_EMPTY           = 1,
    E_QUEUE_FULL            = 2,
    E_QUEUE_ELEMENT_FULL    = 3
}
queue_status_t;

/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       QUEUE_Init()
 *  @description    Init a queue with default starting values.
 *  @parameter      queue_struct_t* queue   :   Queue instance
 *  @return         queue_status_t          :   Queue error status
 */

queue_status_t QUEUE_Init(queue_struct_t *queue);

/*
 *  @function       QUEUE_Write()
 *  @description    Write a byte of data in to the rear element.
 *  @parameter      queue_struct_t* queue   :   Queue instance
 *                  uint8_t         data    :   A byte of data
 *  @return         queue_status_t          :   Queue error status
 */

queue_status_t QUEUE_WriteByte(queue_struct_t *queue, uint8_t data);

/*
 *  @function       QUEUE_Put()
 *  @description    Move to next element, making it a new rear.
 *  @parameter      queue_struct_t* queue   :   Queue instance
 *  @return         queue_status_t          :   Queue error status
 */

queue_status_t QUEUE_Put(queue_struct_t *queue);

/*
 *  @function       QUEUE_Read()
 *  @description    Return the element data pointer.
 *  @parameter      queue_struct_t* queue   :   Queue instance
 *                  uint8_t**       data    :   Pointer receiving data element
 *  @return         queue_status_t          :   Queue error status
 */

queue_status_t QUEUE_Read(queue_struct_t *queue, uint8_t **data);

/*
 *  @function       QUEUE_Get()
 *  @description    Move to next element, making it a new front.
 *  @parameter      queue_struct_t* queue   :   Queue instance
 *  @return         queue_status_t          :   Queue error status
 */

queue_status_t QUEUE_Get(queue_struct_t *queue);