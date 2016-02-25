/**
哈夫曼编码，因为大写字母一共才26个，加上下划线一共27个字符，所以节点数至多是27个，用不用堆都无所谓了。
第一次写指针数组的cmp函数啊，还是有要注意的地方...
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tNode{
    int count;
    struct tNode* l;
    struct tNode* r;
}Node;

char str[100000];
Node* node[27];
int nc;
int hz[27];
int entropy;

int cmp(const void* x,const void* y){
    return (*(Node**)y)->count-(*(Node**)x)->count;//....
}

Node* create_node(int count,Node* l,Node* r){
    Node* n=(Node*)malloc(sizeof(Node));
    n->count=count;
    n->l=l;
    n->r=r;
    return n;
}

/**
 计算编码长度，做个遍历就好了
 */
void post_order(Node* n,int level){//level:节点所在的层
    Node* l=n->l;
    Node* r=n->r;
    if(l){
        post_order(l,level+1);
    }
    if(r){
        post_order(r,level+1);
    }
    if(!l&&!r){//叶子
        entropy+=(level*(n->count));//出现次数*所在层数
    }
    free(n);
}

void huffman(void){
    int i=nc-1;
    while(i--){
        qsort(node,nc,sizeof(Node*),cmp);
        Node* n=create_node(node[nc-1]->count+node[nc-2]->count,node[nc-1],node[nc-2]);//还是那个过程，选俩最小的，计算和
        nc-=2;//删掉俩最小的
        node[nc++]=n;//把他们的和插进去
    }
    post_order(node[0],0);
}

int main(void){
    int i;
    int len;
    char c;
    while(1){
        scanf("%s",str);
        if(strcmp(str,"END")==0){
            break;
        }
        
        memset(hz,0,sizeof(hz));
        memset(node,0,sizeof(Node));
        nc=0;
        entropy=0;
        
        i=0;
        while((c=str[i])!='\0'){
            if(c=='_'){
                hz[26]++;
            }else{
                hz[(int)(c-'A')]++;
            }
            i++;
        }
        len=i;
        
        for(i=0;i<27;i++){
            if(hz[i]){
                node[nc++]=create_node(hz[i],NULL,NULL);
            }
        }
        
        if(nc==1){//只有一个节点，特殊处理
            printf("%d %d 8.0\n",8*len,len);
            continue;
        }
        huffman();
        len=8*len;
        printf("%d %d %.1f\n",len,entropy,(double)(len)/(double)(entropy));
    }
    return 0;
}