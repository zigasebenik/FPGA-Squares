//
// Created by ziga on 02/01/2020.
//

#ifndef DIGITALNO_NACRTOVANJE_RENDER_H
#define DIGITALNO_NACRTOVANJE_RENDER_H

int screenWidth;
int screenHeight;

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}RGBA;

typedef struct{
    void (*drawPixel)(int,int,RGBA*);
}RENDERER;

#endif //DIGITALNO_NACRTOVANJE_RENDER_H
