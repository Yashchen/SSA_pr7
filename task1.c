#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[128];
    fp = popen("rwho | more", "r");
    if (fp == NULL) {
        perror("error executing command");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);

    return 0;
}
