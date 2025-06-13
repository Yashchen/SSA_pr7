#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File \"%s\" deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

void list_and_delete_files() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    char response;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("Delete file \"%s\"? (y/n): ", entry->d_name);
            scanf(" %c", &response);
            if (response == 'y' || response == 'Y') {
                delete_file(entry->d_name);
            }
        }
    }
    closedir(dir);
}

int main() {
    list_and_delete_files();
    return 0;
}