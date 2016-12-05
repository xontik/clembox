#ifndef SATGE_H
#define STAGE_H
#define NB_STAGE 2

#include "globals.h"
#include "XInput.h"
#include "Melody.h"
bool stage1();
bool stage2();
void win();

bool doStage(int v);

extern bool (*stageTab[NB_STAGE])();
#endif
