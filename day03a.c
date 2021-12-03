#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define INPUT_MAX 64
#define INUM_LEN 12

static int pow2(int a) {
    if(a > 0) return 2 << (a - 1);
    else return 1;
}

int gamma_to_epsilon(int g) {
    int g_mask = pow2(INUM_LEN) - 1;
    return g_mask ^ g;
}

int main() {
    size_t input_n = INPUT_MAX;
    char input[INPUT_MAX];

    int zeroes[INUM_LEN] = {0};
    int ones[INUM_LEN] = {0};

    while(fgets(input, input_n, stdin) != NULL) {
        for(int i = 0; i < INUM_LEN; i++) {
            if(input[i] == '1')
                ones[i]++;
            else
                zeroes[i]++;
        }
    }

    int gamma = 0;
    for(int i = 0; i < INUM_LEN; i++) {
        if(ones[i] > zeroes[i])
            gamma |= pow2(INUM_LEN - i - 1);
    }

    int epsilon = gamma_to_epsilon(gamma);
    printf("%d\n", gamma * epsilon); 
}
