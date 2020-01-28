#ifndef SOUND_H_
#define SOUND_H_

#include <sys/types.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <math.h>
#include <stdint.h>

SDL_AudioSpec spec;

/* These are the audio card settings */
#define FREQ 44100
#define SAMPLES 8192 

/* This is basically an arbitrary number */
#define VOLUME 127.0

struct play_sound_args {
  uint8_t exists;
  int duration;
  int freq;
  float sinPos;
  float sinStep;
};

void open_audio();

void close_audio();

void play_sound(void* args);

#endif