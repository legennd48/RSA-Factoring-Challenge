#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

void factorize(const char *num_str) {
    mpz_t num;
    mpz_init(num);
    mpz_set_str(num, num_str, 10);

    mpz_t div, quotient, remainder;
    mpz_inits(div, quotient, remainder, NULL);
    mpz_set_ui(div, 2);

    while (mpz_cmp(div, num) <= 0) {
        mpz_tdiv_qr(quotient, remainder, num, div);
        if (mpz_cmp_ui(remainder, 0) == 0) {
            gmp_printf("%Zd=%Zd*%Zd\n", num, quotient, div);
            break;
        }
        mpz_add_ui(div, div, 1);
    }

    mpz_clears(num, div, quotient, remainder, NULL);
}

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, file) != -1) {
        line[strcspn(line, "\n")] = 0; // remove newline character if present
        factorize(line);
    }

    free(line);
    fclose(file);
    exit(EXIT_SUCCESS);
}
