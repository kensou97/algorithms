/**
 用队列从最后的状态往前推就可以了。
 用头部删除，尾部插入的链表的话，最后需要倒序输出，
 因此就用了头部插入，尾部删除的链表
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct tCard{
    int value;
    struct tCard* pre;
    struct tCard* next;
}Card;

int N;
Card* head;
Card* tail;

/*
 *头部插入
 */
void enqueue(Card* c){
    if(head){
        c->next=head;
        head->pre=c;
        head=c;
    }else{
        head=c;
        tail=c;
    }
}

/*
 尾部删除
 */
Card* dequeue(){
    Card* last=tail;
    tail=last->pre;
    if(last->pre){
        last->pre->next=NULL;
    }
    last->pre=NULL;
    return last;
}

Card* create_card(int value){
    Card* c=(Card*)malloc(sizeof(Card));
    c->value=value;
    c->next=NULL;
    c->pre=NULL;
    return c;
}

void print_result(){
    Card* c=head;
    Card* tmp;
    while(c){
        printf("%d ",c->value);
        tmp=c;
        c=c->next;
        free(tmp);
    }
    printf("\n");
}

int main(void){
    int T;
    int i,j;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        head=create_card(N);
        tail=head;
        for(i=N-1;i>=1;i--){
            enqueue(create_card(i));
            j=i;
            while(j--){
                enqueue(dequeue());
            }
        }
        print_result();
    }
    return 0;
}