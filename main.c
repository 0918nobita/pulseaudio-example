#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pulse/simple.h>
#include <pulse/error.h>

#define DATA_SIZE 1024

int main() {
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 48000;
    ss.channels = 1;

    int pa_errno;
    pa_simple *pa =
        pa_simple_new(
            NULL,
            "example",
            PA_STREAM_PLAYBACK,
            NULL,
            "play",
            &ss,
            NULL,
            NULL,
            &pa_errno
        );
    if (pa == NULL) {
        fprintf(stderr, "ERROR: Failed to connect pulseaudio server: %s\n", pa_strerror(pa_errno));
        return 1;
    }

    char data[DATA_SIZE];

    while (1) {
        for (int i = 0; i < DATA_SIZE; i++) {
            data[i] = rand();
            // data[i] = sin(i * 0.009) * 300;
            /*
            if (i < 512) {
                data[i] = (char)500;
            } else {
                data[i] = (char)70000;
            }
            */
        }

        int pa_result = pa_simple_write(pa, data, DATA_SIZE, &pa_errno);
        if (pa_result < 0) {
            fprintf(stderr, "ERROR: Failed to read data from pulseaudio: %s\n", pa_strerror(pa_errno));
            return 1;
        }
    }

    pa_simple_free(pa);
    return 0;
}
