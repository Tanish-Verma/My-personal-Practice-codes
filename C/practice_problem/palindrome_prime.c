#include <stdio.h>
#include <math.h>

int main()
{
    long int result = 0, start, stop;

    printf("Enter the range of search: \n");
    scanf("%ld %ld", &start, &stop);
    // starting from stop to find largest palindrome.
    for (long int i = stop; i >= start; i--)
    {
        int temp = i, reverse = 0;
        // reversing the rumber.
        while (temp != 0)
        {
            int k = temp % 10;
            reverse = reverse * 10 + k;
            temp /= 10;
        }
        // checking if the number is a palindrome.
        if (reverse == i)
        {
            // checking for prime palindrome
            int isprime = 1;
            for (int k = 2; k < i; k++)
            {
                if (i % k == 0)
                {
                    isprime = 0;
                    break;
                }
            }
            if (isprime == 1)
            {
                result = i;
                printf("The prime palindrome is %ld\n", result);
                return 0; // ends the program
            }
        }
    }
    printf("There was no such palindrome in the range [%ld,%ld].\n", start, stop);

    return 0;
}