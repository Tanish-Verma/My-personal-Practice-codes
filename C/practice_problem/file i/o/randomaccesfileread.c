#include <stdio.h>


typedef struct{
    int accno;
    char firstname[15];
    char lastname[15];
    double balance;
}Account;


int main(){
    FILE * ptr;
    Account client ={0,"","",0};
    if((ptr=fopen("account.dat","rb"))==NULL){
        printf("error opening file");
        return 1;
    }
    else{
        printf("%-6s%-16s%-11s%10s\n","ACC","LastName","FirstName","Balance");
        while(!feof(ptr)){
            fread(&client,sizeof(Account),1,ptr);
            if(client.accno!=0){
                printf("%-6d%-16s%-11s%10.2lf\n",client.accno,client.lastname,client.firstname,client.balance);
            }
        }
        fclose(ptr);
    }
    return 0;
}