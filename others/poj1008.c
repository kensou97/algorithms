/**
 玛雅历
 题目罗嗦了一大堆，其实就是个算术题......
 **/
#include <stdio.h>
#include <string.h>

int day;
char month[10];
int year;

int days;

char* haab_months[]={"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu","uayet"};

char* tzolkin[]={"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

void haab_to_days(void){
    days=0;
    days+=(year*365);
    int i;
    for(i=0;i<19;i++){
        if(strcmp(month,haab_months[i])==0){
            break;
        }
    }
    days+=(i*20);
    days+=day;
}

void days_to_tzolkin(void){
    year=days/260;
    
    int period=days%260;
    day=period%13+1;
    strcpy(month,tzolkin[period%20]);
}

int main(void){
    int N;
    scanf("%d",&N);
    printf("%d\n",N);
    
    while(N--){
        scanf("%d. %s %d",&day,month,&year);
        haab_to_days();
        days_to_tzolkin();
        printf("%d %s %d\n",day,month,year);
    }
    return 0;
}