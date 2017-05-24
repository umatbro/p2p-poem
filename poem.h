#pragma once
#ifndef _POEM_H
#define _POEM_H
#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 200 // max ilość znaków w wierszu
#define VERSE_NUM 150 // ilosć wierszy w tablicy

extern char poem[VERSE_NUM + 1][LINE_LENGTH];
extern int verses_found;

// wynikowa tablica z wierszem
void show_poem();
void init_poem();
void add_verse(int, char*);

#endif /* end of include guard:
 */
