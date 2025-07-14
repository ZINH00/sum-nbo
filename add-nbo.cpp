#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    uint32_t sum = 0;

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "rb");
        if (!file) {
            perror("ERROR");
            return 1;
        }

        uint32_t num;
        if (fread(&num, sizeof(num), 1, file) != 1) {
            fprintf(stderr, "ERROR: %s\n", argv[i]);
            fclose(file);
            return 1;
        }
        fclose(file);

        num = ntohl(num);

        printf("%u(0x%08x)", num, num);
        if (i < argc - 1) {
            printf(" + ");
        }
        sum += num;
    }

    printf("= %u(0x%08x)\n", sum, sum);
    return 0;
}

