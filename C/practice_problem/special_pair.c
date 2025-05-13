#include <stdio.h>
#include <math.h>

int main(){
    int a,b,c,d,e,max=-1,temp1,temp2;
    printf("enter the variables: \n");
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    int var[]={a,b,c,d,e};
    int size =sizeof(var)/sizeof(var[0]);
    for(int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            if (fabs(var[i]-var[j])==3){
                int x=var[i],y=var[j];
                if(x+y>max){
                    temp1=x;temp2=y;
                    max=x+y;
                }
                else{continue;}
            }
        }
    }
    if(temp1 && temp2){

        printf("%d %d",temp1,temp2);
    }
    else{
        printf("No valid pair found.");
    }
    return 0;
}