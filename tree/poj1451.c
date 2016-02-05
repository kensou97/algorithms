/**
 构造好Trie树之后，按照Trie宽搜一步一步找，每次将权值最大的输出就可以了。
 不过感觉好繁啊，另外因为用的是C，所以啥都要自己从头写，几个内存的地方调了挺长时间的，
 大部分都是因为free了空指针导致的段错误。
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNode{
    char* str;
    int probability;//权值
    struct tNode* next[26];//Trie树中的孩子
    struct tNode* qnext;//队列中的下一个元素
    int depth;//宽搜的深度
}Node;

Node* root;//Trie根节点
Node* head;//队头
Node* tail;//队尾
Node* max_node;//权值最大的节点

/**
 *创建一个节点
 */
Node* create_node(char value,int probability,Node* parent){
    Node* node=(Node*)malloc(sizeof(Node));
    
    node->str=NULL;
    node->probability=probability;
    memset(node->next,0,sizeof(node->next));
    node->qnext=NULL;
    
    if(parent!=NULL){
        int i=(int)(value-'a');
        Node** next=parent->next;
        next[i]=node;
    }
    return node;
}

/**
 动态创建Trie，如果节点已存在，将权值加上去；如果不存在，创建节点。
 */
Node* search_or_insert(char* str,int probability){
    int j=0;
    char c;
    Node* current_node=root;
    while((c=str[j])!='\0'){
        int i=(int)(c-'a');
        if(current_node->next[i]==NULL){
            current_node=create_node(c,probability,current_node);
            char *tmp=(char*)malloc(j+2);
            strncpy(tmp,str,j+1);
            tmp[j+1]='\0';
            current_node->str=tmp;
        }else{
            current_node=current_node->next[i];
            current_node->probability+=probability;
        }
        j++;
    }
    return current_node;
}

/**
 *单个节点free一下
 */
void free_node(Node* node){
    if(node->str){
        free(node->str);
    }
    if(node){
        free(node);
    }
}

/**
 *free整个trie树
 */
void free_tree(Node* node){
    int i;
    for(i=0;i<26;i++){
        if(node->next[i]){
            free_tree(node->next[i]);
        }
    }
    
    free_node(node);
}

/**
 *入队
 */
void enqueue(Node* node){
    node->qnext=NULL;//这句挺关键，加上它才能用（!head）判断队列是不是空，否则上次的结果会对判断结果有干扰，找了好久的....
    tail->qnext=node;
    tail=node;
}

/**
 *出队
 */
void dequeue(){
    head=head->qnext;
}

int main(void){
    int scenarios;
    int w;
    int probability;
    char str[101];
    int m;
    char digit[101];
    
    char* digit_alpha[]={"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    
    scanf("%d",&scenarios);
    
    int k;
    for(k=1;k<=scenarios;k++){
        printf("Scenario #%d:\n",k);
        
        root=create_node('a',0,NULL);
        root->depth=0;
        
        scanf("%d",&w);
        while(w--){//根据单词及权值创建Trie树
            scanf("%s %d",str,&probability);
            search_or_insert(str,probability);
        }
        
        scanf("%d",&m);
        while(m--){
            scanf("%s",digit);//435561
            
            head=root;
            tail=root;
            
            int i=0;
            while(digit[i]!='1'){//4
                max_node=NULL;
                char* alphas=digit_alpha[(int)(digit[i]-'2')];
                
                while(head&&(head->depth==i)){
                    int j=0;
                    while(alphas[j]){//将每个按键对应的后继节点入队，深度depth是当前深度加1
                        Node* tmp_node=head->next[(int)(alphas[j]-'a')];
                        if(tmp_node){
                            tmp_node->depth=i+1;
                            if((max_node==NULL)||(max_node->probability<tmp_node->probability)){//顺便记下最大的
                                max_node=tmp_node;
                            }
                            enqueue(tmp_node);
                        }
                        j++;
                    }
                    dequeue();
                }
                i++;
                
                if(!head){//队列空了，说明没有匹配
                    printf("MANUALLY\n");
                }else{
                    printf("%s\n",max_node->str);
                }
            }
            printf("\n");
        }
        
        free_tree(root);
        printf("\n");
    }
    return 0;
}



