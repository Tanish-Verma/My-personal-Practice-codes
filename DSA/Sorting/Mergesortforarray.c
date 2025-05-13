#include <stdio.h>
#include <stdlib.h>

void merge(int arr[],int l,int r,int mid){
    int i=l,j=mid+1,k=l;
    int * mergedarray=(int *)malloc(sizeof(int)*(r+1));
    while(i<=mid && j<=r){
        if(arr[i]<=arr[j]){
            mergedarray[k]=arr[i];
            i++;k++;
        }
        else{
            mergedarray[k]=arr[j];
            j++;k++;
        }
    }
    while(i<=mid){
        mergedarray[k]=arr[i];
        k++;i++;
    }
    while(j<=r){
        mergedarray[k]=arr[j];
        k++;j++;
    }

    while(l<=r){
        arr[l]=mergedarray[l];
        l++;
    }
    free(mergedarray);
}

void mergesortlist(int arr[],int l,int h){
    if(l<h){
        int mid=(l+h)/2;
        mergesortlist(arr,l,mid);
        mergesortlist(arr,mid+1,h);
        merge(arr,l,h,mid);
    }
}
int main(){
    int N;
    fscanf(stdin,"%d",&N);
    int arr[N];
    for(int i=0;i<N;i++){
        fscanf(stdin,"%d",&arr[i]);
    }
    mergesortlist(arr,0,N-1);
    for(int i=0;i<N;i++){
        fprintf(stdout,"%d ",arr[i]);
    }
    return 0;
}