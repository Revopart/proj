#include <stdio.h>

int main() {
    int name;
    char del;
    if (scanf("%d%c", &name, &del) != 1 && del != '\n') {
        return -1;
    }
    printf("Hello, %d!\n", name);
    return 0;
}
