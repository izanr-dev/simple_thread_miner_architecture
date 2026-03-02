/**
 * @file miner.h
 * @author Izan Roble
 * @author Javier Ruiz
 * @brief Header of the functions for miner execution
 */

#ifndef MINER_H
#define MINER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    long int target;
    long int start;
    long int end;
    long int *solution;
    int *found;
} ThreadArgs;

/**
 * @brief Logic for every thread
 */
void *mine_thread(void *arg);

/**
 * @brief Logic for the miner
 */
int miner_process(int write_fd, char *target_ini, int rounds, int n_threads);

#endif