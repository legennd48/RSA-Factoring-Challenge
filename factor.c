#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    long long number, counter, div;
    ssize_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        number = atoll(line);
        div = 2;
        while (div <= number) {
            if (number % div == 0) {
                counter = number / div;
                printf("%lld=%lld*%lld\n", number, counter, div);
                break;
            }
            div++;
        }
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
