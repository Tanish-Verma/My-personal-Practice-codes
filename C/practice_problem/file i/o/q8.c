#include <stdio.h>

int main() {
    printf("Processing... ");
    fflush(stdout);  // Ensure "Processing... " is immediately displayed

    // Simulate some work with a delay
    for (volatile int i = 0; i < 1000000000; i++);  // Busy wait

    printf("Done!\n");  // Complete the message after processing
    return 0;
}
