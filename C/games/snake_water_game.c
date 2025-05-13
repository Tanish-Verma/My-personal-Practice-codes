#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int get_random(int min, int max) {  // Renamed function
    return min + rand() % (max - min + 1);
}

void toLowercase(char *str) {
    int i = 0;
    while (str[i]) {
        str[i] = tolower(str[i]);  // Convert each character to lowercase
        i++;
    }
}

int main() {
    srand(time(NULL));
    /*0=snake
    1=water
    2=gun*/
    char opt[15];
    printf("Welcome to snake water gun.\nHere you will be playing against a specially trained computer. Do try your best to win!\n");
    int nrounds, computer = 0, player = 0;
    printf("Enter the Number of points to play: ");
    scanf("%d", &nrounds);

    while (computer < nrounds && player < nrounds) {
        int computeroption = get_random(0, 2);  // Updated function call
        char compoption[15];
        int playeroption;
        printf("Type your choice: ");
        scanf("%14s", opt);  // Removed & from opt
        toLowercase(opt);

        if (strcmp("snake", opt) == 0) playeroption = 0;
        else if (strcmp("water", opt) == 0) playeroption = 1;
        else if (strcmp("gun", opt) == 0) playeroption = 2;
        else {
            printf("Invalid input \n");
            continue;
        }

        if (computeroption == 0) strcpy(compoption, "snake");
        if (computeroption == 1) strcpy(compoption, "water");
        if (computeroption == 2) strcpy(compoption, "gun");

        printf("Player = %s \tcomputer = %s\n", opt, compoption);
        if (strcmp(opt, compoption) == 0) {
            printf("It is a draw \n\n");
        }
        if ((playeroption == 0 && computeroption == 1) || (playeroption == 1 && computeroption == 2) || (playeroption == 2 && computeroption == 0)) {
            printf("YAY! You won this round \n\n");
            player++;
        }
        if ((computeroption == 0 && playeroption == 1) || (computeroption == 1 && playeroption == 2) || (computeroption == 2 && playeroption == 0)) {
            printf("NOo! You lost this round \n\n");
            computer++;
        }
        printf("Current points Player = %d and computer = %d\n", player, computer);
    }

    if (player > computer) printf("YAY! You won the game\n");
    else printf("NOoo! You lost the game\n");

    return 0;
}
