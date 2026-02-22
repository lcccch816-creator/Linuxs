/***************************
 * @file InsertSort.c
 * @brief :排序算法
 * @date 2026-02-04
 * @author: lcccch816@gmail.com
 * @version 1.0
 * @copyright Copyright (c) 2026 lcccch816@gmail.com   All rights reserved.
 **************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//插入排序
void InsertSort(int buf[10],int bufsize){
    int i,j;
    int temp;
    //可以假设把数组中的第一个元素作为有序序列的元素，从第二个元素开始，依次插入到有序序列中
    for(i=1;i<bufsize;i++){
        temp = buf[i];//备份当前待插入元素的值
        for(j=i-1;j>=0;j--){
            if(buf[j]>temp){
                buf[j+1] = buf[j];
            }else{
                break;
            }
        }
        buf[j+1] = temp;
    }
}

//冒泡排序
void BubbleSort(int buf[10],int bufsize){
    int temp = 0;//为了临时存储交换值
    //1.循环比较元素，需要比较几轮
    for(int n = 1 ; n < bufsize; ++n)
    {
        //2.每轮需要比较m次
        for(int m = 0 ; m <bufsize-n ;++m)
        {
            if(buf[m]>buf[m+1])
            {
                temp = buf[m];
                buf[m] = buf[m+1];
                buf[m+1]=temp;
            }
        }
    }
}

//选择排序，从序列中找到一个最小值元素，把最小值元素放在整个序列的首部，重复n轮，直到整个序列有序。
void SelectSort (int buf[10],int bufsize)
{
    int min = 0;
    int temp = 0;
    //需要比较n轮，每轮找到序列中的第一个元素是最小值元素。
    for(int n = 0 ; n<bufsize-1 ; ++n)
    {
        min = n;//假设每轮序列中的第一个元素是最小值元素
        //找到序列中的最小值元素的下标
        for(int i =n+1 ; i<bufsize ; i++)
        {
            if(buf[min] > buf[i])
            {
                min = i;
            }
        }
        temp = buf[min];
        buf[min]=buf[n];
        buf[n]=temp;
    }   
}

//计数排序，统计数组A中比每个元素小的元素个数，并把该个数作为数组B的下标。
void CountSort(int A[],int B[],int size)
{
        int cnt = 0;
        for(int n = 0;n< size ;n++)
        {   
            cnt = 0;
            for(int i =0;i<size;i++)
            {
                if(A[n]>A[i])
                {
                    cnt++;
                }
            }
            B[cnt] = A[n];
        }   
}



int main(){
    int buf[10] = {1,3,5,7,9,2,4,6,8,10};
    InsertSort(buf,10);
    for(int i=0;i<10;i++){
        printf("%d",buf[i]);
    }
    return 0;
}