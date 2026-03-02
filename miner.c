#include "miner.h"
#include "pow.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *mine_thread(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;

    for (long int i = args->start; i < args->end; i++)
    {
        if (*(args->found))
        {
            break;
        }

        if (pow_hash(i) == args->target)
        {
            *(args->solution) = i;
            *(args->found) = 1;
            break;
        }
    }
    return NULL;
}

int miner_process(int write_fd, char *target_ini, int rounds, int n_threads)
{
    long int current_target = atol(target_ini);
    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    ThreadArgs *t_args = malloc(n_threads * sizeof(ThreadArgs));

    if (!threads || !t_args)
    {
        return EXIT_FAILURE;
    }

    for (int r = 0; r < rounds; r++)
    {
        long int solution = -1;
        int found = 0;
        long int chunk_size = POW_LIMIT / n_threads;

        for (int i = 0; i < n_threads; i++)
        {
            t_args[i].target = current_target;
            t_args[i].start = i * chunk_size;
            t_args[i].end = (i == n_threads - 1) ? POW_LIMIT : (i + 1) * chunk_size;
            t_args[i].solution = &solution;
            t_args[i].found = &found;

            if (pthread_create(&threads[i], NULL, mine_thread, &t_args[i]) != 0)
            {
                free(threads);
                free(t_args);
                return EXIT_FAILURE;
            }
        }

        for (int i = 0; i < n_threads; i++)
        {
            pthread_join(threads[i], NULL);
        }

        if (solution == -1)
        {
            free(threads);
            free(t_args);
            return EXIT_FAILURE;
        }

        printf("Solution accepted: %08ld --> %08ld\n", current_target, solution);

        long int msg[2] = {current_target, solution};
        if (write(write_fd, msg, sizeof(msg)) == -1)
        {
            free(threads);
            free(t_args);
            return EXIT_FAILURE;
        }

        current_target = solution;
    }

    free(threads);
    free(t_args);
    return EXIT_SUCCESS;
}