/**
 * @brief Punto de entrada al programa
 * @file main.c
 * @author Izan Robles
 * @author Javier Ruiz
 */

# include "miner.h"
# include "log.h"

/*----------------------------------------------------------*/
/*-------------------------- MAIN --------------------------*/
/*----------------------------------------------------------*/

int main (int argc, char* argv[])
{
    pid_t pid = 0;
    int fd[2];
    
    /*Control de formato de entrada*/
    if (argc != 4) 
    {
        printf("USE: ./MINER <TARGET_INI> <ROUNDS> <NO_THREADS>");
        return EXIT_FAILURE;
    }

    /*Tuberia y Fork*/
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    
    /*Llamadas -> Hijo*/
    if (pid == 0) 
    {
        int status = 0;
        close(fd[1]);
        
        status = log_process(fd[0]);
 
        close(fd[0]);
        exit(status);
    }

    /*Llamadas -> Padre*/
    else 
    {
        int log_status;
        int miner_status;
        close(fd[0]);
        
        miner_status = miner_process(fd[1], argv[1], atoi(argv[2]), atoi(argv[3]));
        close(fd[1]);

        wait(&log_status);
        
        if (WIFEXITED(log_status))
        {
            printf("\nLogger exited with status %d", WEXITSTATUS(log_status));
        }
        else if (WIFSIGNALED(log_status))
        {
            printf("\nLogger terminated unexpectedly");
        }

        if (miner_status == EXIT_SUCCESS)
        {
            printf("\nMiner exited with status %d", EXIT_SUCCESS);
        }
        else if (miner_status == EXIT_FAILURE)
        {
            printf("\nMiner exited with status %d", EXIT_FAILURE);
        }
    }
}


