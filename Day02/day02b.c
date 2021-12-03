#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

enum MoveType {
    MOVE_HORZ,
    MOVE_DEPTH,
};

bool parse_cmd(char *in, enum MoveType *mvtype, int *value) {
    char *token;
    bool reverse = false;
    token = strtok(in, " ");

    if(!strcmp(in, "forward")) {
        *mvtype = MOVE_HORZ;
    } else if(!strcmp(in, "down")) {
        *mvtype = MOVE_DEPTH;
    } else if(!strcmp(in, "up")) {
        reverse = true;
        *mvtype = MOVE_DEPTH;
    } else {
        return true;
    }

    token = strtok(NULL, " ");
    *value = atoi(token);

    if(reverse)
        *value = -(*value);
    
    return false;
}

int main() {
    size_t input_n = 128;
    char input[128];

    int aim = 0, depth = 0, horizontal = 0;

    while(fgets(input, input_n, stdin) != NULL) {
        enum MoveType mvtype;
        int value;

        if(parse_cmd(input, &mvtype, &value)) {
            fprintf(stderr, "Couldn't parse: %s\n", input);
            exit(1);
        }

        if(mvtype == MOVE_HORZ) {
            horizontal += value;
            depth += aim * value;
        } else {
            aim += value;
        }
    }

    printf("%d", horizontal * depth);
}
