/*************************************************************
 * @file LinkedListStack.c
 * @brief:     链表栈的基本操作实现
 * @author:lccch816@gmail.com
 * @date:     2026-02-01
 * @version:  1.0
 * @note:      NULL
 * CopyRight (c) 2026-2027, lccch816@gmail.com All Rights Reserved
 **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int DataType_t; // 数据类型

typedef struct LinkedList {
    DataType_t               Data; //结点的数据域
    struct LinkedList  *next; //结点的指针域 
} LinkedList_t;

typedef struct LinkedListStack {
    LinkedList_t *top; //栈顶指针
    unsigned int size;     //栈的当前容量，以元素为单位
} LinkedListStack_t;

//创建一个链表栈，并对链表栈进行初始化
LinkedListStack_t *LinkedListStack_Create(void) {
    //1.给链表栈申请内存空间
    LinkedListStack_t *stack = (LinkedListStack_t *)calloc(1,sizeof(LinkedListStack_t));
    if (NULL == stack) {
        perror("calloc failed!\n");
        exit (-1);
    }
    //2.初始化栈顶指针和栈的容量
    stack->top = NULL; //栈为空栈，栈顶指针指向NULL
    stack->size = 0;   //栈的容量初始化为0
    return stack;
}

//链表栈入栈，这是头插
bool LinkedListStack_Push(LinkedListStack_t *stack, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    LinkedList_t *New = (LinkedList_t *)calloc(1,sizeof(LinkedList_t));
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    New->Data = data;
    //2.将新节点插入到栈顶
    New->next = stack->top;//头插
    stack->top = New;
    //3.更新栈的容量
    stack->size++;
    return true;
}

//链表栈出栈
DataType_t LinkedListStack_Pop(LinkedListStack_t *stack) {
    DataType_t data = 0;
    //1.判断链表栈是否为空
    if (stack->top == NULL) {
        printf("LinkedListStack is empty!\n");
        return -1; //返回-1表示出栈失败
    }
    //2.将栈顶元素弹出
    LinkedList_t *temp = stack->top; //备份栈顶节点地址
    data = temp->Data; //获取栈顶节点的数据域
    stack->top = stack->top->next; //更新栈顶指针
    free(temp); //释放栈顶节点的内存空间
    //3.更新栈的容量
    stack->size--;
    return data; //返回栈顶节点的数据域
}
