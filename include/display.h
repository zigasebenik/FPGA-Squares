//
// Created by ziga on 02/01/2020.
//

#ifndef DIGITALNO_NACRTOVANJE_DISPLAY_H
#define DIGITALNO_NACRTOVANJE_DISPLAY_H

#include <stdint.h>

typedef struct{
    void (*initDisplay)(uint8_t *frameBufferC, int width, int height, int setStride);
    void (*setVSyncCallback)(uint8_t* (*swappingFrameBuffers)());

}DISPLAY;

#endif //DIGITALNO_NACRTOVANJE_DISPLAY_H
