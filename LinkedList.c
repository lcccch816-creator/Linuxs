/**
 * @filename:LinkedList.c
 * @brief：单向链表实现基本操作
 * @author：Lcccch_816@163.com
 * @date: 2026-01-25
 * @version: V1.0 
 * @note：NULL
 * CopyRight (c) 2026-2027, Lcccch_816@163.com All Rights Reserved
 * */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//指的是单向链表中的结点有效数据类型，用户可以根据需要进行修改
 typedef int DataType_t;
//构造链表节点，链表中所有节点的数据类型应该是相同的
 typedef struct LinkedList { 
     DataType_t         Data; //结点的数据域
     struct LinkedList *next; //结点的指针域
 }LList_t;

 //链表初始化,也就是创建一个空链表，空链表应该有一个头节点。头节点是链表中第一个节点，头节点不存储有效数据，头节点指向链表中第一个有效数据节点
 LList_t * LList_Create(void) {
     //1.创建一个头结点，给头结点申请内存空间
     LList_t *head = (LList_t *)calloc(1,sizeof(LList_t));
     //2.判断头结点是否创建成功
     if (NULL == head) {
         perror("calloc failed!\n");
         return NULL;
     }
     //3.将头结点的指针域置为NULL,头结点不存储有效的内容！！！
     head->next = NULL;
     //4.返回头结点
     return head;
 }

//创建一个新节点，新节点应该包含一个有效数据和一个指向下一个节点的指针域。
 LList_t * LList_NewNode(DataType_t data) {
     //1.给新节点申请内存空间
     LList_t *New = (LList_t *)calloc(1,sizeof(LList_t));
     //2.判断新节点是否创建成功
     if (NULL == New) {
         perror("calloc failed!\n");
         return NULL;
     }
     //3.将新节点的数据域赋值 将新节点的指针域置为NULL
     New->Data = data;
     New->next = NULL;
     return New;
     }

     //在头结点处插入一个新结点
  bool LList_HeadInsert(LList_t *head, DataType_t data) {
     //1.创建一个新节点
     LList_t *New = LList_NewNode(data);
     //2.判断新节点是否创建成功
     if (NULL == New) {
         perror("Create LList_NewNode failed!\n");
         return false;
     }
     //3.判断链表是否为空，如果为空，直接插入就可以
     if (NULL == head->next) {
          head ->next = New;
          return true;
     }
     New->next = head->next;
     head->next = New;
     return true;
   }

   //在链表尾部插入一个新结点
   bool LList_TailInsert(LList_t *head, DataType_t data)
   {
     //1.创建一个新节点
     LList_t *New = LList_NewNode(data);
     //2.判断新节点是否创建成功
     if (NULL == New) {
         perror("Create LList_NewNode failed!\n");
         return false;
     }
     //3.判断链表是否为空，如果为空，直接插入就可以
     if (NULL == head->next) {
          head ->next = New;
          return true;
     }
     //3.找到链表的尾节点
     LList_t *p = head;
     while(p->next)
     {
        p = p->next;
     } 
     //4.将新节点插入到尾节点的后面
     p->next = New;
     New->next = NULL;
     return true;
   }
   bool LList_DestInsert(LList_t *head, DataType_t data, DataType_t dest)
   {
     //1.创建一个新节点
     LList_t *New = LList_NewNode(data);
     //2.判断新节点是否创建成功
     if (NULL == New) {
         perror("Create LList_NewNode failed!\n");
         return false;
     }
      //3.判断链表是否为空，如果为空，直接插入就可以
     if (NULL == head->next) {
          head ->next = New;
          return true;
     }
     //4.遍历列表，找到目标节点
        LList_t *p = head->next;
        while(p != NULL && dest != p->Data)
        {
           p = p->next;
        }
        if(NULL == p)
        {
           printf("未找到目标节点，插入失败\n");
           free(New);
           return false;
        }
        //5.将新节点插入到目标节点的后面
        New->next = p->next;
        p->next = New;
        return true;
   }
//删除头结点的下一个节点
bool LList_HeadDel(LList_t *head)
   {
      if(NULL == head->next)
      {
         printf("链表为空，无法删除\n");
         return false;
      }
      LList_t *p = head;
      head->next = p->next->next;
      p ->next->next = NULL;
      free(p->next);
      return true;
   }

   void LList_Print(LList_t *head) {
    //对链表的头文件的地址进行备份
     LList_t *p = head;
     while(p ->next)
     {
        //把当前结点的直接后继作为新的当前结点
         p = p->next;
         //输出当前结点的数据域
        printf("%d ",p->Data);
     }
   }

   //删除单链表中的最小值结点
   bool LList_DelMin(LList_t *head)
    {
        if(NULL == head->next)
        {
            printf("链表为空，无法删除\n");
            return false;
        }
        LList_t *p = head->next;//记录当前结点的地址
        LList_t *min= p;//记录最小值的地址
        LList_t *minPre = head;//记录最小值结点的前驱结点
        LList_t *p_prev= head;//记录当前结点的前驱结点
        //1.遍历链表，找到最小值结点
        while(p->next)
        {
            //把当前结点的数据域和最小结点的数据域进行比较 
            if(p->Data < min->Data)
            {
                min = p;
                minPre = p_prev;
            }
            p_prev = p;
            p = p->next;
        }
        //2.删除最小值结点，前提是让最小值结点的直接前驱指向最小值结点的直接后继
        minPre->next = min->next;
        min->next = NULL;
        free(min);
        return true;

}