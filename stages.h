#ifndef SATGE_H
#define STAGE_H

#define START 1
#define NB_STAGE 2

#include "globals.h"
#include "XInput.h"
#include "Melody.h"

bool stage1();
bool stage2();
bool stage3();
void win();

bool doStage(int v);

extern bool (*stageTab[NB_STAGE])();
#endif
