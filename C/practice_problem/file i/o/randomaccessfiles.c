#include <stdio.h>

typedef struct{
    int accno;
    char firstname[15];
    char lastname[15];
    double balance;
}Account;

int main(){
    FILE *ptr;
    Account client={0,"","",0};
    ptr=fopen("account.dat","wb+");
    if(ptr==NULL){
        printf("Error opening file\n");
        return 1;
    }
    else{
        printf("Enter account no (1-100) 0 to end: ");
        scanf("%d",&client.accno);
        getchar();
        while(client.accno!=0){
            printf("Enter first name,Last name,balance: ");
            fscanf(stdin,"%s%s%lf",client.firstname,client.lastname,&client.balance);
            fseek(ptr,(client.accno-1)*sizeof(Account),SEEK_SET);
            fwrite(&client,sizeof(Account),1,ptr);
            printf("Enter account number: ");
            scanf("%d",&client.accno);
            getchar();
        }
    }
    fclose(ptr);
    return 0;
}