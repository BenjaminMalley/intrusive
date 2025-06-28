#ifndef INTERFACE
#define INTERFACE

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

#define BUFFER_SIZE 8192

typedef struct logger {
    void (*info)(struct logger* self, char* message);
} logger;

typedef struct {
    logger lgr;
    char *buffer;
    size_t bufferPos;
} stdout_logger;

void log_stdout(logger* self, char* message) {
    stdout_logger *stdoutLogger = CONTAINER_OF(self, stdout_logger, lgr);
    size_t messageLen = strlen(message);
    if (stdoutLogger->bufferPos + messageLen > BUFFER_SIZE) {
        write(STDOUT_FILENO, stdoutLogger->buffer, stdoutLogger->bufferPos);
        stdoutLogger->bufferPos = 0;
    }
    memcpy(stdoutLogger->buffer + stdoutLogger->bufferPos, message, messageLen);
    stdoutLogger->bufferPos += messageLen;
}

#endif
