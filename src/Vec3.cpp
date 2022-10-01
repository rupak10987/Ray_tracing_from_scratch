#include "Vec3.h"

Vec3::Vec3(double i,double j,double k)
{
    this->x=i;
    this->y=j;
    this->z=k;

}
Vec3::Vec3()
{
    this->x=0.00;
    this->y=0.00;
    this->z=0.00;
}
Vec3::~Vec3()
{

}
class Vec3 Vec3:: Direction_Vec(class Vec3 target,class Vec3 from)
{
    target.x-=from.x;
    target.y-=from.y;
    target.z-=from.z;
    return target;
};

double Vec3::DOT_PRODUCT(class Vec3* A,class Vec3* B)
{
return (A->x*B->x)+(A->y*B->y)+(A->z*B->z);
}
double Vec3::DOT_PRODUCT(class Vec3 A,class Vec3 B)
{
return (A.x*B.x)+(A.y*B.y)+(A.z*B.z);
}
