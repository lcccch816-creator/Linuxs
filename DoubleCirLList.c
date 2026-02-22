/*************************************************************************
 * @filename :DoubleCirLList.c
 * @brief:     实现双向循环链表的基本操作
 * @author:Lcccch_816@163.com
 * @date:      2026-01-25
 * @version:   V1.0
 * @note:      NULL
 * CopyRight (c) 2026-2027, Lcccch_816@163.com All Rights Reserved
 * **************************************************************************/





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType_t;
//构造链表节点，链表中所有节点的数据类型应该是相同的    
typedef struct DoubleCirLList {
    DataType_t             Data; //结点的数据域
    struct DoubleCirLList *prev; //指向前一个节点的指针域
    struct DoubleCirLList *next; //指向下一个节点的指针域
} DoubleCirLList_t;

//创建一个空的双向循环链表，空链表应该有一个头结点，并对链表进行初始化
DoubleCirLList_t * DblCircLList_Create(void) {
    DoubleCirLList_t *head = (DoubleCirLList_t *)calloc(1,sizeof(DoubleCirLList_t));
    if (NULL == head) {
        perror("calloc failed!\n");
        exit (-1);
    }
    head->prev = head;
    head->next = head;
    return head;
}
//创建新的结点，并对新结点进行初始化（数据域+指针域）
DoubleCirLList_t * DblCircLList_CreateNode(DataType_t data) {
    //1.给新结点申请内存空间
    DoubleCirLList_t *New= (DoubleCirLList_t *)calloc(1,sizeof(DoubleCirLList_t));
    //2.判断新结点是否创建成功
    if (NULL == New) {
        perror("calloc failed!\n");
        return NULL;
       }
       //3.将新结点的数据域赋值 将新结点的指针域置为自身,也就是将新结点的指针域和数据域进行初始化
       New->Data = data;
       New->prev = New;
       New->next = New;
       return New;
}


bool DblCirLList_HeadInsert(DoubleCirLList_t *head, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DoubleCirLList_t *New = DblCircLList_CreateNode(data);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    //2.判断双向循环链表是否为空链表
     if (head == head->next) {
        head->next = New;
        New->prev = New;
        New->next = New;
        return true;
    }
    //3.双向循环链表不为空链表，将新结点插入到头结点之后
    New->next = head->next; //将新结点的next指针指向头结点的下一个结点
    New->prev = head->next->prev; //将新结点的prev指针指向头结点的下一个结点的前驱结点
    head->next->prev->next = New; //将头结点的下一个结点的前驱结点的next指针指向新结点
    head->next->prev = New; //将头结点的下一个结点的prev指针指向新结点
    head->next = New; //将头结点的next指针指向新结点
    return true;

}

//在双向循环链表尾部插入一个新结点
bool DblCirLList_TailInsert(DoubleCirLList_t *head, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DoubleCirLList_t *New = DblCircLList_CreateNode(data);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    //2.判断双向循环链表是否为空链表
     if (head == head->next) {
        head->next = New;
        New->prev = New;
        New->next = New;
        return true;
    }
    //3.双向循环链表不为空链表，将新节点插入到尾节点之后
    head->next->prev->next = New; //将尾节点的下一个结点的next指针指向新结点
    New->prev = head->next->prev; //将新结点的prev指针指向尾节点的下一个结点
    New->next = head->next; //将新结点的next指针指向头结点
    head->next->prev = New; //将头结点的prev指针指向新结点
    return true;
}

//在双向循环链表指定元素后插入新的元素
bool DblCirLList_MidInsert(DoubleCirLList_t *head, DataType_t dest, DataType_t data) {
    //1.创建一个新的结点，并对新结点进行初始化（数据域+指针域）
    DoubleCirLList_t *New = DblCircLList_CreateNode(data);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
        }
    //2.判断双向循环链表是否为空链表
     if (head == head->next) {
        head->next = New;
        New->prev = New;
        New->next = New;
        return true;
    }
    //3.双向循环链表不为空链表，将新节点插入到指定元素之后
    DoubleCirLList_t *p = head->next;
    while (p->next != head->next && p->Data != dest) {
        p = p->next; //将p指针指向下一个结点
    }
    if(p->next == head->next && p->Data != dest) {
        printf("未找到目标节点，插入失败\n");
        free(New);
        return false;
    }
    New->next = p->next; //将新结点的next指针指向p指针的下一个结点
    New->prev = p; //将新结点的prev指针指向p指针
    p->next->prev = New; //将p指针的下一个结点的prev指针指向新结点
    p->next = New; //将p指针的next指针指向新结点
    return true;
}

//删除双向循环链表的首结点
bool DblCirLList_DeleteHead(DoubleCirLList_t *head) {
    //1.判断双向循环链表是否为空链表
    if (head == head->next) {
        printf("双向循环链表为空，删除失败\n");
        return false;
    }
    //2.双向循环链表不为空链表，删除头结点的下一个结点
    //判断链表中是否只有一个结点，如果只有一个节点，则将头结点的next和prev指针指向自己
    DoubleCirLList_t *p = head->next;
    if (p->next == head->next) {
        head->next = head;
        free(p);
        return true;
    }
    head->next = p->next; //将头结点的next指针指向头结点的下下个结点
    p->next->prev = p->prev; //将头结点的下下个结点的prev指针指向头结点的前一个结点
    p->prev->next = p->next; //将头结点的前一个结点的next指针指向头结点的下下个结点
    p->next = NULL;
    p->prev = NULL;
    free(p); //释放头结点的下一个结点的内存空间
    return true;
}

//删除双向循环链表的尾结点
bool DblCirLList_DeleteTail(DoubleCirLList_t *head) {
    //1.判断双向循环链表是否为空链表
    if (head == head->next) {
        printf("双向循环链表为空，删除失败\n");
        return false;
    }
    //2.双向循环链表不为空链表，删除尾结点
    DoubleCirLList_t *p = head->next->prev; //将p指针指向尾结点
    //判断链表中是否只有一个结点，如果只有一个节点，则将头结点的next和prev指针指向自己
    if (p == head->next) {
        head->next = head;
        free(p);
        return true;
    }
    p->prev->next = head->next; //将尾结点的前一个结点的next指针指向头结点
    head->next->prev = p->prev; //将头结点的prev指针指向尾结点的前一个结点
    p->next = NULL;
    p->prev = NULL;
    free(p); //释放尾结点的内存空间
    return true;
}