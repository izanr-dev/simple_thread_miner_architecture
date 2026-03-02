/**
 * @file log.h
 * @author Izan Roble
 * @author Javier Ruiz
 * @brief Header of the functions for logger execution 
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/** 
 * @brief Logic for the logger
 */
int log_process(int read_fd); 

#endif