#include <stdbool.h>

#include "test.h"
#include "library.h"
#include "render_sw.h"
#include "display.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>



SQUARE* randomizeSquares(int numberOfSquares)
{

    SQUARE *squares = (SQUARE*)malloc(sizeof(SQUARE) * numberOfSquares);

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


void moveSquares(RENDERER *renderer, SQUARE* squares, int n)
{
    SQUARE *tmp = squares;
    for(int i=0;i< n;i++)
    {
        if(tmp->x+tmp->speedX + tmp->size > screenWidth || tmp->x+tmp->speedX < 0 )
            tmp->speedX *= -1;

        if( tmp->y + tmp->speedY + tmp->size > screenHeight || tmp->y+tmp->speedY < 0)
            tmp->speedY *= -1;

        tmp->x += tmp->speedX;
        tmp->y += tmp->speedY;

        renderRect(renderer, tmp->x, tmp->y, tmp->size, tmp->size, &tmp->color);
        tmp++;
    }
}

void testSquares(int numberOfSquares)
{


    SQUARE *squares = randomizeSquares(numberOfSquares);
    RENDERER renderer = getRendererSw();

    RGBA backgroundColor = {200, 200, 200, 255};

    bool run = true;

    long FPScounter = 0;

    time_t startTime;
    time(&startTime);
    time_t measureTime;


    char fpsString[20];

    while (run == true)
    {

        currentlyDRAWING = true;
        setFrameBufferColor(&renderer, &backgroundColor);
        moveSquares(&renderer, squares, numberOfSquares);

        time(&measureTime);
        if(difftime(measureTime, startTime) >= 1)
        {
            sprintf(fpsString, "FPS:%d", FPScounter);
            time(&startTime);
            FPScounter = 0;
        }

        putText(&renderer, 5, 5, fpsString, &backgroundColor);
        currentlyDRAWING = false;

        while(timeToSwapFrameBuffer() == false);

        FPScounter++;
        swapFrameBuffers();
        setActiveFrameBuffer(activeBuffer);
    }

}
