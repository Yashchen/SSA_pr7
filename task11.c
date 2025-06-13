#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#define MAX_NAME 256

int max_depth = 0;
int total_dirs = 0;
int total_symlinks = 0;

typedef struct NameNode {
    char name[MAX_NAME];
    int count;
    struct NameNode *next;
} NameNode;

NameNode *head = NULL;

void add_or_increment(const char *name) {
    NameNode *curr = head;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }
    NameNode *new_node = malloc(sizeof(NameNode));
    strcpy(new_node->name, name);
    new_node->count = 1;
    new_node->next = head;
    head = new_node;
}

int count_repeats() {
    int repeat_penalty = 0;
    NameNode *curr = head;
    while (curr) {
        if (curr->count > 1) {
            repeat_penalty += curr->count - 1;
        }
        curr = curr->next;
    }
    return repeat_penalty;
}

void free_list() {
    NameNode *curr = head;
    while (curr) {
        NameNode *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

void analyze_dir(const char *path, int depth) {
    if (depth > max_depth) max_depth = depth;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        lstat(full_path, &st);

        if (S_ISDIR(st.st_mode)) {
            total_dirs++;
            add_or_increment(entry->d_name);
            analyze_dir(full_path, depth + 1);
        } else if (S_ISLNK(st.st_mode)) {
            total_symlinks++;
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s <шлях_до_каталогу>\n", argv[0]);
        return 1;
    }

    analyze_dir(argv[1], 1);

    int penalty = count_repeats();
    int complexity = (max_depth * 2) + total_dirs + (total_symlinks * 3) + (penalty * 2);

    printf("Максимальна глибина: %d\n", max_depth);
    printf("Кількість директорій: %d\n", total_dirs);
    printf("Кількість symlink: %d\n", total_symlinks);
    printf("Штраф за повтори: %d\n", penalty);
    printf("Складність структури: %d\n", complexity);

    free_list();
    return 0;
}
