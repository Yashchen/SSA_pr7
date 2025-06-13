#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_FILES 100

void change_permissions(const char *filename) {
    if (chmod(filename, S_IRUSR | S_IRGRP | S_IROTH) == 0) {
        printf("permission was given -> %s\n", filename);
    } else {
        perror("couldn't give permission");
    }
}

void list_and_modify_c_executables() {
    struct dirent *entry;
    DIR *dir = opendir(".");
    char files[MAX_FILES][256];
    int count = 0;

    if (!dir) {
        perror("couldn't open catalog");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        struct stat statbuf;
        if (stat(entry->d_name, &statbuf) == 0 && (strstr(entry->d_name, ".c") || strstr(entry->d_name, ".exe"))) {
            strncpy(files[count++], entry->d_name, sizeof(files[count]) - 1);
        }
    }
    closedir(dir);

    if (count == 0) {
        printf("out files was not found\n");
        return;
    }

    printf("\n%d files were found\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%d] %s\n", i + 1, files[i]);
    }

    char response;
    printf("\nDo you want to give permission?(y/n): ");
    scanf(" %c", &response);

    if (response == 'y' || response == 'Y') {
        for (int i = 0; i < count; i++) {
            change_permissions(files[i]);
        }
    } else {
        printf("permissions was not changed\n");
    }
}

int main() {
    list_and_modify_c_executables();
    return 0;
}