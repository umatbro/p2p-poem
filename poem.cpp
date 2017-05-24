#include "poem.h"

char poem[VERSE_NUM + 1][LINE_LENGTH] = {0};
int verses_found = 0;

void init_poem(){
  memset(poem, 0, sizeof(poem));
  strncpy(poem[6], "gdyś jej ścieżki powycinał żelaznymi łzami.", sizeof(poem[6]));
  verses_found = 1;
}

void show_poem(){
  printf("------------------------------------\n");
  printf("Znalezionych wersów: %d\n", verses_found);
  printf("------------------------------------\n");
  for(int i = 1; i < sizeof(poem)/LINE_LENGTH; i++){
    if(strlen(poem[i]) != 0)  printf("%d. %s\n", i, poem[i]);
  }
  printf("------------------------------------\n");
}

void add_verse(int verse_number, char* verse){
  memset(poem[verse_number], 0, sizeof(poem[verse_number])); // najpierw wyczyść wers
  // potem skopiuj treść wersu do miejsca w tablicy
  strncpy(poem[verse_number], verse, sizeof(poem[verse_number]));
  verses_found++;
}
