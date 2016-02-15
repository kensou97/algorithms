/**
 其实这题方法应该还是挺多样的，bst写的少，练了练手。
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tNode{
    char species_name[31];
    struct tNode* left;
    struct tNode* right;
    int count;
}Node;

Node* root=NULL;
char str[31];
int total_count=0;

Node* create_node(char* str,Node* parent,int left){
    Node* node=(Node*)malloc(sizeof(Node));
    
    strcpy(node->species_name,str);
    node->left=NULL;
    node->right=NULL;
    node->count=1;
    
    if(parent){
        if(left){
            parent->left=node;
        }else{
            parent->right=node;
        }
    }
    
    return node;
}

/**
 *search，如果search不到，insert
 */
void search_insert(Node* node){
    int result=strcmp(str,node->species_name);
    if(result==0){
        node->count++;
    }
    if(result>0){
        if(node->right){
            search_insert(node->right);
        }else{
            create_node(str,node,0);
        }
    }
    if(result<0){
        if(node->left){
            search_insert(node->left);
        }else{
            create_node(str,node,1);
        }
    }
}

void inorder(Node* node){//按顺序输出结果嘛，当然是中序
    if(!node){
        return;
    }
    inorder(node->left);
    printf("%s %.4f\n",node->species_name,100.0*node->count/total_count);
    inorder(node->right);
    
    free(node);
}

int main(void){
    while(gets(str)!=NULL){
        if(root){
            search_insert(root);
        }else{
            root=create_node(str,NULL,0);
        }
        total_count++;		
    }
    
    inorder(root);
    
    return 0;
}