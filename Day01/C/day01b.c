#include <stdio.h>

void iqueue_push(int *queue, size_t n, int a) {
    for(int i = 0; i < n - 1; i++)
        queue[i] = queue[i+1];

    queue[n-1] = a; 
}

int main() {
    int counter = 0;

    int queue[3] = {0,0,0};
    int new = 0;

    for(int i = 0; i < 3; i++)
        scanf("%d", &queue[i]);

    while(scanf("%d", &new) != EOF) {
        if(new > queue[0])
            counter++;

        iqueue_push(queue, 3, new);
    }
    
    printf("%d\n", counter);
}
