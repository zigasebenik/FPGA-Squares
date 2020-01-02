//
// Created by ziga on 02/01/2020.
//

#include "render_sw.h"

void draw(int y, int x, RGBA *color)
{
    //res = ((src*alpha) + dst*(255-alpha)) / 256

    int dstAlpha = drawingBuffer[y * stride*4 + x*4 + 3];
    int dstR = drawingBuffer[y * stride*4 + x*4 + 0];
    int dstG = drawingBuffer[y * stride*4 + x*4 + 1];
    int dstB = drawingBuffer[y * stride*4 + x*4 + 2];

    int newR = ((color->r * color->a) + dstR * (255-color->a))/256;
    int newG = ((color->g * color->a) + dstG * (255-color->a))/256;
    int newB = ((color->b * color->a) + dstB * (255-color->a))/256;

    drawingBuffer[y * stride*4 + x*4 + 0] = newR;
    drawingBuffer[y * stride*4 + x*4 + 1] = newG;
    drawingBuffer[y * stride*4 + x*4 + 2] = newB;
    //drawingBuffer[y * stride*4 + x*4 + 3] = (color->a+drawingBuffer[y * stride*4 + x*4 + 3])/2;
    drawingBuffer[y * stride*4 + x*4 + 3] = 255;
}

RENDERER getRendererSw()
{
    RENDERER x = {&draw};

    return x;
}
