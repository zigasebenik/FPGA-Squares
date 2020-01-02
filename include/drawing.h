//
// Created by ziga on 31/12/2019.
//

#ifndef DIGITALNO_NACRTOVANJE_DRAWING_H
#define DIGITALNO_NACRTOVANJE_DRAWING_H

#include <stdint.h>
#include <stdbool.h>

#include "render.h"

bool currentlyDRAWING;
bool bufferAVAIABLE;

int stride;

uint8_t *drawingBuffer;
uint8_t *activeBuffer;

void initDrawing(int width, int height, int stride, int setReservedHeight);

uint8_t* swapFrameBuffers();

void putText(RENDERER *renderer, int textX, int textY, char *text, RGBA *backgroundColor);
void setFrameBufferColor(RENDERER *renderer, RGBA *color);
void renderRect(RENDERER *renderer, int startX, int startY, int rectWidth, int rectHeight, RGBA *color);

#endif //DIGITALNO_NACRTOVANJE_DRAWING_H
