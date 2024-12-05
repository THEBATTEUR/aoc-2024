/*
 * NMC
 * Advent of code day 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define BUFFER_SIZE 20000

int main(void) {
    const char *pattern = "mul\\(([0-9]+),([0-9]+)\\)";

    FILE *inputFile = NULL;
    inputFile = fopen("../day03/input", "r");
    if (inputFile == NULL) {
        printf("Fatal error : cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    char line[BUFFER_SIZE];
    regex_t regex;
    regmatch_t matches[3];
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        printf("Error: cannot compile REGEX.\n");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t total = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        char *current = line;

        while (regexec(&regex, current, 3, matches, 0) == 0) {
            size_t start1 = matches[1].rm_so;
            size_t end1 = matches[1].rm_eo;
            size_t start2 = matches[2].rm_so;
            size_t end2 = matches[2].rm_eo;

            char num1_str[end1 - start1 + 1];
            char num2_str[end2 - start2 + 1];
            snprintf(num1_str, sizeof(num1_str), "%.*s", end1 - start1, current + start1);
            snprintf(num2_str, sizeof(num2_str), "%.*s", end2 - start2, current + start2);

            size_t num1 = atoi(num1_str);
            size_t num2 = atoi(num2_str);

            size_t result = num1 * num2;

            total += result;

            current += matches[0].rm_eo;
        }
    }

    printf("Total : %d", total);

    regfree(&regex);
    fclose(inputFile);
    return 0;
}
