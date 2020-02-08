#include "LightLineClass.h"
#include <iostream>
#include <math.h>
#define PI 3.14159265

LightLineClass::LightLineClass(int sX, int sY, int rayID, int numberOfRays) {
    startX = sX;
    startY = sY;

    finishX = sin(rayID*(360/numberOfRays)*(PI/180))*(1000) + startX;
    finishY = cos(rayID*(360/numberOfRays)*(PI/180))*(1000) + startY;

    length = sqrt((finishX-startX)*(finishX-startX)-(finishY-startY)*(finishY-startY));
}

int LightLineClass::getFinishX(void) {
    return finishX;
}
int LightLineClass::getFinishY(void) {
    return finishY;
}
int LightLineClass::getLength(void) {
    return length;
}

void LightLineClass::setFinishX(float fX) {
    finishX = fX;
}
void LightLineClass::setFinishY(float fY) {
    finishY = fY;
}
