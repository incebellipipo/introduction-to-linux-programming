#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <musicmaker/sound.h>

void generate_wave(void* data, Uint8 *stream, int len) {
int i=0;
for (i=0; i<len; i++) {
/* Just fill the stream with sine! */
stream[i] = (Uint8) (VOLUME * sinf(sinPos))+127;
sinPos += sinStep;
}
}
void play_sound(void* args) {
int duration = ((struct play_sound_args *) args)->duration;
long freq = ((struct play_sound_args *) args)->freq;
printf("duration: %d, freq: %ld", duration, freq);
/* This will hold our data */
SDL_AudioSpec spec;
/* This will hold the requested frequency */
long reqFreq = freq;
/* This is the duration to hold the note for */

/* Set up the requested settings */
spec.freq = FREQ;
spec.format = AUDIO_U8;
spec.channels = 1;
spec.samples = SAMPLES;
spec.callback = (*generate_wave);
spec.userdata = NULL;

/* Open the audio channel */
if (SDL_OpenAudio(&spec, NULL) < 0) { 
/* FAIL! */
fprintf(stderr, "Failed to open audio: %s \n", SDL_GetError());
exit(1); 
} 

/* Initialize the position of our sine wave */
sinPos = 0;
/* Calculate the step of our sin wave */
sinStep = 2 * M_PI * reqFreq / FREQ;

/* Now, run this thing */
SDL_PauseAudio(0); 
/* Delay for the requested number of seconds */
sleep(duration);
/* Then turn it off again */
SDL_PauseAudio(1);

/* Close audio channel */
SDL_CloseAudio();

}