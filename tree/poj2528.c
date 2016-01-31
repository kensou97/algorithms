/*
 线段树入门
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tNode{
    int left,right;
    int color;
    struct tNode* lc;
    struct tNode* rc;
}Node;

int N;

int map[10000001];
int left[10000];
int right[10000];
int point[20000];
int px;
int occur[10001];

Node* root;
int result;

int cmp(const void* x,const void* y){
    return *((int*)x)-*((int*)y);
}

Node* create_node(int left,int right){//递归创建线段树
    Node* n=(Node*)malloc(sizeof(Node));
    n->left=left;
    n->right=right;
    n->color=0;//无色
    n->lc=NULL;
    n->rc=NULL;
    if(left!=right){
        int mid=(left+right)/2;
        n->lc=create_node(left,mid);
        n->rc=create_node(mid+1,right);
    }
    return n;
}

void paint(Node* node,int left,int right,int color){
    if(left>node->right||right<node->left){
        return;
    }
    if(node->left>=left&&node->right<=right){
        node->color=color;
        return;
    }
    Node* lc=node->lc;
    Node* rc=node->rc;
    if(node->color>=0){
        lc->color=node->color;//先将它的颜色传给孩子
        rc->color=node->color;
        node->color=-1;//将它自己改为颜色不确定，需要根据孩子判断
    }
    paint(lc,left,right,color);//递归处理孩子
    paint(rc,left,right,color);
}

void pre_order(Node* node){//前序遍历，如果从根节点能得到结论，就不再遍历它的孩子
    int color=node->color;
    if(color==0){
        return;
    }
    if(color>0){
        if(!occur[color]){//没出现过该颜色
            occur[color]=1;
            result++;
        }
        return;
    }
    pre_order(node->lc);
    pre_order(node->rc);
}

void post_order_free(Node* node){//后序遍历，释放内存
    if(node->lc){
        post_order_free(node->lc);
    }
    if(node->rc){
        post_order_free(node->rc);
    }
    free(node);
}

int main(void){
    int T;
    int i;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        px=0;
        result=0;
        memset(map,-1,sizeof(map));
        for(i=0;i<N;i++){
            scanf("%d %d",left+i,right+i);
            if(map[left[i]]==-1){
                point[px++]=left[i];
                map[left[i]]=1;
            }
            if(map[right[i]]==-1){
                point[px++]=right[i];
                map[right[i]]=1;
            }
        }
        root=create_node(0,px-1);//构造线段树
        
        qsort(point,px,sizeof(int),cmp);
        for(i=0;i<px;i++){
            map[point[i]]=i;//更新映射
        }
        for(i=0;i<N;i++){
            paint(root,map[left[i]],map[right[i]],i+1);
        }
        memset(occur,0,sizeof(occur));
        pre_order(root);
        //post_order_free(root);加上就超时了，想想也是，这也是遍历线段树，而线段树的优势就是不用遍历整棵树，
        //这么遍历一遍让线段树没任何意义了....
        //还好内存没超，不过测试用例再多点的话就要超内存了，用堆内存有时候就是有这样尴尬的时候啊，加上free TLE，不加free MLE，
        //因此能用栈尽量用栈吧。
        printf("%d\n",result);
    }
    return 0;
}