//
// Created by ziga on 01/01/2020.
//

#ifndef DIGITALNO_NACRTOVANJE_TEST_H
#define DIGITALNO_NACRTOVANJE_TEST_H

#include "drawing.h"

typedef struct{
    int x;
    int y;
    int size;
    RGBA color;

    int speedX;
    int speedY;

}SQUARE;

void testSquares(int numberOfSquares);

#endif //DIGITALNO_NACRTOVANJE_TEST_H
