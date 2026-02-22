/**********************************************************
 * @filename:      DoubleLinkedList.c
 * @brief:         实现双向链表的基本操作
 * @author:        Lcccch_816@163.com
 * @date:          2026-01-25
 * @version:       V1.0
 * @note:          NULL
 * CopyRight (c) 2026-2027 Lcccch_816@163.com All rights reserved.
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//指的是双向链表中的结点有效数据类型，用户可以根据需要进行修改
 typedef int DataType_t;
 //构造双向链表节点，链表中所有节点的数据类型应该是相同的
 typedef struct DoubleLinkedList {
     DataType_t              Data; //结点的数据域
     struct DoubleLinkedList *prev; //指向前一个节点的指针域
     struct DoubleLinkedList *next; //指向下一个节点的指针域
 } DblLList_t;


/**
 * @name: DblLList_Create
 * @brief: 创建一个空的双向链表
 * @param: void
 * @return: DblLList_t* 创建成功返回头结点指针，失败返回NULL
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 头节点不存储有效数据，头节点的prev指针域置为NULL，next指针域置为NULL
 */

//创建一个空的双向链表，空链表应该有一个头节点。头节点是链表中第一个节点，头节点不存储有效数据，头节点指向链表中第一个有效数据节点
 DblLList_t * DblLList_Create(void) {
     DblLList_t *head = (DblLList_t *)calloc(1,sizeof(DblLList_t));
     if (NULL == head) {
         perror("calloc failed!\n");
         return NULL;
     }
     head->prev = NULL;
     head->next = NULL;
     return head;
 }

 //创建新的结点，并对新结点进行初始化（数据域+指针域）
DblLList_t * DblLList_CreateNode(DataType_t data) {
     //1.给新结点申请内存空间
     DblLList_t *New= (DblLList_t *)calloc(1,sizeof(DblLList_t));
     //2.判断新结点是否创建成功
     if (NULL == New) {
         perror("calloc failed!\n");
         return NULL;
        }
        //3.将新结点的数据域赋值 将新结点的指针域置为NULL,也就是将新结点的指针域和数据域进行初始化
        New->Data = data;
        New->prev = NULL;
        New->next = NULL;
        return New;
 }

 //在头结点处插入一个新结点
bool DblLList_HeadInsert(DblLList_t *head, DataType_t data) { 
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DblLList_t *New = DblLList_CreateNode(data);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false;
        }
    //2.判断双向链表是否为空链表
    if (NULL == head->next) {
        head->next = New; //将头结点的next指针指向新结点
        return true;
    }
    //3.双向链表不为空链表
    New->next = head->next;//将新结点的next指针指向头结点的下一个结点
    head->next->prev = New;//将头结点的下一个结点的直接前驱prev指针指向新结点
    head->next = New; //将头结点的next指针指向新结点
    return true;
}

//在双向链表尾部插入一个新结点
bool DblLList_TailInsert(DblLList_t *head, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DblLList_t *New = DblLList_CreateNode(data);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    //2.判断双向链表是否为空链表
     if (NULL == head->next) {
        head->next = New; //将头结点的next指针指向新结点
        return true;
    }
    //3.双向链表不为空链表，找到链表的尾节点
    DblLList_t *p = head;
    while(p->next) {
        p = p->next; //将p指针指向链表的尾节点
    }
    p->next = New;
    New->prev = p;
    return true;
}


//在目标节点的后面插入一个新结点
bool DblLList_DestInsert(DblLList_t *head, DataType_t data, DataType_t dest) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DblLList_t *New = DblLList_CreateNode(data);
    //2.判断双向链表是否为空链表
     if (NULL == head->next) {
        printf("链表为空，插入失败\n");
        free(New);
        return false;
    }
    //3.遍历链表，找到目标节点
    DblLList_t *p = head->next;
    while(p->next != NULL && dest != p->Data) {
        p = p->next;
    }
    //if判断是否找到了目标节点，没有找到则插入失败，释放新结点的内存空间。
    if (NULL == p->next && dest != p->Data) {
        printf("未找到目标节点，插入失败\n");
        free(New);
        return false;
    }
    //遍历链表找到目标节点，分为两种情况：头尾中
    if (NULL == p->next) { //如果目标节点是尾节点
            p->next = New;
    New->prev = p;
    }
    else //如果目标节点是头节点
    {
        New ->next = p->next; //将新结点的next指针指向目标节点的下一个节点
        New->prev = p; //将新结点的prev指针指向目标节点
        p->next->prev = New; //将目标节点的下一个节点的prev指针指向新结点
        p->next = New; //将目标节点的next指针指向新结点
    }  
    return true;
}

