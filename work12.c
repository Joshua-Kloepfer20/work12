#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    DIR * d;
    if (argc == 1 || (argc == 2 && (d = opendir(argv[1])) == NULL)) {
        d = NULL;
        char z[100];
        while (d == NULL) {
            if (strcmp(strerror(errno), "Success\0")) {
                printf("%s\nplease enter a new path:\n", strerror(errno));
            }
            else {
                printf("please enter a path:\n");
            }
            int x = read(STDIN_FILENO, z, 100);
            if (z[x - 1] == '\n') {
                z[x - 1] = '\0';
                }
            else {
                z[x] = '\0';
                }
            d = opendir(z);
        }
    }
    struct dirent *x;
    struct stat y;
    int sum = 0;
    while ((x=readdir(d)) != NULL) {
        if (x->d_type == 8) {
            stat(x->d_name, &y);
            sum += y.st_size;
        }
    }
    printf("Total Size: %d\n", sum);
    rewinddir(d);
    printf("directories:\n");
    while ((x=readdir(d)) != NULL) {
        if (x->d_type == 4) {
            printf("%s\n", x->d_name);
        }
    }
    rewinddir(d);
    printf("files:\n");
    while ((x=readdir(d)) != NULL) {
        if (x->d_type == 8) {
            printf("%s\n", x->d_name);
        }
    }
    return 0;
}