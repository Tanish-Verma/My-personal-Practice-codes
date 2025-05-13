#include <stdio.h>
#include <stdlib.h>

enum sortcrt{
    age=1,
    weight
};

typedef struct person {
    char *name;
    int age;
    float weight;
}prs;

int structsort(const void  *a, const void *b) {
    prs *pa = (prs *)a;
    prs *pb = (prs*)b;
    return  (pa->age - pb->age);
}
int structsort1(const void  *a, const void *b) {
    prs *pa = (prs *)a;
    prs *pb = (prs*)b;
    return  (pa->weight - pb->weight);
}

int main(){
    int T;
    enum sortcrt  sortcrit;
    printf("Enter the number of people for the database: ");
    scanf("%d",&T);
    prs * ptr=(prs*)calloc(T,sizeof(prs));
    for(int i=0;i<T;i++){
        getchar();
        ptr[i].name=(char*)calloc(1,sizeof(char));
        printf("Enter the name of person %d: ",i+1);
        int j=0;
        while (1){
            char k;
            scanf("%c",&k);
            // getchar();
            if(k=='\0' || k=='\n'){
                break;
            }
            ptr[i].name[j]=k;
            ptr[i].name=realloc(ptr[i].name,j+2);
            j++;
            // printf("hi");
        }
        ptr[i].name[j]='\0';
        printf("Enter the Age of person %d: ",i+1);
        scanf("%d",&ptr[i].age);
        printf("Enter the weight of person %d: ",i+1);
        scanf("%f",&ptr[i].weight);
    }
    int choice;

    printf("enter the sort criterion(1 or 2): ");
    scanf("%d",&choice);
    if(choice==age){
        qsort(ptr,T,sizeof(prs),structsort);
    }
    else{
        qsort(ptr,T,sizeof(prs),structsort1);
    }
    for(int i=0;i<T;i++){
        printf("name=%s, age=%d, weight=%f\n",ptr[i].name,ptr[i].age,ptr[i].weight);
    }

    return 0;
}