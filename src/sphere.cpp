#include "sphere.h"

sphere::sphere(double rad,class Vec3 center,class Col col)
{
    //ctor
    this->Radious=rad;
    this->Center.x=center.x;
    this->Center.y=center.y;
    this->Center.z=center.z;
    this->sph_color.r=col.r;
    this->sph_color.g=col.g;
    this->sph_color.b=col.b;
    this->specular=100;
}

sphere::~sphere()
{
    //dtor
}
