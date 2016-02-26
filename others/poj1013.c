/**
 1.even的情况所有参与的字母标记0
 2.up的情况左边非0的字母标记2，右边非0的字母标记1，未参与的子母标0，发生1变为2或者2变为1的情况均直接变为0
 3.down的情况可以对称2
 **/
#include <stdio.h>
#include <string.h>

int coin[12];
char left[7];
char right[7];
char state[5];

int find(int ci,char* str){
    char c=(char)('A'+ci);
    int i=0;
    while((str[i])&&(c!=str[i])){
        i++;
    }
    if(str[i]){
        return 1;
    }
    return 0;
}

void change_state(int up){
    int i,j;
    for(i=0;i<12;i++){
        if(find(i,left)||find(i,right)){
            continue;
        }
        coin[i]=0;
    }
    
    if(up){
        i=0;
        while(left[i]){
            j=(int)(left[i]-'A');
            if(coin[j]!=0){
                coin[j]=(coin[j]==1?0:2);
            }
            i++;
        }
        i=0;
        while(right[i]){
            j=(int)(right[i]-'A');
            if(coin[j]!=0){
                coin[j]=(coin[j]==2?0:1);
            }
            i++;
        }
    }else{
        i=0;
        while(left[i]){
            j=(int)(left[i]-'A');
            if(coin[j]!=0){
                coin[j]=(coin[j]==2?0:1);
            }
            i++;
        }
        i=0;
        while(right[i]){
            j=(int)(right[i]-'A');
            if(coin[j]!=0){
                coin[j]=(coin[j]==1?0:2);
            }
            i++;
        }
    }
}

int main(void){
    int i,j;
    
    int N;
    scanf("%d",&N);
    while(N--){
        memset(coin,-1,sizeof(coin));
        i=3;
        while(i--){
            scanf("%s %s %s",left,right,state);
            if(state[0]=='e'){
                j=0;
                while(left[j]){
                    coin[(int)(left[j]-'A')]=0;
                    j++;
                }
                j=0;
                while(right[j]){
                    coin[(int)(right[j]-'A')]=0;
                    j++;
                }
            }else if(state[0]=='u'){
                change_state(1);
            }else{
                change_state(0);
            }
        }
        for(i=0;i<12;i++){
            if(coin[i]){
                if(coin[i]==1){
                    printf("%c is the counterfeit coin and it is light.\n",(char)('A'+i));
                }else{
                    printf("%c is the counterfeit coin and it is heavy.\n",(char)('A'+i));
                }
            }
        }	
    }
    return 0;
}