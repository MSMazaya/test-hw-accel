#pragma once

#include <psp_api.h>
#include <uart.h>

void initPlatform();
void startTimer();
void endTimer();
void printTimerResult(const char* title);
