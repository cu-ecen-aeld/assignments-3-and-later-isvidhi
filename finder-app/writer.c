#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Setup syslog logging with LOG_USER facility
    openlog("writer", LOG_PID, LOG_USER);

    // Check if two arguments are provided
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Log the write operation at LOG_DEBUG level
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Open the file for writing. 
    // O_WRONLY: Open for writing only
    // O_CREAT: Create file if it doesn't exist
    // O_TRUNC: Truncate file to zero length if it exists
    // 0664: Permissions (rw-rw-r--)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file %s: %s", writefile, strerror(errno));
        perror("open");
        closelog();
        return 1;
    }

    // Write the string to the file
    ssize_t nr = write(fd, writestr, strlen(writestr));
    if (nr == -1) {
        syslog(LOG_ERR, "Error writing to file %s: %s", writefile, strerror(errno));
        perror("write");
        close(fd);
        closelog();
        return 1;
    } else if (nr != strlen(writestr)) {
        syslog(LOG_ERR, "Partial write to file %s", writefile);
        fprintf(stderr, "Error: Partial write to file\n");
        close(fd);
        closelog();
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error closing file %s: %s", writefile, strerror(errno));
        perror("close");
        closelog();
        return 1;
    }

    closelog();
    return 0;
}