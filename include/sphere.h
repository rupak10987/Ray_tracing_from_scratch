#ifndef SPHERE_H
#define SPHERE_H
#include"Vec3.h"
#include"Col.h"
class sphere
{
    public:
        sphere(double rad,class Vec3 center,class Col col);
        virtual ~sphere();
        double Radious;
        class Vec3 Center;
        class Col sph_color;
        double specular;
    protected:

    private:
};

#endif // SPHERE_H
