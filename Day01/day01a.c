#include <stdio.h>

int main() {
    int counter = 0;

    int last = 0, x = 0;
    scanf("%d", &last);

    while(scanf("%d", &x) != EOF) {
        if(x > last)
            counter++;

        last = x;
    }
    
    printf("%d\n", counter);
}
