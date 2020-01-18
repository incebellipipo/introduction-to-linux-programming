#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <musicmaker/sound.h>

void generate_wave(void* data, u_int8_t *stream, int len) {
  int i=0;
  for (i=0; i<len; i++) {
  /* Just fill the stream with sine! */
    stream[i] = (u_int8_t) (VOLUME * sinf(sinPos))+127;
    sinPos += sinStep;
  }
}

void open_audio() {
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
  SDL_PauseAudio(0);
}

void close_audio() {
  SDL_PauseAudio(1);
  SDL_CloseAudio();
}

void play_sound(void* args) {
  int duration = ((struct play_sound_args *) args)->duration;
  long freq = ((struct play_sound_args *) args)->freq;
  long reqFreq = freq;

  for(int i = 0 ; i < 5; i++) {
    sleep(duration);
    if(i % 2 == 0) {
      fprintf(stdout, "Playing freq: %ld\n", freq);
      sinPos = 0;
      sinStep = 2 * M_PI * reqFreq / FREQ;
    }
  }
}