#ifndef VEC3_H
#define VEC3_H
#include<iostream>
using namespace std;

class Vec3
{
    public:
        double x;
        double y;
        double z;
        Vec3(double i,double j,double k);
        Vec3();
        virtual ~Vec3();
        double DOT_PRODUCT(class Vec3* A,class Vec3* B);
        double DOT_PRODUCT(class Vec3 A,class Vec3 B);
        class Vec3 Direction_Vec(class Vec3 target,class Vec3 from);


    protected:

    private:

};

#endif // VEC3_H
