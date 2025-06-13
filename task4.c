#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20

void print_file_with_pause(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Не вдалося відкрити файл: %s\n", filename);
        return;
    }

    char line[512];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count >= LINES_PER_PAGE) {
            printf("\nenter ENTER to cont");
            getchar();
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf(" %s\n%s\n", argv[i], "=============================");
        print_file_with_pause(argv[i]);
    }

    return 0;
}