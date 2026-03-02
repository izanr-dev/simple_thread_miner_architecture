#include "log.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int log_process(int read_fd) 
{
    pid_t ppid = getppid();
    char filename[256];
    
    snprintf(filename, sizeof(filename), "%d.log", ppid);

    int log_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (log_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    long int msg[2]; /* msg[0] = target, msg[1] = solution */
    ssize_t bytes_read;
    int round = 1;

    while ((bytes_read = read(read_fd, msg, sizeof(msg))) > 0) {
        if (bytes_read == sizeof(msg)) {
            dprintf(log_fd, "Id:             %d\n", round);
            dprintf(log_fd, "Winner:         %d\n", ppid);
            dprintf(log_fd, "Target:         %08ld\n", msg[0]);
            dprintf(log_fd, "Solution:       %08ld (validated)\n", msg[1]);
            dprintf(log_fd, "Votes:          %d/%d\n", round, round);
            dprintf(log_fd, "Wallets:        %d:%d\n", ppid, round);
            
            round++;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(log_fd);
        return EXIT_FAILURE;
    }

    close(log_fd);
    return EXIT_SUCCESS;
}