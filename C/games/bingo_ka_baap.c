#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h> // Required for strcmp

// Function to check if the player's input matches one of the three generated numbers
int checkinput(int, int[]);

// Function to generate a random number between min and max (inclusive)
int random(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Function to generate three unique random numbers within a given range (min, max)
void generate_unique_random_numbers(int randomnum[3], int min, int max)
{
    for (int i = 0; i < 3; i++)
    {
        int num = random(min, max); // Generate random number
        int is_unique = 0;

        // Keep generating numbers until a unique one is found
        while (!is_unique)
        {
            is_unique = 1;              // Assume the number is unique
            for (int j = 0; j < i; j++) // Compare with previously generated numbers
            {
                if (randomnum[j] == num)
                {
                    is_unique = 0; // Not unique, regenerate
                    num = random(min, max);
                    break;
                }
            }
        }
        randomnum[i] = num; // Store the unique number
    }
}

// Function to check if a number is already present on the current player's bingo card
int repcheck(int players, int size, int arr[players][size][size], int num, int currentplayer, int currentrow, int currentcolumn)
{
    // Check the current player's bingo card up to the current row and column for duplicate numbers
    for (int i = 0; i <= currentrow; i++)
    {
        int limit = (i == currentrow) ? currentcolumn : size; // Limit columns in the current row to the current column
        for (int j = 0; j <= limit; j++)
        {
            if (arr[currentplayer][i][j] == num)
                return 1; // Duplicate found
        }
    }
    return 0; // No duplicates
}

// Function to generate a bingo card for each player with unique numbers
void makebingocard(int players, int size, int arr[players][size][size])
{
    int max = size * size; // Maximum possible number on the bingo card
    for (int i = 0; i < players; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                int num = random(1, max);
                if (repcheck(players, size, arr, num, i, j, k))
                {
                    k--; // Regenerate the number if it's a duplicate
                    continue;
                }
                arr[i][j][k] = num; // Assign unique number to the bingo card
            }
        }
    }
}

// Function to check and mark a number on the current player's bingo card
int checkbingocard(int num, int players, int size, int arr[players][size][size], int currentplayer)
{
    // Search for the number on the bingo card and mark it as zero (crossed out) if found
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[currentplayer][i][j] == num)
            {
                arr[currentplayer][i][j] = 0; // Mark as called (cross out)
                return 1;
            }
        }
    }
    return 0;
}

// Function to check if a player has completed a row, column, or diagonal and won the game
int gamefinish(int players, int size, int arr[players][size][size], int currentplayer)
{
    // Check rows and columns
    for (int i = 0; i < size; i++)
    {
        int row_complete = 1;
        int column_complete = 1;

        for (int j = 0; j < size; j++)
        {
            if (arr[currentplayer][i][j] != 0) // Check if the entire row is crossed out
                row_complete = 0;

            if (arr[currentplayer][j][i] != 0) // Check if the entire column is crossed out
                column_complete = 0;
        }

        if (row_complete || column_complete) // Return true if any row or column is fully crossed out
            return 1;
    }

    // Check diagonals
    int diag1_complete = 1; // Top-left to bottom-right diagonal
    int diag2_complete = 1; // Top-right to bottom-left diagonal

    for (int i = 0; i < size; i++)
    {
        if (arr[currentplayer][i][i] != 0) // Check if main diagonal is crossed out
            diag1_complete = 0;

        if (arr[currentplayer][i][size - i - 1] != 0) // Check if anti-diagonal is crossed out
            diag2_complete = 0;
    }

    if (diag1_complete || diag2_complete) // Return true if either diagonal is fully crossed out
        return 1;

    return 0; // No winner yet
}

// Function to add a number to the player's card
int add(int players, int size, int arr[players][size][size], int num, int player, int row, int col)
{
    // Check if the number does not already exist and the cell is empty
    if (!(repcheck(players, size, arr, num, player, size, size)) && arr[player][row][col] == 0)
    {
        arr[player][row][col] = num; // Add the number to the given row and column
        return 1;
    }
    return 0;
}

// Function to check if the player's choice is valid (must match one of the generated random numbers)
int checkinput(int num, int arr[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (num == arr[i])
            return 1;
    }
    return 0;
}

