/**
 题目意思是给一堆木棍，每个木棍的两个端点都涂上颜色，问能否将这堆木棍彼此相连组成一根大木棍，
 相连的条件是：如果两个小木棍有颜色相同的端点，那么可以通过颜色相同的端点将他们连接起来。比如题目给的例子：
 
 blue red
 red violet
 cyan blue
 blue magenta
 magenta cyan
 可以这样连起来（blue magenta）（magenta cyan）（cyan blue） （blue red）（red violet）。
 
 不难发现，在最终组成的大木棍中，除了首尾两个端点的颜色的出现次数可能是奇数外，其他任意一种颜色出现的次数必定是偶数，因为中间的每种颜色都是成对出现的。
 如果用图表示，每种颜色是一个顶点，那么至多只有两个点的度为奇数。当然只有这一个条件还是不够的，比如下边这个例子：

 blue red
 red blue
 cyan black
 black cyan
 虽然所有颜色的度都是偶数，但是还是不能满足要求，用图表述这种情况的话就是图不是连通的。因此还有一个条件是图要连通。
 
 是不是很像欧拉通路啊？其实就是欧拉通路。直接上定理了，无向图G有欧拉通路的充分必要条件为：G连通，G中只有两个奇度顶点(它们分别是欧拉通路的两个端点)。
 既然得到结论了，是不是直接邻接矩阵搞起啊？其实没必要，邻接矩阵的重点是保存了边，而如果只是判断是不是欧拉通路的话，完全没必要保存边的信息，
 因为我们只关心两点：顶点的度，图是否连通。判断图是否连通可以用集合来做，每个集合代表一个连通子图（即集合中的任意两个顶点都是连通的），
 初始时每个顶点构成一个集合。然后每读入一个边，就可以进行如下操作：
 
 首先更新该边两个顶点的度，然后将两个顶点所在集合合并，然后该边就可以舍弃了（不需要存下来），继续读下一条边。读完所有的边后，就可以检查条件了，
 统计一下奇数度顶点的个数，再就是如果图是连通的，那么最后所有的顶点都会属于同一个集合。
 
 集合可以用并查集来做，主要操作有两个，判断元素所属的集合find，合并集合union 。并查集大体分链式和树型两种实现，简单说下两种实现优缺点，
 链式find操作快，复杂度O（1），union的时间和链的长度有关；树型find操作的时间和树的高度有关，union操作是O（1） 。我的实现用的是树型的。
 
 另外本题顶点并不是0，1，2.....这种数字型，而是字符串型的，因为数据量较大，所以需要比较高效的字符串查找。可以用hash，可以用Trie树，我用的是动态创建的Trie树。
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tNode{
    struct tNode* next[26];//trie树中该节点的孩子
    int degree;
    struct tNode* representation_element;//集合的代表元
}Node;

Node* root;//trie树根
Node* union_node;//如果图是连通的，所有的节点应该指向同一个代表元（也就是属于一个集合），保存该代表元
int odd_count;//奇数度节点的个数

Node* create_node(char value,Node* parent){
    Node* node=(Node*)malloc(sizeof(Node));
    
    memset(node->next,0,sizeof(node->next));
    node->degree=-1;
    node->representation_element=node;//初始时一个节点构成一个集合，集合的代表元当然就是它自己啦
    
    if(parent!=NULL){
        int i=(int)(value-'a');
        Node** next=parent->next;
        if(next[i]==NULL){
            next[i]=node;
        }
    }
    return node;
}

/**
 *查找，找不到的话动态创建Trie树节点
 */
Node* search_or_insert(char* str){
    int j=0;
    char c;
    Node* current_node=root;
    while((c=str[j++])!='\0'){
        int i=(int)(c-'a');
        if(current_node->next[i]==NULL){
            current_node=create_node(c,current_node);
        }else{
            current_node=current_node->next[i];
        }
    }
    if(current_node->degree==-1){
        current_node->degree=1;
    }else{
        current_node->degree++;
    }
    return current_node;
}

/**
 *集合的合并
 */
void union_set(Node* first_node,Node* second_node){
    while(first_node->representation_element!=first_node){//找到各自的代表元，如果一个节点的代表元等于该节点本身，它就是代表元啦
        first_node=first_node->representation_element;
    }
    while(second_node->representation_element!=second_node){
        second_node=second_node->representation_element;
    }
    if(first_node==second_node){//本就是一个集合，直接返回吧
        return;
    }
    
    second_node->representation_element=first_node;//将second_node的代表元修改为first_node
}

void go_get_result(Node* node){//前序遍历啦
    if(node==NULL){
        return;
    }
    
    int degree;
    if(node!=root&&(degree=node->degree)!=-1){
        if((degree&1)==1){
            odd_count++;
            if(odd_count==3){//根据欧拉通路的条件.....奇数度的点太多了
                printf("Impossible\n");
                exit(0);
            }
        }
        
        if(union_node==NULL){
            union_node=node->representation_element;
        }else{
            Node * current_node=node;
            while(current_node->representation_element!=current_node){
                current_node=current_node->representation_element;
            }
            if(union_node!=current_node){//不连通
                printf("Impossible\n");
                exit(0);
            }
        }
    }
    Node** next=node->next;
    int i=0;
    for(;i<26;i++){
        go_get_result(next[i]);
    }
    //	free(node);
}

int main(void){
    char first[11];
    char second[11];
    
    root=create_node('a',NULL);
    union_node=NULL;
    odd_count=0;
    
    while(scanf("%s %s",first,second)!=EOF){
        Node* first_node=search_or_insert(first);
        Node* second_node=search_or_insert(second);
        union_set(first_node,second_node);//根据棒子合并集合
    }
    
    go_get_result(root);
    printf("Possible\n");
    //free释放下内存..
    return 0;
}