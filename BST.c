/***********************************************************
 * 
 * 
 * 设计BST二叉查找树的接口，为了方便对二叉树进行节点的增删改查操作，所以采用双向不循环链表实现，
 * 每个节点内部都需要有两个指针，分别指向该节点的左子树（lchild）和右子树（rchild），同时还需要一个指针指向该节点的父节点（parent）。
 * 
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//指的是BST树中的结点有效键值类型，用户可以根据需要进行修改
 typedef int KeyType_t;
//构造BST节点，树中所有节点的键值类型应该是相同的
 typedef struct BSTree {
     KeyType_t              Key; //结点的键值域 
     struct BSTree         *lchild; //指向左子树的指针域
     struct BSTree         *rchild; //指向右子树的指针域
 } BST_t;


//创建一个带根节点的BST树，对BST树进行初始化
 BST_t* CreateBSTree(KeyType_t key) {
     //1.给根节点申请内存空间
     BST_t *root = (BST_t *)calloc(1,sizeof(BST_t));
     //2.判断根节点是否创建成功
     if (NULL == root) {
         perror("calloc failed!\n");
         return NULL;
     }
     //3.将根节点的键值域赋值，将根节点的左右子树指针域置为NULL
     root->Key = key;
     root->lchild = NULL;
     root->rchild = NULL;
     return root;
 }

 //创建一个新的结点，并对新结点进行初始化（键值域+指针域）
BST_t * CreateBSTNode(KeyType_t key) {
     //1.给新结点申请内存空间
     BST_t *New= (BST_t *)calloc(1,sizeof(BST_t));
     //2.判断新结点是否创建成功
     if (NULL == New) {
         perror("calloc failed!\n");
         return NULL;
        }
        //3.将新结点的键值域赋值 将新结点的指针域置为NULL,也就是将新结点的指针域和键值域进行初始化
        New->Key = key;
        New->lchild = NULL;
        New->rchild = NULL;
        return New;
 }

//在BST树中插入一个新结点 规则：小于等于当前节点的键值插入到左子树，大于当前节点的键值插入到右子树
bool BSTree_InsertNode(BST_t *root, KeyType_t key) {

    //为了避免根节点地址丢失，需要使用对根节点地址进行备份
    BST_t *p = root;

    //1.创建一个新的结点，并对新结点进行初始化（键值域+指针域）
    BST_t *New = CreateBSTNode(key);
    if (NULL == New) {
         perror("calloc failed!\n");
         return false ;
    }
    //2.判断当前根节点是否为空，有两种情况（空树or非空树）
    if (NULL == root) {
        root = New;//此时BST树为空树，将新结点作为根节点
        return true;
    }
    else {
        //3.当前BST树非空，需要找到新结点应该插入的位置
        while(p)   {
            //新节点的键值和根节点的键值进行比较，如果相等则终止函数
            if (key == p->Key) {
                printf("BSTree already has the key %d, insert failed!\n", key);
                free(New);
                return false;
            }
            else{
                if(New->Key < p->Key) {
                    if(p->lchild == NULL) {
                        p->lchild = New; //将新结点插入到左子树
                        break;
                    }
                    p = p->lchild; //继续向左子树查找插入位置
            }
            else {
                if(p->rchild == NULL) {
                    p->rchild = New; //将新结点插入到右子树
                    break;
                    }
                p = p->rchild; //继续向右子树查找插入位置  
                }
            }
        }
    }
    return true;
}


//前序遍历  根左右   体现递归思想
bool BSTree_PreOrder(BST_t *root) {
    if (NULL == root) {
        return false;
    }
    printf("key = %d ", root->Key);//输出根节点的键值
    BSTree_PreOrder(root->lchild);
    BSTree_PreOrder(root->rchild);
    return true;
}

 //中序遍历  左根右
bool BSTree_InOrder(BST_t *root) {
    if (NULL == root) {
        return false;
    }
    BSTree_InOrder(root->lchild);
    printf("key = %d ", root->Key);//输出根节点的键值
    BSTree_InOrder(root->rchild);
    return true;
}

//后序遍历  左右根
bool BSTree_PostOrder(BST_t *root) {
    if (NULL == root) {
        return false;
    }
    BSTree_PostOrder(root->lchild);
    BSTree_PostOrder(root->rchild);
    printf("key = %d ", root->Key);//输出根节点的键值
    return true;
}

//计算一颗二叉树的所有节点的数量
int BSTree_Count(BST_t *root) {
    if (NULL == root) {
        return 0;
    }
    return BSTree_Count(root->lchild) + BSTree_Count(root->rchild) + 1;
}


//用二叉链计算一颗二叉树的所有叶子节点的数量
int BSTree_CountLeaf(BST_t *root) {
    if (NULL == root) {
        return 0;
    }
    if (NULL == root->lchild && NULL == root->rchild) {
        return 1;
    }
    return BSTree_CountLeaf(root->lchild) + BSTree_CountLeaf(root->rchild);
}

//计算二叉树的深度
int BSTree_Depth(BST_t *root) {
    if(NULL == root) {
        return 0;
    }
    int left = BSTree_Depth(root->lchild);
    int right = BSTree_Depth(root->rchild);
    return left > right ? left + 1 : right + 1;
}

