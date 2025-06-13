#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf("%c%c%c%c%c%c%c%c%c ",
           (S_ISDIR(mode)) ? 'd' : '-',
           (mode & S_IRUSR) ? 'r' : '-',
           (mode & S_IWUSR) ? 'w' : '-',
           (mode & S_IXUSR) ? 'x' : '-',
           (mode & S_IRGRP) ? 'r' : '-',
           (mode & S_IWGRP) ? 'w' : '-',
           (mode & S_IXGRP) ? 'x' : '-',
           (mode & S_IROTH) ? 'r' : '-',
           (mode & S_IWOTH) ? 'w' : '-');
}

void list_files(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(path);

    if (!dir) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            print_permissions(file_stat.st_mode);
            printf("%c ", (file_stat.st_mode & S_IXOTH) ? 'x' : '-');
            printf("%ld ", file_stat.st_nlink);
            printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
            printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
            printf("%ld ", file_stat.st_size);
            printf("%.12s ", ctime(&file_stat.st_mtime) + 4);
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}