/**
 * @name: DblLList_DeleteHead
 * @brief:删除双向链表的首结点
 * @param:head 双向链表的头结点地址
 * @return：bool 删除成功返回true，失败返回false
 * @date: 2026-01-25
 * @version:v1.0
 * @note: 如果链表为空链表，删除失败
 */
//删除双向链表首结点
bool DblLList_DeleteHead(DblLList_t *head) {
    //1.判断双向链表是否为空链表
    if (NULL == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    DblLList_t *p = head->next; //记录要删除的节点
    head->next = p->next; //将头结点的next指针指向要删除节点的下一个节点
    if (p->next != NULL) { //如果要删除的节点不是尾节点
        p->next->prev = NULL; //将要删除节点的下一个节点的prev指针指向NULL
    }
    p->next = NULL;
    free(p); //释放要删除节点的内存空间
    return true;
}

/**
 * @name: DblLList_DeleteTail
 * @brief: 删除双向链表的尾结点
 * @param: head 双向链表的头结点指针
 * @return： bool 删除成功返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，删除失败
 */
//删除双向链表的尾结点
bool DblLList_DeleteTail(DblLList_t *head) {
    //1.判断双向链表是否为空链表
    if (NULL == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    //2.找到链表的尾节点
    DblLList_t *p = head->next;
    while(p->next) {
        p = p->next;
    }
    p->prev->next = NULL;
    free(p);
    return true;
}

/**
 * @name: DblLList_Deletemid
 * @brief: 删除双向链表中的目标节点
 * @param: head 双向链表的头结点指针
 *         data 目标节点的数据域
 * @return： bool 删除成功返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，删除失败；如果未找到目标节点，删除失败
 */

bool DblLList_Deletemid(DblLList_t *head, DataType_t data) {
    //1.判断双向链表是否为空链表
    if (NULL == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    //2.遍历链表，找到目标节点
    DblLList_t *p = head->next;
    while(p != NULL && data != p->Data) {
        p = p->next;
    }
    //if判断是否找到了目标节点，没有找到则删除失败。
    if (NULL == p->next && data != p->Data) {
        printf("未找到目标节点，删除失败\n");
        return false;
    }
    //3.删除目标节点
    if(p->prev == NULL) {//如果目标结点为头结点的下一个结点也就是首结点
        head->next = p->next;//将头结点的下一个结点置为目标节点的下一个结点
        if(p->next != NULL) {
        p->next->prev = NULL;//将目标结点的下一个结点的prev指针置为NULL
        p->next = NULL;//将目标结点的next指针置为NULL
        }
        free(p);
    }
   else if (p->next == NULL) { //如果目标结点为尾结点
        p->prev->next = NULL;//将目标结点的前驱结点的next指针置为NULL
        p->prev = NULL;//将目标结点的prev指针置为NULL
        free(p);//释放目标结点的内存空间
    }
  else {  
    p->next->prev = p->prev;//将目标结点的下一个节点的直接前驱指向目标节点的直接前驱
    p->prev->next = p->next;//将目标结点的前驱结点的next指针指向目标结点的下一个结点
    p->next = NULL;
    p->prev = NULL;
    free(p);
  }
    return true;
}

void DblLList_Print(DblLList_t *head) {
    if (NULL == head->next) {
        printf("链表为空，无法打印\n");
        return;
    }
    DblLList_t *p = head->next;
    while(p) {
        printf("%d ", p->Data);
        p = p->next;
    }
    printf("\n");
}


int main(void) {
    DblLList_t *head = DblLList_Create();
    DblLList_HeadInsert(head, 10);
    DblLList_Deletemid(head, 10);
    DblLList_Print(head);
    return 0;
}