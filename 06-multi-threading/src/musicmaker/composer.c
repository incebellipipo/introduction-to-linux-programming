#include <stdio.h>
#include <stdlib.h>
#include <musicmaker/sound.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char** argv) {

  pthread_t note_A;
  pthread_t note_Cs;
  int duration = 1;
  struct play_sound_args node_a_args;
  node_a_args.duration=duration;
  node_a_args.freq=440;
  
  struct play_sound_args node_b_args;
  node_b_args.duration=duration;
  node_b_args.freq=580;

  open_audio();

  pthread_create(&note_A, NULL, (void*)&play_sound, (struct play_sound_args*)&node_a_args);
  pthread_detach(note_A);
  sleep(duration);
  pthread_create(&note_Cs, NULL, (void*)&play_sound, (struct play_sound_args*)&node_b_args);
  pthread_detach(note_Cs);
  // wait a bit, what else you gotta do?
  sleep(duration * 5 + duration);
  close_audio();
  return 0;
}