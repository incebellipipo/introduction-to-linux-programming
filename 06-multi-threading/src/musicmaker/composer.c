#include <stdio.h>
#include <stdlib.h>
#include <musicmaker/sound.h>
#include <musicmaker/util.h>
#include <pthread.h>
#include <unistd.h>

void playNote(int freq, int duration) {
  pthread_t th;
  struct play_sound_args *note_args = malloc(1 * sizeof(struct play_sound_args));
  note_args->duration = duration;
  note_args->freq = freq;

  pthread_create(&th, NULL, (void *) &play_sound, note_args);
  pthread_detach(th);
  sleep_ms(duration);
}

void *back_instrument(void *d) {
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_C3S, 200);
  sleep_ms(200);
  playNote(NOTE_C3S, 200);
  sleep_ms(200);
  playNote(NOTE_C3S, 200);
  sleep_ms(200);
  playNote(NOTE_C3S, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_A2, 200);
  sleep_ms(200);
  playNote(NOTE_A2, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
  playNote(NOTE_D3, 200);
  sleep_ms(200);
}

void *main_instrument(void *d) {
  playNote(NOTE_A4, 400);

  playNote(NOTE_E4, 200);
  playNote(NOTE_F4, 200);
  playNote(NOTE_G4, 400);

  playNote(NOTE_F4, 200);
  playNote(NOTE_E4, 200);
  playNote(NOTE_D4, 400);

  playNote(NOTE_D4, 200);
  playNote(NOTE_F4, 200);
  playNote(NOTE_A4, 400);

  playNote(NOTE_G4, 200);
  playNote(NOTE_F4, 200);
  playNote(NOTE_E4, 600);

  playNote(NOTE_F4, 200);
  playNote(NOTE_G4, 400);
  playNote(NOTE_A4, 400);

  playNote(NOTE_F4, 400);

  playNote(NOTE_D4, 400);

  playNote(NOTE_D4, 400);
  
  sleep_ms(600);


}

int main(int argc, char** argv) {
  int duration = 1;
  pthread_t main_instr;
  pthread_t back_instr;

  open_audio();

  pthread_create(&main_instr, NULL, main_instrument, NULL);
  pthread_detach(main_instr);

  pthread_create(&back_instr, NULL, back_instrument, NULL);
  pthread_detach(back_instr);

  sleep(10);
  close_audio();
  return 0;
}