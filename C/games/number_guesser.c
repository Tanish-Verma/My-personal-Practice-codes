#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int min=1,max=100,input,i=0;
    srand(time(0));
    int random_number= min+ rand()%(max -min+1);
    printf("Welcome to number guesser.\nA random number is chosen between 1 and 100 (both inclusive).\nYou must guess the number in least amount of tries to win.\nIf you wish to resign type 0.\n");
    do
    {
        printf("Enter your guess: ");
        scanf("%d",&input);
        if(input>random_number){
            printf("Lower number please!!\n");}
        else if(input==random_number){
            printf("Congratulations, You guessed it right!!!\n");
            break;
        }
        else if(input==0){
            printf("You have resigned\n");
            break;
        }
        else{
            printf("Higher number please!!\n");
        }
        i++;
    } while (2<10);
    printf("You took %d tries.",i+1);
    printf("Thank you for playing!!!\n");
    return 0;
}