


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType_t;

typedef struct SequenceStack {
    DataType_t  *bottom;    //栈底指针
    int          top;       //记录栈顶元素的下标
    unsigned int size;     //栈的当前容量，以元素为单位
} SeqStack_t;

SeqStack_t *SeqStack_Create(unsigned int size) {
    //1.利用calloc函数给顺序栈申请内存空间
    SeqStack_t *stack = (SeqStack_t *)calloc(1, sizeof(SeqStack_t));
    if (NULL == stack) {
        perror("calloc failed!\n");
        exit(-1); //程序异常终止
    }
    //2.利用calloc给栈底指针申请堆内存，也就是给所有元素申请堆内存
    stack->bottom = (DataType_t *)calloc(size, sizeof(DataType_t));
    if (NULL == stack->bottom) {
        perror("calloc failed!\n");
        free(stack);
        exit(-1);
    }
    stack->top = -1; //栈为空栈，栈顶指针指向-1，栈顶元素的下标初值为-1.
    stack->size = size;//对顺序栈的容量进行初始化
    return stack;
}

//判断顺序栈是否已满
bool SeqStack_IsFull(SeqStack_t *stack) {
    return (stack->top +1 == stack->size) ? true : false;
}

//向顺序表的尾部加入元素
bool SeqStack_Push(SeqStack_t *stack, DataType_t data) {
    //1.判断顺序栈是否已满
    if (SeqStack_IsFull(stack)) {
        printf("SeqStack is full!\n");
        return false;
    }
    //2。如果顺序栈有空闲空间，则把新元素添加到顺序栈的栈顶
    stack->bottom[++stack->top] = data;
    return true;
}

//判断顺序栈是否为空
bool SeqStack_IsEmpty(SeqStack_t *stack) {
    return (stack->top == -1) ? true : false;
}

//从顺序栈中弹出栈顶元素
DataType_t SeqStack_Pop(SeqStack_t *stack) {
    DataType_t data = 0;
    //1.判断顺序栈是否为空
    if (SeqStack_IsEmpty(stack)) {
        printf("SeqStack is empty!\n");
        return -1;
    }
    //2.如果顺序栈不为空，则将栈顶元素弹出
    data = stack->bottom[stack->top--];
    return data;
}

//遍历顺序栈并打印栈中的所有元素
void SeqStack_Print(SeqStack_t *stack) {
    if (SeqStack_IsEmpty(stack)) {
        printf("SeqStack is empty, cannot print!\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->bottom[i]);
    }
    printf("\n");
}


//将十进制转换为十六进制
void SeqStack_Dec2Hex(SeqStack_t *stack,unsigned int dec) {
    int reminder;//余数
    do  {
        reminder = dec % 16;
        //分析余数的范围，0~9直接入栈，10~15需要转换为A~F再入栈
        if (reminder < 10) {
            SeqStack_Push(stack, reminder + '0');//将数字转换为字符再入栈
        } else {
            SeqStack_Push(stack, reminder - 10 + 'A');//将数字转换为字符再入栈
        }
        dec /= 16;//更新被除数
    }while(dec != 0);
    printf("0x");
    //将栈中的元素依次弹出，打印出来就是十六进制的表示
    while (!SeqStack_IsEmpty(stack)) {
        
        printf("%c", SeqStack_Pop(stack));//将数字转换为字符再出栈
}
    printf("\n");
}

bool SeqStack_IsStringVaild(SeqStack_t *stack,const char *str) {
    char *p = str;//备份地址，防止地址丢失

    //1.循环遍历字符串，寻找“（”
    while (*p != '\0') {
        //判断当前地址下的字符是否为“（”
        if (*p == '(') {
            //将“（”入栈
            SeqStack_Push(stack, *p);
        } else if (*p == ')') {
            //遇到“）”，则需要将栈顶的“（”弹出
            if (SeqStack_IsEmpty(stack)) {
                //栈为空，说明没有与之匹配的“（”，字符串不合法
                return false;
            }
               //栈不为空，则将栈顶的“（”弹出
                SeqStack_Pop(stack);
        }
        p++;//指向下一个字符
    }
    //2.遍历结束后，判断栈是否为空
    if (!SeqStack_IsEmpty(stack)) {
        //栈不为空，说明有未匹配的“（”，字符串不合法
        return false;
    } 
        //栈为空，说明所有的“（”都找到了匹配的“）”，字符串合法
        return true;
}

int main() {
    SeqStack_t *stack = SeqStack_Create(100);
    SeqStack_Dec2Hex(stack, 255);
    return 0;
}