int main()
{
    // Display game introduction
    printf("Welcome to BINGO KA BAAP.\nPlease read the following details:\n");
    printf("1. The game is played between 2-10 players.\n");
    printf("2. The bingo card can be made into any square matrix.\n");
    printf("3. In this game, you will be given three numbers.\n");
    printf("4. You can choose any one number to cross out on your bingo card.\n");
    printf("5. Whoever gets a complete row, column, or diagonal crossed first will win.\n");
    printf("6. You can also 'add' a number to another player's card.\n");
    printf("7. Once a player has added,the next player cannot add.(totally not a bug)\n");
    printf("Please enjoy the game\n");
    srand(time(NULL)); // Initialize random number generator

    int size, players, s = 0;

    // Input validation for number of players and size of the bingo card
    while (s != 1)
    {
        printf("Enter the number of players (2-10): ");
        scanf("%d", &players);
        if (players > 10)
        {
            printf("Too many players. Please input again.\n");
            continue;
        }

        printf("Enter the size of the bingo card (max 6): ");
        scanf("%d", &size);
        if (size > 6)
        {
            printf("The size is too large. Please input again.\n");
            continue;
        }
        else
            s = 1;
    }

    // Create and initialize bingo cards for all players
    int bingocards[players][size][size];
    makebingocard(players, size, bingocards);

    // Display bingo cards for all players
    for (int i = 0; i < players; i++)
    {
        printf("Player %d Bingo card:\n", i + 1);
        for (int k = 0; k < size; k++)
        {
            printf("[ ");
            for (int j = 0; j < size; j++)
            {
                printf("%d ", bingocards[i][k][j]);
            }
            printf("]\n");
        }
        printf("\n");
    }

    // Main game loop
    int option[players];
    while (1)
    {
        for (int i = 0; i < players; i++)
        {
            // Generate three unique random numbers for the player to choose from
            int randomnum[3];
            generate_unique_random_numbers(randomnum, 1, size * size);

            // Display current bingo card for the player
            printf("Current Bingo card for player %d\n", i + 1);
            for (int k = 0; k < size; k++)
            {
                printf("[ ");
                for (int j = 0; j < size; j++)
                {
                    printf("%d ", bingocards[i][k][j]);
                }
                printf("]\n");
            }
            char choice[10];
            // Display the random numbers for the player to choose
            printf("%d %d %d\n", randomnum[0], randomnum[1], randomnum[2]);
            printf("Type your Move (add or cross): ");
            scanf("%s", choice);
            //checking for valid input
            if (strcmp(choice, "add")!= 0 && strcmp(choice, "cross")!= 0)
            {
                printf("Invalid choice,Try again.\n");
                i--;
                continue;
            }
            if (strcmp(choice, "add") == 0) // Handle "add" option
            {
                int num = 0, player, row, col;
                while (!(checkinput(num, option))) // Ensure a valid number is selected
                {
                    printf("Choose the player you want to add the number to: ");
                    scanf("%d", &player);
                    printf("Choose the number you want to add: ");
                    scanf("%d", &num);
                    if (!checkinput(num, randomnum)) // Validate the number
                    {
                        printf("Invalid Input, please type proper input\n");
                        continue;
                    }
                    if (repcheck(players, size, bingocards, num, player-1, size, size))
                    {
                        printf("Too bad, the number already exists.\n");
                        continue;
                    }
                    printf("Choose the row and column you want the number to be in (input=(x y) where x is row, y is column): ");
                    scanf("%d %d", &row, &col);

                    if (row < 0 || row - 1 >= size || col < 0 || col - 1 >= size) // Ensure valid row and column inputs
                    {
                        printf("Invalid row or column. Please input values within bounds.\n");
                        continue;
                    }

                    if (add(players, size, bingocards, num, player - 1, row - 1, col - 1)) // Adjust for 0-based index
                    {
                        printf("Number successfully added :)\n");
                    }
                    else
                    {
                        printf("Too bad, you can't replace numbers.\n");
                    }
                }
            }
            else if (strcmp(choice, "cross") == 0) // Handle "cross" option
            {
                printf("For player %d\n", i + 1);
                printf("Enter any one number to cross out on your bingo card: ");
                scanf("%d", &option[i]);

                // Validate the player's choice
                if (!checkinput(option[i], randomnum))
                {
                    printf("Invalid Input. Please try again.\n");
                    i--;
                    continue;
                }
                // Mark the chosen number on the bingo card
                checkbingocard(option[i], players, size, bingocards, i);
            }
            printf("Current Bingo card for player %d\n", i + 1);
            for (int k = 0; k < size; k++)
            {
                printf("[ ");
                for (int j = 0; j < size; j++)
                {
                    printf("%d ", bingocards[i][k][j]);
                }
                printf("]\n");
            }

            // Check if the player has won
            if (gamefinish(players, size, bingocards, i))
            {
                printf("Player %d has WON!!!\n", i + 1);
                return 0;
            }
        }
    }
    printf("THANK YOU FOR PLAYING THE GAME (;\n");
}
