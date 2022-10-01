#include "Col.h"

Col::Col()
{
    this->r=255;
    this->g=0;
    this->b=200;
}
Col::Col(int r,int g,int b)
{
    this->r=r;
    this->g=g;
    this->b=b;
}
Col::~Col()
{
    //dtor
}
