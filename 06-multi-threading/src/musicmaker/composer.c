#include <stdio.h>
#include <stdlib.h>
#include <musicmaker/sound.h>
#include <pthread.h>

int main(int argc, char** argv) {

  pthread_t note_A;
  pthread_t note_Cs;

  struct play_sound_args node_a_args;
  node_a_args.duration=2;
  node_a_args.freq=440;
  
  struct play_sound_args node_b_args;
  node_b_args.duration=2;
  node_b_args.freq=540;

  pthread_create(&note_A, NULL, (void*)&play_sound, (struct play_sound_args*)&node_a_args);
  // pthread_create(&note_Cs, NULL, (void*)&play_sound, (struct play_sound_args*)&node_b_args);
  // pthread_create(&note_Cs, NULL, *play_sound, 2, 440);
  pthread_join(note_A, NULL);
  // pthread_join(note_Cs, NULL);
  // play_sound(2, 440);
  return 0;
}