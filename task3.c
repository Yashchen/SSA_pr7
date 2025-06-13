#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void search_in_file(const char *filename, const char *word) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("file not found");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word)) {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {return 1;}
    search_in_file(argv[1], argv[2]);
    return 0;
}