#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) {
        perror("cannot find catalog");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 ||
		strcmp(entry->d_name, "..") == 0)
                continue;
            printf("catalog -> %s\n", full_path);
            list_files(full_path); 
        } else {
            printf("file -> %s\n", full_path);
        }
    }

    closedir(dir);
}

int main() {
    char path[1024];
    getcwd(path, sizeof(path));
    list_files(path);
    return 0;
}