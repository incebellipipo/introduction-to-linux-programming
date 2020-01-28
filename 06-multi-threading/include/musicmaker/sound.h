#ifndef SOUND_H_
#define SOUND_H_

#include <sys/types.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <math.h>
#include <stdint.h>

#define NOTE_C0  16
#define NOTE_C0S 17
#define NOTE_D0  18
#define NOTE_D0S 19
#define NOTE_E0  20
#define NOTE_F0  21
#define NOTE_F0S 23
#define NOTE_G0  24
#define NOTE_G0S 26
#define NOTE_A0  27
#define NOTE_A0S 29
#define NOTE_B0  30
#define NOTE_C1  32
#define NOTE_C1S 34
#define NOTE_D1  36
#define NOTE_D1S 38
#define NOTE_E1  41
#define NOTE_F1  43
#define NOTE_F1S 46
#define NOTE_G1  49
#define NOTE_G1S 52
#define NOTE_A1  55
#define NOTE_A1S 58
#define NOTE_B1  61
#define NOTE_C2  65
#define NOTE_C2S 69
#define NOTE_D2  73
#define NOTE_D2S 77
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_F2S 92
#define NOTE_G2  98
#define NOTE_G2S 103
#define NOTE_A2  110
#define NOTE_A2S 116
#define NOTE_B2  123
#define NOTE_C3  130
#define NOTE_C3S 138
#define NOTE_D3  146
#define NOTE_D3S 155
#define NOTE_E3  164
#define NOTE_F3  174
#define NOTE_F3S 185
#define NOTE_G3  196
#define NOTE_G3S 207
#define NOTE_A3  220
#define NOTE_A3S 233
#define NOTE_B3  246
#define NOTE_C4  261
#define NOTE_C4S 277
#define NOTE_D4  293
#define NOTE_D4S 311
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_F4S 370
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_A4S 466
#define NOTE_B4  493
#define NOTE_C5  523
#define NOTE_C5S 554
#define NOTE_D5  587
#define NOTE_D5S 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_F5S 739
#define NOTE_G5  783
#define NOTE_G5S 830
#define NOTE_A5  880
#define NOTE_A5S 932
#define NOTE_B5  987
#define NOTE_C6  1046
#define NOTE_C6S 1108
#define NOTE_D6  1174
#define NOTE_D6S 1244
#define NOTE_E6  1318
#define NOTE_F6  1396
#define NOTE_F6S 1479
#define NOTE_G6  1567



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