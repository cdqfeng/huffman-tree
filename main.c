#include <stdio.h>


/****************************************
 *
 * 构造哈夫曼树
 * 
 ****************************************/

typedef struct
{
    int weight;
    int lchild, rchild, parent;
} Node;

// 结点个数
#define n 8
// 哈夫曼树结点数组长度,这里留出第0个元素
#define m 2*n


// 寻找结点中的最小值和次小值
void select(Node tree[], int *p1, int *p2) {
    // 初设最小值
    int min = 0;
    for (int i = 0; i < m; i++) {
        if (tree[i].parent == 0 && tree[i].weight != 0) {   // 不能为已经合并值，不能为权值为0的值
            min = tree[i].weight;   
            *p1 = i;
            break;
        }
    }
    // 找到最小值
    for (int i = 1; i < m; i++) {
        if (tree[i].weight != 0 && tree[i].weight < min && tree[i].parent == 0) {
            min = tree[i].weight;
            * p1 = i;
        }
    }

    // 初设次小值
    for (int i = 0; i < m; i++) {
        if (i != *p1 && tree[i].parent == 0 && tree[i].weight != 0) {   // 此初始值不能为最小值，不能为已经合并值，不能为权值为0的值
            min = tree[i].weight;   
            *p2 = i;
            break;
        }
    }
    // 找到次小值
    for (int i = 1; i < m; i++) {
        if (tree[i].weight != 0 && tree[i].weight <= min && i != *p1 && tree[i].parent == 0) {
            min = tree[i].weight;
            * p2 = i;
        }
    }
}


int main() {
    int leaf[] = {5, 10, 10, 14, 13, 5, 20, 23};
    Node tree[m];
    
    // 初始化数组
    for(int i = 0; i < m; i++)
    {
        tree[i].weight = 0;
        tree[i].lchild = 0;tree[i].rchild = 0;tree[i].parent = 0;   
    }


    // 读入n个权值
    for(int i = 0; i < n; i++)
    {
        tree[i+1].weight = leaf[i];
    }

    
    int p1 = 0, p2 = 0;

    // 合并结点
    for(int i = n+1; i < m; i++)
    {
        select(tree, &p1, &p2);
        printf("最小值=%d, 次小值=%d\n", p1, p2);


        // 新结点
        tree[i].weight = tree[p1].weight + tree[p2].weight;
        tree[i].lchild = p1; tree[i].rchild = p2;
        
        tree[p1].parent = i; tree[p2].parent = i;
    }

    printf("\n");
    printf("构造完成的哈夫曼树结点如下，(数组第一个元素不算结点)\n\n[");
    for(int i = 0; i < m; i++)
    {
        printf("%d,", tree[i].weight);
    }
    printf("]\n\n");
    
    

    return 0;
}