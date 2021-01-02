#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define R 20
#define C 20

enum boolean
{
    false,
    true
};
int matrix[R][C], arr[R];

void *sumMatrix(void *p)
{
    int k = *((int *)p);
    int i;
    for (i = 0; i < C; i++)
    {
        arr[k] += matrix[k][i];
    }
    return NULL;
}

void *createMatrix()
{
    int i, j, *p, tmp;
    int sum = 0;
    pthread_t th[R];
    enum boolean bool;
    bool = true;

    while (bool)
    {

        int count = 0, totalMatrix = 0;
        printf("Oluşturulacak matrix sayısı = ");
        scanf("%d", &totalMatrix);
        if (totalMatrix <= 0)
        {
            pthread_exit(NULL);
            bool = false;
            exit(-1);
        }
        while (count < totalMatrix)
        {

            for (i = 0; i < R; i++)
            {
                for (j = 0; j < C; j++)
                {
                    matrix[i][j] = rand() % 100;
                }
            }

            printf("\nOluşturulan Matris: \n");
            for (i = 0; i < R; i++)
            {
                for (j = 0; j < C; j++)
                    printf("%d ", matrix[i][j]);
                printf("\n");
            }

            for (i = 0; i < R; i++)
            {
                p = malloc(sizeof(int));
                *p = i;
                tmp = pthread_create(&th[i], NULL, sumMatrix, p);
                if (tmp != 0)
                {
                    printf("Thread oluşturma Hatas!");
                    exit(-1);
                }
            }

            for (i = 0; i < R; i++)
            {
                sum += arr[i];
            }

            printf("Toplam = %d\n", sum);
            printf("------------\n");
            count++;
        }
    }

    return NULL;
}

int main()
{
    int *p, i = 0;
    for (i = 0; i < R; i++)
    {
        p = malloc(sizeof(int));
        *p = i;
    }
    pthread_t thread_matrix_creator;
    pthread_t thread_matrix_sum;
    void *status;

    pthread_create(&thread_matrix_creator, NULL, createMatrix, NULL);
    pthread_create(&thread_matrix_sum, NULL, sumMatrix, p);

    if (pthread_join(thread_matrix_creator, &status) != 0)
    {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(thread_matrix_sum, &status) != 0)
    {
        perror("pthread_join");
        exit(1);
    }

    return 0;
}
