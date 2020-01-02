#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    void initFrameBufferSFML(uint8_t *frameBufferC, int width, int height, int setStride);
    bool timeToSwapFrameBuffer();
    void setActiveFrameBuffer(uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif //LIBRARY_H
