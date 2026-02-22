/***
 * 
 * 
 * 
 * 
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 typedef int DataType_t;
 typedef struct CirQueue {
     DataType_t  *Addr;   //队列的基址指针
     unsigned int front;    //队头指针，指向队头元素
     unsigned int rear;     //队尾指针，指向队尾元素的下一个位置
     unsigned int size;     //队列的当前容量，以元素为单位
} CirQueue_t;

//创建循环队列
CirQueue_t *SeqQueue_Create(unsigned int size) {
    //1.利用calloc函数给循环队列申请内存空间
    CirQueue_t *queue = (CirQueue_t *)calloc(1, sizeof(CirQueue_t));
    if (NULL == queue) {
        perror("calloc failed!\n");
        exit(-1); //程序异常终止
    }

    //2.利用calloc为所有元素申请堆内存
    queue->Addr = (DataType_t *)calloc(size, sizeof(DataType_t));
    if (NULL == queue->Addr) {
        perror("calloc failed!\n");
        exit(-1); //程序异常终止
    }

    //3.初始化循环队列的各个成员变量
    queue->front = 0; //队头指针初值为0
    queue->rear = 0;  //队尾指针初值为0
    queue->size = size; //队列容量初始化
    return queue; //返回循环队列的指针
}

//判断循环队列是否已满
bool SeqQueue_IsFull(CirQueue_t *queue) {
    return ((queue->rear +1) % queue->size == queue->front) ? true : false;
}

//入队
bool SeqQueue_EnQueue(CirQueue_t *queue, DataType_t data) {
    //1.判断队列是否已满
    if (SeqQueue_IsFull(queue)) {
        printf("Queue is full!\n");
        return false;
    }
    //2.将元素入队
    queue->Addr[queue->rear] = data;
    //3.防止队尾下标越界
    queue->rear = (queue->rear + 1) % queue->size;
    return true; //入队成功
}


//判断循环队列是否为空
bool SeqQueue_IsEmpty(CirQueue_t *queue) {
    return (queue->front == queue->rear) ? true : false;
}


//出队
DataType_t SeqQueue_DeQueue(CirQueue_t *queue) {
    DataType_t data = 0;
    //1.判断队列是否为空
    if (SeqQueue_IsEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    //2.将队头元素出队
    data = queue->Addr[queue->front];
    //3.防止队头下标越界
    queue->front = (queue->front + 1) % queue->size;
    return data; //返回出队的元素
}

