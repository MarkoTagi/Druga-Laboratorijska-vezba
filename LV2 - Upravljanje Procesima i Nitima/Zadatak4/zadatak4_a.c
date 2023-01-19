#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Command line arguments...\n");
    for (int i = 0; i < argc - 1; ++i) printf("Argument #%d: %s,\n", i, argv[i]);
    printf("Argument #%d: %s.\n", argc - 1, argv[argc - 1]);
    return 0;
}
