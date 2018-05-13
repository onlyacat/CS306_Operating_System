#include <stdio.h>
#include <string.h>

int main() {
    int i = 0;
    char testcase[100][7];
    char input[7];
    int valid[64];
    char array[64][7];
    int hitnum = 0;

    while (1) {
        fflush(stdin);
        scanf("%s", input);
        if (strcmp(input, "END") == 0)
            break;
        input[6] = '\0';
        strcpy(testcase[i], input);
        i++;
    }

    for (int j = 0; j < i; ++j) {
        int a;
        sscanf(testcase[j], "%x", &a);
        int index = a % 64;

        if (valid[index] == 0) {
            valid[index] = 1;
            strcpy(array[index], testcase[j]);
            printf("Miss\n");
            continue;
        }
        if (strcmp(array[index], testcase[j]) != 0) {
            strcpy(array[index], testcase[j]);
            printf("Miss\n");
            continue;
        }

        printf("Hit\n");
        hitnum++;
    }

    printf("Hit ratio = %.2f%%\n", (float) hitnum / i * 100);

    return 0;
}