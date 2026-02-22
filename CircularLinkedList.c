/************************************************************
 * @filename: CircularLinkedList.c
 * @brief：实现单向循环列表的基本操作
 * @author：Lcccch_0816@163.com
 * @date: 2026-01-25
 * @version: V1.0
 * @note:NULL
 * CopyRight (c) 2026-2027, Lcccch_0816@163.com All Rights Reserved
 ************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>






//指的是单向链表中的结点有效数据类型，用户可以根据需要进行修改
 typedef int DataType_t;
//构造链表节点，链表中所有节点的数据类型应该是相同的
 typedef struct CircularLinkedList { 
     DataType_t         Data; //结点的数据域
     struct CircularLinkedList *next; //结点的指针域
 } CircLList_t;

 //链表初始化,也就是创建一个空链表，空链表应该有一个头节点。头节点是链表中第一个节点，头节点不存储有效数据，头节点指向链表中第一个有效数据节点
 CircLList_t * CircLList_Create(void) {
     //1.创建一个头结点，给头结点申请内存空间
     CircLList_t *head = (CircLList_t *)calloc(1,sizeof(CircLList_t));
     //2.判断头结点是否创建成功
     if (NULL == head) {
         perror("calloc failed!\n");
         return NULL;
     }
     //3.将头结点的指针域指向自己,头结点不存储有效的内容！！！
     head->next = head;
     //4.返回头结点
     return head;
 }

 //创建新的结点，并对新结点进行初始化（数据域+指针域）
 CircLList_t * CircLList_CreateNode(DataType_t data) {
     //1.给新结点申请内存空间
     CircLList_t *New= (CircLList_t *)calloc(1,sizeof(CircLList_t));
     //2.判断新结点是否创建成功
     if (NULL == New) {
         perror("calloc failed!\n");
         return NULL;
        }
        //3.将新结点的数据域赋值 将新结点的指针域置为NULL,也就是将新结点的指针域和数据域进行初始化
        New->Data = data;
        New->next = NULL;
        return New;
 }


/**
 * @name: CircLList_HeadInsert
 * @brief:在单向循环链表头结点处插入一个新节点
 * @parma:head 单向循环链表的头结点地址 data新节点的数据域
 * @return：bool 插入成果则返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，直接插入新节点，并将新节点的指针域指向头结点
 */
 //在头结点处插入一个新结点
bool CircLList_HeadInsert(CircLList_t *head, DataType_t data) { 
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    CircLList_t *New = CircLList_CreateNode(data);
    //2.判断链表是否为空链表
    if (head == head->next) {
        head->next = New;//将头结点的指针域指向新结点
        New->next = head->next;//将新结点的指针域指向头结点
        return true;
    }
    //3.链表不为空链表，找到链表的尾节点
    CircLList_t *p = head->next;
    while(p->next != head->next)
    {
        p = p->next; //将p指针指向链表的尾节点
    }
     p->next =New;
     New->next = head->next;
     head->next = New;
     return true;

}


/**
 * @name: CircLList_TailInsert
 * @brief:在单向循环链表尾部插入一个新结点
 * @param:head 循环链表的头结点地址 data新节点的有效数据
 * @return：bool 插入成功返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，直接插入新节点，并将新节点的指针域指向头结点
 */
bool CircLList_TailInsert(CircLList_t *head, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    CircLList_t *New = CircLList_CreateNode(data);
    //2.判断链表是否为空链表
    if (head == head->next) {
        head->next = New;//将头结点的指针域指向新结点
        New->next = head;//将新结点的指针域指向头结点
        return true;
    }
    //3.链表不为空链表，找到链表的尾节点
    CircLList_t *p = head;
    while(p->next !=head->next) {
        p = p->next; //将p指针指向链表的尾节点
    }
    p->next = New;
    New->next = head->next;
    return true;
}


/**
 * @name: CircLList_midInsert
 * @brief:在单向循环链表中的目标节点后面插入一个新节点
 * @param: head 单向循环链表的头结点地址
 *         data 新节点的数据域
 *         dest 目标节点的数据域
 * @return： bool 插入成功返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，直接插入新节点，并将新节点的指针域指向头结点
 */
bool CircList_midInsert(CircLList_t *head, DataType_t data, DataType_t dest) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    CircLList_t *New = CircLList_CreateNode(data);
    //2.判断链表是否为空链表
    if (head == head->next) {
        head->next = New;//将头结点的指针域指向新结点
        New->next = head->next;//将新结点的指针域指向头结点
        return true;
    }
    //3.遍历链表，找到目标节点
    CircLList_t *p = head->next;
    while(p != head->next && dest != p->Data) {
        p = p->next;
    }
    //4.在目标节点的后面插入新结点
    New ->next = p->next;
    p ->next = New;
    return true;
}

/**
 * @name： CircLList_DleHead
 * @brief：删除单向循环链表中的首结点
 * @param：head 头结点的地址
 * @return： bool 删除成功返回true，失败返回false
 * @date: 2026-01-25
 * @version: V1.0
 * @note: 如果链表为空链表，删除失败，显示链表为空，删除失败。
 */
bool CircLList_DleHead(CircLList_t *head) {
    //1.判断单向循环链表是否为空链表
    CircLList_t *p = head->next; //将p指针指向链表的首结点
    if(head == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    if(p->next == head->next) {
        head->next = head;//将头结点的指针域指向自己
        p->next = NULL;//断开首结点与头结点的连接
        free(p);//释放首结点的内存空间
        return false;
    }
    //2.找到链表的尾节点
    while(p->next != head->next) {
        p = p->next; //将p指针指向链表的尾节点
    }
    p->next = head->next->next;
    head->next = head->next->next;
    head ->next->next = NULL;//断开首结点与直接后继的练习，将首结点的直接后继指向NULL
    free(head->next);//释放首结点的内存空间
    return true;
}

bool CircLList_DleTail(CircLList_t *head) {
    //1.判断单向循环链表是否为空链表
    if(head == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    //2.找到链表的尾节点
    CircLList_t *p = head->next;
    CircLList_t *q = head;
    while(p->next != head->next) {
        p = p->next; //将p指针指向链表的尾节点
        q = q->next; //将q指针指向链表的尾节点的前驱节点
    }
    q->next = head->next;
    p->next = NULL;
    free(p);
    return true;
}



bool CircLList_DleDest(CircLList_t *head, DataType_t dest) {
    //1.判断单向循环链表是否为空链表
    if(head == head->next) {
        printf("链表为空，无法删除\n");
        return false;
    }
    //2.找到目标节点
    CircLList_t *p = head->next;
    CircLList_t *q = head;
    while(p != head->next && dest != p->Data) {
        q = p;
        p = p->next;
    }
    if(p == head->next) {
        printf("未找到目标节点，删除失败\n");
        return false;
    }
    q->next = p->next;
    p->next = NULL;
    free(p);
    return true;
}

//遍历单向循环链表并打印链表中的所有节点
void CircLList_Print(CircLList_t *head) {
    if (head->next == head) {
        printf("链表为空，无法打印\n");
        return;
    }
    CircLList_t *p = head;
    while(p->next) {
        p = p->next;
        if(p->next == head->next) {
            break;
        }
        printf("%d ",p->Data);
    }
    printf("\n");
}


int main() {
    CircLList_t *head = CircLList_Create();
    CircLList_HeadInsert(head,10);
    CircLList_HeadInsert(head,20);
    CircLList_HeadInsert(head,30);
    CircLList_HeadInsert(head,40);
    CircLList_HeadInsert(head,50);
    CircLList_Print(head);
}