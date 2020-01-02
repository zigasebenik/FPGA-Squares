//
// Created by ziga on 31/12/2019.
//

#ifndef DIGITALNO_NACRTOVANJE_DRAWING_H
#define DIGITALNO_NACRTOVANJE_DRAWING_H

#include <stdint.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}RGBA;

int screenWidth;
int screenHeight;

int stride;

uint8_t *frameBuffer1;
uint8_t *frameBuffer2;

uint8_t *drawingBuffer;
uint8_t *activeBuffer;

void initDrawing(int width, int height, int stride, int setReservedHeight);
void setFrameBufferColor(RGBA *color);
void renderRect(int startX, int startY, int rectWidth, int rectHeight, RGBA *color);
void swapFrameBuffers();
void putText(int textX, int textY, char *text, RGBA *backgroundColor);

#endif //DIGITALNO_NACRTOVANJE_DRAWING_H
