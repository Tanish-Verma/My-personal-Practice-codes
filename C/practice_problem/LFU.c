#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int key;
    int count;
    int value;
    struct ListNode * next;
    struct ListNode * prev; 
};

typedef struct LFUcache{
    int capacity;
    int size;
    struct ListNode * head;
    struct ListNode * tail;
} LFUCache;

struct ListNode * newNode(int key,int count,int value){
    struct ListNode * newnode =(struct ListNode *)malloc(sizeof(struct ListNode));
    newnode->key=key;
    newnode->count=count;
    newnode->value=value;
    newnode->next=NULL;
    newnode->prev=NULL;
    return newnode;
}

void removeNode(LFUCache * obj,struct ListNode * node){
    struct ListNode * search= obj->head;
    struct ListNode dummy;
    dummy.next=search;
    struct ListNode * prev=&dummy;
    while(search!=node){
        search=search->next;
        prev=prev->next;
    }
    if(node==obj->head){
        obj->head=node->next;
    }
    else if(node==obj->tail){
        obj->tail=prev;
    }
    prev->next=search->next;
    obj->size--;
    free(node);
}

void addToFront(LFUCache * obj,struct ListNode * node){
    if(obj->head==NULL){
        obj->head=node;
        obj->tail=node;
        obj->size++;
        node->count++;
        return;
    }
    // struct Node * newnode =newNode(node->key,node->value)
    node->next=obj->head;
    obj->head=node;
    node->count++;
    obj->size++;
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache * obj = (LFUCache *)malloc(sizeof(LFUCache));
    obj->capacity=capacity;
    obj->head=NULL;
    obj->size=0;
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    struct ListNode * search =obj->head;
    while(search!=NULL && search->key!=key){
        search=search->next;
    }
    if(search==NULL){
        return -1;
    }
    else{
        int val = search->value;
        addToFront(obj,newNode(key,search->count,val));
        removeNode(obj,search);
        return val;
    }
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    struct ListNode * search =obj->head;
    while(search!=NULL && search->key!=key){
        search=search->next;
    }
    if(search==NULL){
        addToFront(obj,newNode(key,0,value));
    }
    else{
        search->value=value;
        addToFront(obj,newNode(key,search->count,value));
        removeNode(obj,search);
    }
    if(obj->size>obj->capacity){
        int min=2147483647;
        struct ListNode * minfreq=NULL;
        struct ListNode* current=obj->head;
        while(current!=NULL){
            if(current->count<=min){
                min=current->count;
                minfreq=current;
            }
            current=current->next;
        }
        removeNode(obj,minfreq);
    }
}

void lFUCacheFree(LFUCache* obj) {
    struct ListNode * current = obj->head;
    while(current!=NULL){
        struct ListNode * temp = current;
        current=current->next;
        free(temp);
    }
}

void printCache(LFUCache * obj){
    struct ListNode * current = obj->head;
    while(current!=NULL){
        printf("%d %d %d\n",current->key,current->count,current->value);
        current=current->next;
    }
}

int main (){
    int capacity, op, key, value;
    
    scanf("%d", &capacity);
    LFUCache* cache = lFUCacheCreate(capacity);
    
    while(1){
        scanf("%d", &op);
        switch(op){
            case 1:
                scanf("%d", &key);
                value = lFUCacheGet(cache, key);
                if(value == -1){
                    printf("Get %d: Not found.\n", key);
                }
                else {
                    printf("Get %d: %d\n", key, value);
                }
                break;
            case 2:
                scanf("%d %d", &key, &value);
                lFUCachePut(cache, key, value);
                break;
            case 3:
                printCache(cache);
                break;
            default:
                return 0;
        }
    }
    lFUCacheFree(cache);
    return 0;
}