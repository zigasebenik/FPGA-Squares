#include <stdbool.h>

#include "../include/test.h"
#include "../../SFMLfunctions/include/library.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


typedef struct{
    void (*renderRect)(int,int,int,int,RGBA*);
    void (*setBackgroundColor)(RGBA*);
}RENDERER;

square* randomizeSquares(int numberOfSquares)
{
    square *squares = (square*)malloc(sizeof(square)*numberOfSquares);

    srand(time(NULL));
    for(int i=0; i<numberOfSquares; i++)
    {
        RGBA color = {rand()%256, rand()%256, rand()%256, rand()%256};

        squares[i].color = color;
        squares[i].size = rand() % ((((int)fmin(screenWidth, screenHeight)/6) -5) +5);

        squares[i].x = rand()%(screenWidth - squares[i].size);
        squares[i].y = rand()%(screenHeight - squares[i].size);

        squares[i].speedX = rand()%5;
        squares[i].speedY = rand()%5;

        if(squares[i].speedX + squares[i].speedY == 0)
            if(rand()%2 == 0)
                squares[i].speedX = 1 + rand()%4;
            else
                squares[i].speedY = 1 + rand()%4;

    }
    return squares;
}


void moveSquares(RENDERER *renderer, square* squares, int n)
{
    square *tmp = squares;
    for(int i=0;i< n;i++)
    {
        if(tmp->x+tmp->speedX + tmp->size > screenWidth || tmp->x+tmp->speedX < 0 )
            tmp->speedX *= -1;

        if( tmp->y + tmp->speedY + tmp->size > screenHeight || tmp->y+tmp->speedY < 0)
            tmp->speedY *= -1;

        tmp->x += tmp->speedX;
        tmp->y += tmp->speedY;

        renderer->renderRect(tmp->x, tmp->y, tmp->size, tmp->size, &tmp->color);
        tmp++;
    }
}

void testSquares(int numberOfSquares)
{

    square *squares = randomizeSquares(numberOfSquares);

    RENDERER renderer = {&renderRect, &setFrameBufferColor};
    RGBA backgroundColor = {200, 200, 200, 255};

    bool run = true;

    long FPScounter = 0;
    long FPSupdate = 0;

    time_t startTime;
    time(&startTime);
    time_t measureTime;

    while (run == true)
    {

        renderer.setBackgroundColor(&backgroundColor);

        moveSquares(&renderer, squares, numberOfSquares);

        time(&measureTime);
        if(difftime(measureTime, startTime) >= 1)
        {
            time(&startTime);
            FPSupdate = FPScounter;
            FPScounter = 0;
        }

        char fpsString[20];
        sprintf(fpsString, "FPS:%d", FPSupdate);

        putText(5,5,fpsString,&backgroundColor);

        while(timeToSwapFrameBuffer() == false);

        FPScounter++;
        swapFrameBuffers();
        setActiveFrameBuffer(activeBuffer);
    }

}
