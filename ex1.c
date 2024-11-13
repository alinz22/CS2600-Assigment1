#include <stdio.h>

int main() {
    int number;

    // Print the table header
    printf("Number\tSquare\tCube\n");

    // Loop through numbers from 0 to 10 and calculate square and cube
    for (number = 0; number <= 10; number++) {
        printf("%d\t%d\t%d\n", number, number * number, number * number * number);
    }

    return 0;
}
