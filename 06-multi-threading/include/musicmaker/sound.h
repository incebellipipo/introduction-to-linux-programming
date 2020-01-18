#ifndef SOUND_H_
#define SOUND_H_

#include <sys/types.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <math.h>

SDL_AudioSpec spec;

/* These are in charge of maintaining our sine function */
float sinPos;
float sinStep;

/* These are the audio card settings */
#define FREQ 44100
#define SAMPLES 8192 

/* This is basically an arbitrary number */
#define VOLUME 127.0

struct play_sound_args {
  int duration;
  int freq;
};

void generate_wave(void* data, u_int8_t *stream, int len);

void open_audio();

void close_audio();

void play_sound(void* args);

#endif