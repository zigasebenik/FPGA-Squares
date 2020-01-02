//
// Created by ziga on 31/12/2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <display.h>

#include "drawing.h"
#include "font_bmp_raw_32_bitDepth.h"
#include "library.h"

uint8_t *frameBuffer1;
uint8_t *frameBuffer2;


void putText(RENDERER *renderer, int textX, int textY, char *text, RGBA *backgroundColor)
{
    char *tmp = text;

    int index = 0;

    int newRow = 0;
    bool newRowChanged = false;

    while(*tmp != '\0')
    {
        char c = *tmp;
        int startX = 0;
        int startY = 0;

        int charWidth = 32;
        int charHeight = 32;

        if(c >= '0' && c <= '9')
        {
            startY = 95;
            startX = charWidth * (c-'0')-1;
        }
        else if(c >= 'A' && c <= 'O')
        {
            startY = 126;
            startX = charWidth * (c-'0') -1;
        }
        else if(c >= 'P' && c <= 'Z')
        {
            startY = 159;
            startX = charWidth * (c-'0')-1;
        }
        else if(c >= 'a' && c <= 'o')
        {
            startY = 192;
            startX = charWidth * (c-'0')-1;
        }
        else if(c >= 'p' && c <= 'z')
        {
            startY = 225;
            startX = charWidth * (c-'0')-1;
        }
        else if(c == ':')
        {
            startY = 93;
            startX = 325;
        }
        else
        {
            charWidth = 0;
            charHeight = 0;
        }
        //printf("%d\n", sizeof(font_bmp_raw_map)/ sizeof(uint8_t));

        int drawX = startX+charWidth;
        int drawY = startY+charHeight;

        for (int y = drawY; y >= drawY-charHeight; y--)
        {
            for (int x = drawX; x >= drawX-charWidth; x--)
            {

                uint8_t fontR = font_bmp_raw_map[54+ (fontData.h-y-1) * fontData.w*4 + x*4 + 0];
                uint8_t fontG = font_bmp_raw_map[54+ (fontData.h-y-1) * fontData.w*4 + x*4 + 1];
                uint8_t fontB = font_bmp_raw_map[54+ (fontData.h-y-1) * fontData.w*4 + x*4 + 2];

                RGBA pixelColor = {fontR, fontG, fontB, 255};
                if(fontR == 0 && fontG == 0 && fontB == 0)
                    pixelColor.a = 0;

                int coordY = (textY + abs(y-startY));
                int coordX = (textX + abs(x-startX)) + index*charWidth;

                if(coordX >= screenWidth && newRowChanged==false)
                {
                    index = 0;
                    newRow++;
                    newRowChanged = true;
                }

                if(newRowChanged == true)
                {
                    coordX = (textX + abs(x-startX))+ index*charWidth;
                    coordY = charHeight*(newRow)+(textY + abs(y-startY));
                }

                renderer->drawPixel(coordY, coordX, &pixelColor);
            }
        }

        index++;
        tmp++;
    }
}

void setFrameBufferColor(RENDERER *renderer, RGBA *color)
{
    for(int i=0;i<screenHeight;i++)
    {
        for(int j=0;j<screenWidth;j++)
        {
            renderer->drawPixel(i, j, color);
        }
    }
}

void renderRect(RENDERER *renderer, int startX, int startY, int rectWidth, int rectHeight, RGBA *color)
{
    int x2 = rectWidth + startX;
    int y2 = rectHeight + startY;

    if(startX >= 0 && startY >= 0 && x2 <= screenWidth && y2 <= screenHeight)
        for(int y = startY; y < y2; y++)
        {
            for(int x = startX; x < x2; x++)
            {
                renderer->drawPixel(y, x, color);
            }
        }
    else
        printf("ERROR-> X1: %d, X2: %d <--> Y1: %d, Y2: %d\n",startX,x2,startY,y2);
}

void initDrawing(int width, int height, int stride, int setReservedHeight)
{
    if(width > stride)
    {
        printf("zajebao si stride:\nPREMAJHEN\n");
        return ;
    }

    if(height > setReservedHeight)
    {
        printf("zajebao si reservedHeight:\nPREMAJHNA\n");
        return ;
    }

    stride = stride;
    screenWidth = width;
    screenHeight = height;
    frameBuffer1 = (unsigned char*)malloc(sizeof(unsigned char) * setReservedHeight * stride * 4);
    frameBuffer2 = (unsigned char*)malloc(sizeof(unsigned char) * setReservedHeight * stride * 4);

    drawingBuffer = frameBuffer1;
    activeBuffer = frameBuffer2;
    bufferAVAIABLE = false;

    initFrameBufferSFML(activeBuffer, width, height, stride);
}

uint8_t* swapFrameBuffers()
{
    if (drawingBuffer == frameBuffer1)
    {
        activeBuffer = frameBuffer1;
        drawingBuffer = frameBuffer2;
    }
    else
    {
        activeBuffer = frameBuffer2;
        drawingBuffer = frameBuffer1;
    }

    return activeBuffer;
}