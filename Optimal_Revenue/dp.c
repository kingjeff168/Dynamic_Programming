#include <stdio.h>
#include <stdlib.h>

void findMaxRevenue(int N, int *pi, int *ci, int batter, char *distribution) 
{
    int *maxRevenue = (int *)malloc((N + 1) * sizeof(int));
    int *lastBatterSize = (int *)malloc((N + 1) * sizeof(int));

    maxRevenue[0] = 0;

    for (int i = 1; i <= N; i++) 
    {
        maxRevenue[i] = 0;
        // Iterate over sizes and update the max revenue if a better choice is found.
        for (int j = 0; j < batter; j++) 
        {
            if (i >= ci[j] && maxRevenue[i - ci[j]] + pi[j] > maxRevenue[i]) 
            {
                maxRevenue[i] = maxRevenue[i - ci[j]] + pi[j];
                lastBatterSize[i] = ci[j];
            }
        }
    }

    printf("%d", maxRevenue[N]);

    // If the user enters "d", then output the optimal way to distribute the batter.
    if (distribution[0] == 'd') 
    {
        printf("\n");
        while (N > 0) 
        {
            printf("%d", lastBatterSize[N]);
            N -= lastBatterSize[N];
            if (N > 0) 
            {
                printf(" ");
            }
        }
        printf("\n");
    } 
    else 
    {
        printf("\n");
    }

    // Release the memory allocated.
    free(maxRevenue);
    free(lastBatterSize);
}

int main(int argc, char *argv[]) 
{

    FILE *file = fopen(argv[1], "r");

    // Read the batch of the batter.
    int N;
    fscanf(file, "%d", &N);

    // allocate the memory for pi and ci.
    int *pi = (int *)malloc(N * sizeof(int));
    int *ci = (int *)malloc(N * sizeof(int));

    // Read the price.
    for (int i = 0; i < N; i++) 
    {
        fscanf(file, "%d", &pi[i]);
    }

    // Read the size.
    for (int i = 0; i < N; i++) 
    {
        ci[i] = i + 1;
    }

    fclose(file);

    char *distribution = (argc == 3) ? argv[2] : "";

    // Calculate and find the max revenue. 
    findMaxRevenue(N, pi, ci, N, distribution);

    // Release the memory.
    free(pi);
    free(ci);

    return 0;
}
