/**
 模拟实现一下浏览器的后退和前进功能，题目中也有提示，用两个栈就可以了，比较简单。
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int top;//栈顶
    char* s[100];
} Stack;

/**
 *初始化
 */
Stack* create_stack(){
    Stack* stack=(Stack*)(malloc(sizeof(Stack)));
    stack->top=-1;
    memset(stack->s,0,sizeof(stack->s));
    return stack;
}

void push(Stack* stack,char* str){
    stack->s[++stack->top]=str;
}

char* pop(Stack* stack){
    int top=stack->top;
    if(top==-1){
        return NULL;
    }
    stack->top--;
    return stack->s[top];
}

int isEmpty(Stack* stack){
    return stack->top==-1;
}

int main(void){
    Stack* forward=create_stack();
    Stack* backward=create_stack();
    
    char* home_page="http://www.acm.org/";
    char* current_page=home_page;
    char command[8];
    while(1){
        scanf("%s",command);
        if(command[0]=='Q'){//QUIT
            break;
        }else if(command[0]=='V'){//VISIT
            push(backward,current_page);
            
            char *str=(char*)malloc(sizeof(char)*71);
            scanf("%s",str);
            current_page=str;
            
            forward->top=-1;
            printf("%s\n",str);
        }else if(command[0]=='B'){//BACK
            if(isEmpty(backward)){
                printf("Ignored\n");
            }else{
                push(forward,current_page);
                current_page=pop(backward);
                printf("%s\n",current_page);
            }
        }else{//FORWARD
            if(isEmpty(forward)){
                printf("Ignored\n");
            }else{
                push(backward,current_page);
                current_page=pop(forward);
                printf("%s\n",current_page);
            }
        }
    }
    
    int i;
    for(i=0;i<100;i++){//释放下堆内存.....
        char* tmp=backward->s[i];
        if(tmp&&tmp!=home_page){
            free(backward->s[i]);
        }
    }
    free(forward);
    free(backward);
    return 0;
}