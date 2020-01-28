#include "musicmaker/util.h"

#include <time.h>

void sleep_ms(long ms) {
    struct timespec tspec;

    tspec.tv_nsec = ((ms % 1000) * 1000000);
    tspec.tv_sec = (ms / 1000);

    nanosleep(&tspec, NULL);
}