#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union data
{
    int Int;
    char *str;
} data;

void print_matrix(int rows, int cols, int selector, data matrix[][cols])
{
    printf("[ \n");
    for (int i = 0; i < rows; i++)
    {
        printf("[ ");
        for (int j = 0; j < cols; j++)
        {
            if (selector)
            {

                strlen(matrix[i][j].str) > 3 ? printf("%d ", strlen(matrix[i][j].str)) : printf("%s ", matrix[i][j].str);
            }
            else
            {
                printf("%s ", matrix[i][j].str);
            }
        }
        printf("]\n");
    }
    printf("]\n");
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    getchar();
    data arr[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char *str = (char *)malloc(sizeof(char));
            int k = 0;
            char c;
            while ((c = getchar()) != '\n' && c != ' ' && c != EOF)
            {
                str = (char *)realloc(str, k + 2);
                str[k++] = c;
            }
            str[k] = '\0';
            arr[i][j].str = str;
        }
    }
    print_matrix(n, m, 0, arr);
    print_matrix(n, m, 1, arr);
    return 0;
}