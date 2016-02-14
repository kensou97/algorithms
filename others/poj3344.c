/**
 模拟
 **/
#include <stdio.h>

char ch[8][9];
char command[5];
int direction;
int step;
char dc[6];
int r;
int c;
int blank[8];

int directions[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
char symbol[]="^>v<";

void count_blank(void){
    int count=0;
    int i=r;
    int j=c;
    while(i>=0&&i<8&&j>=0&&j<8){
        i+=directions[direction][0];
        j+=directions[direction][1];
        if(ch[i][j]=='.'){
            count++;
            continue;
        }
        if(direction==0||direction==2){
            blank[i]=count;
        }else{
            blank[j]=count;
        }
    }
}

void moveOn(void){
    count_blank();
    int i;
    int ni;
    int offset;
    if(direction==0){
        for(i=0;i<r;i++){
            if(ch[i][c]=='.'){
                continue;
            }
            offset=step-blank[i];
            if(offset<=0){
                continue;
            }
            ni=i-offset;
            if(ni<0){
                continue;
            }
            ch[ni][c]=ch[i][c];
        }
        ni=r-step;
        ni=ni<0?0:ni;
        for(i=r;i>ni;i--){
            ch[i][c]='.';
        }
        ch[r][c]='.';
        ch[ni][c]='^';
        r=ni;
        return;
    }
    if(direction==2){
        for(i=7;i>r;i--){
            if(ch[i][c]=='.'){
                continue;
            }
            offset=step-blank[i];
            if(offset<=0){
                continue;
            }
            ni=i+offset;
            if(ni>7){
                continue;
            }
            ch[ni][c]=ch[i][c];
        }
        ni=r+step;
        ni=ni>7?7:ni;
        for(i=r;i<ni;i++){
            ch[i][c]='.';
        }
        ch[r][c]='.';
        ch[ni][c]='v';
        r=ni;
        return;
    }
    if(direction==1){
        for(i=7;i>c;i--){
            if(ch[r][i]=='.'){
                continue;
            }
            offset=step-blank[i];
            if(offset<=0){
                continue;
            }
            ni=i+offset;
            if(ni>7){
                continue;
            }
            ch[r][ni]=ch[r][i];
        }
        ni=c+step;
        ni=ni>7?7:ni;
        for(i=c;i<ni;i++){
            ch[r][i]='.';
        }
        ch[r][c]='.';
        ch[r][ni]='>';
        c=ni;
        return;
    }
    if(direction==3){
        for(i=0;i<c;i++){
            if(ch[r][i]=='.'){
                continue;
            }
            offset=step-blank[i];
            if(offset<=0){
                continue;
            }
            ni=i-offset;
            if(ni<0){
                continue;
            }
            ch[r][ni]=ch[r][i];
        }
        ni=c-step;
        ni=ni<0?0:ni;
        for(i=c;i>ni;i--){
            ch[r][i]='.';
        }
        ch[r][c]='.';
        ch[r][ni]='<';
        c=ni;
        return;
    }
}

void turn(void){
    if(dc[0]=='r'){//right
        direction+=1;
        direction=direction==4?0:direction;
        ch[r][c]=symbol[direction];
        return;
    }
    if(dc[0]=='l'){//left
        direction-=1;
        direction=direction==-1?3:direction;
        ch[r][c]=symbol[direction];
        return;
    }
    direction+=2;//back
    direction%=4;
    ch[r][c]=symbol[direction];
}

void print_table(void){
    int i;
    for(i=0;i<8;i++){
        printf("%s\n",ch[i]);
    }
    printf("\n");
}

int main(void){
    int i,j;
    char tc;
    int find;
    while(1){
        for(i=0;i<8;i++){//读棋盘
            scanf("%s",ch[i]);
            if(ch[i][0]=='-'){
                return 0;
            }
        }
        
        find=0;
        for(i=0;i<8;i++){//找起点
            for(j=0;j<8;j++){
                tc=ch[i][j];
                if(tc=='<'||tc=='>'||tc=='^'||tc=='v'){
                    r=i;
                    c=j;
                    find=1;
                    if(tc=='^'){
                        direction=0;
                        break;
                    }
                    if(tc=='>'){
                        direction=1;
                        break;
                    }
                    if(tc=='v'){
                        direction=2;
                        break;
                    }
                    if(tc=='<'){
                        direction=3;
                        break;
                    }
                }
            }
            if(find){
                break;
            }
        }
        
        while(1){//读scripts
            scanf("%s",command);
            if(command[0]=='#'){
                break;
            }
            if(command[0]=='m'){
                scanf("%d",&step);
                moveOn();
            }else{
                scanf("%s",dc);
                turn();
            }
        }
        print_table();
    }
    return 0;
}