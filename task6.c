#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_DIRS 1000

void list_sorted_dirs(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) {
        perror("cannot open catalog");
        return;
    }

    char directories[MAX_DIRS][256];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat statbuf;
        char full_path[1024];

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                strncpy(directories[count++], entry->d_name, sizeof(directories[count]) - 1);
            }
        }
    }
    closedir(dir);
    qsort(directories, count, sizeof(directories[0]), (int (*)(const void *, const void *)) strcmp);

    printf("SORTED CATALOGES in%s\n", path);
    for (int i = 0; i < count; i++) {
        printf("%s\n", directories[i]);
    }
}

int main() {
    char path[1024] = "."; 
    list_sorted_dirs(path);
    return 0;
}