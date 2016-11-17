#ifndef SATGE_H
#define STAGE_H
#define NB_STAGE 2

#include "globals.h"
#include "XInput.h"
#include "Melody.h"
void stage1();
void stage2();
void win();

bool doStage(int v);

extern void (*stageTab[NB_STAGE])();
#endif
