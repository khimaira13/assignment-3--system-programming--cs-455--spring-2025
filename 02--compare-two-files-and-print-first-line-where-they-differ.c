#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename1>.<extension> <filename2>.<extension>\n", argv[0]);
        return 1;
    }

    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");

    if (!f1 || !f2) {
        printf("Error opening files\n");
        return 1;
    }

    char line1[MAX_LEN], line2[MAX_LEN];
    int line = 1;

    while (fgets(line1, MAX_LEN, f1) && fgets(line2, MAX_LEN, f2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Difference at line %d:\n", line);
            printf("File 1: %s\n", line1);
            printf("File 2: %s", line2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
        line++;
    }
    //check for extra line from one file than the other
    if (fgets(line1, MAX_LEN, f1) || fgets(line2, MAX_LEN, f2)) {
        printf("Difference at line %d: one file is longer\n", line);
    } else {
        printf("Files are identical\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
