#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <musicmaker/sound.h>

#define NR_CHANNELS 8

struct play_sound_args sound_args[NR_CHANNELS] = {0};
int nr_active_channels = 0;


struct play_sound_args *find_empty_channel() {
  int i;
  for(i = 0; i < NR_CHANNELS; i++) {
    if(sound_args[i].exists == 0) {
      return &sound_args[i];
    }
  }
  return NULL;
}

void clear_wave(void *data, uint8_t *stream, int len) {
  int i=0;
  for (i=0; i<len; i++) {
    stream[i] = (u_int8_t) 128;
  }
}

void generate_wave(void* data, u_int8_t *stream, int len, struct play_sound_args *psa) {
  int i=0;
  for (i=0; i<len; i++) {
  /* Just fill the stream with sine! */
    stream[i] += (u_int8_t) ((VOLUME/nr_active_channels) * sinf(psa->sinPos));
    psa->sinPos += psa->sinStep;
  }
}

void combine_waves(void *data, uint8_t *stream, int len) {
  clear_wave(data, stream, len);
  int i;
  for(i = 0; i < NR_CHANNELS; i++) {
    if(sound_args[i].exists) generate_wave(data, stream, len, &sound_args[i]);
  }
}

void open_audio() {
  /* Set up the requested settings */
  spec.freq = FREQ;
  spec.format = AUDIO_U8;
  spec.channels = 1;
  spec.samples = SAMPLES;
  spec.callback = (*combine_waves);
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

  struct play_sound_args *psa = (struct play_sound_args *) args;
  struct play_sound_args *target_psa = find_empty_channel();
  

  if(target_psa) {
    nr_active_channels++;
    printf("active channels : %d\n", nr_active_channels);
    *target_psa = *psa;

    int duration = target_psa->duration;
    long freq = target_psa->freq;
    long reqFreq = freq;

    target_psa->exists = 1;
    for(int i = 0 ; i < 5; i++) {
      sleep(duration);
      if(i % 2 == 0) {
        fprintf(stdout, "Playing freq: %ld\n", freq);
        target_psa->sinPos = 0;
        target_psa->sinStep = 2 * M_PI * reqFreq / FREQ;
      }
    }
    target_psa->exists = 0;
    nr_active_channels--;
  }
}