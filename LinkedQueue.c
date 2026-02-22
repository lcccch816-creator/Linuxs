/**********************************************************
 * @file :LinkedQueue.c
 * @brief:     链式队列的基本操作实现
 * @author:  lcccch@gmail.com
 * @date:    2026-01-31
 * @version: V1.0
 * @note:      NULL
 * CopyRight (c) 2026-2027, lcccch@gmail.com All Rights Reserved
 * **********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType_t; // 数据类型

typedef struct LinkedQueue {
    DataType_t               Data; //结点的数据域
    struct LinkedQueue      *next; //结点的指针域 //队列的当前容量，以元素为单位
} LinkedQueue_t;

//创建一个空的链式队列，空队列应该有一个头节点，并对队列进行初始化
LinkedQueue_t *LinkedQueue_Create(void) {
    LinkedQueue_t *head = (LinkedQueue_t *)calloc(1,sizeof(LinkedQueue_t));
    if (NULL == head) {
        perror("calloc failed!\n");
        exit (-1);
    }
    head->next = NULL;
    head->Data = 0;
    return head;;
}


//在链式队列尾部插入一个新结点
bool LinkedQueue_EnQueue(LinkedQueue_t *head, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    LinkedQueue_t *New = (LinkedQueue_t *)calloc(1,sizeof(LinkedQueue_t));
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    New->Data = data;
    New->next = NULL;
    //2.判断链式队列是否为空链表
     if (head->next == NULL) {
        head->next = New;
        return true;
    }
    //3.链式队列不为空链表，找到链表的尾节点
    LinkedQueue_t *p = head;
    while(p->next) {
        p = p->next;
    }
    p->next = New;
    return true;
}


//在链式队列头部删除一个结点
DataType_t LinkedQueue_DeQueue(LinkedQueue_t *head) {
    //1.判断链式队列是否为空链表
    DataType_t temp;
    if (head->next == NULL) {
        return -1; //队列为空，无法出队
    }
    //2.链式队列不为空链表，找到链表的第一个结点;
    temp = head->next->Data;
    head->next = head->next->next;
    head->next->next = NULL;
    free(head->next);
    return temp;
}