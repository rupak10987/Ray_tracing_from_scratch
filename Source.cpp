#include<iostream>
#include<vector>
#include<math.h>
#include<graphics.h>
#include"Vec3.h"
#include"sphere.h"
#include"Col.h"
using namespace std;
struct solution_T
{
    double t1;
    double t2;
};
struct pixel
{
    int X;
    int Y;
};
vector<class sphere*> SPHERES;
class Col Back_ground_color(200,200,200);
class Vec3 O(0,0,0);
double inf=100.0000000;
double view_port_W=1;
double view_port_H=1;
double View_port_D=1;

struct solution_T intersect_ray_sphere(class Vec3 O, class Vec3 D,class sphere* sph);
class Col TraceRay(class Vec3 O,class Vec3 D,double t_min,double t_max);
class Vec3 CanvasToViewport(int x, int y);
struct pixel screen_pos(int px,int py,int width,int height);
int main()
{   //sphere1
    class Col col1(255,100,100);
    class Vec3 C1(0,0,3);
    class sphere *sph1=new sphere(1,C1,col1);
    SPHERES.push_back(sph1);
    delete &col1;//RELEASING memory
    delete &C1;//RELEASING memory
    //sphere2
    class Col col2(100,255,100);
    class Vec3 C2(2, 0, 4);
    class sphere *sph2=new sphere(1,C2,col2);
    SPHERES.push_back(sph2);
    delete &col2;//RELEASING memory
    delete &C2;//RELEASING memory
    //sphere3
    class Col col3(100,255,255);
    class Vec3 C3(-2, 0, 4);
    class sphere *sph3=new sphere(1,C3,col3);
    SPHERES.push_back(sph3);
    delete &col3;//RELEASING memory
    delete &C3;//RELEASING memory

//rendering part
    int gd = DETECT, gm, color;
    initgraph(&gd, &gm, (const char*)"");
    for(int i=-250;i<400;i++)//canvas X
    {
        for(int j=-249;j<250;j++)//canvas Y
        {
            class Vec3 D(CanvasToViewport(i,j));//in range of[-1to1], the point the ray intersects the viewport
            class Col col=TraceRay(O,D,(int)View_port_D,inf);//if the ray and any sphere collides this function will return the color of the sphere
            struct pixel p=screen_pos(i,j,500,500);//canvas pos
            putpixel(p.X, p.Y, COLOR(col.r,col.g,col.b));
        }
    }
    getch();
    closegraph();


    return 0;

}
struct solution_T intersect_ray_sphere(class Vec3 O, class Vec3 D,class sphere* sph)
{
solution_T t={inf,inf};
double r=sph->Radious;
class Vec3 CO(O.Direction_Vec(O,sph->Center));
double a=D.DOT_PRODUCT(D,D);
double b=2*CO.DOT_PRODUCT(CO, D);
double c=CO.DOT_PRODUCT(CO, CO) - r*r;
double discriminant = b*b - 4*a*c;
if(discriminant<0)
{
return t;
}
t.t1 = (-b +sqrt(discriminant)) / (2*a);
t.t2 = (-b -sqrt(discriminant)) / (2*a);
return t;
}
class Col TraceRay(class Vec3 O,class Vec3 D,double t_min,double t_max)
{
    double closest_t=inf;
    class sphere *closest_sphere=nullptr;
    for(int i=0;i<3;i++)
    {
        solution_T t=intersect_ray_sphere(O,D,SPHERES[i]);
        if (t.t1>t_min && t.t1<t_max && t.t1<closest_t)
        {
            closest_t=t.t1;
            closest_sphere=SPHERES[i];
        }
        if (t.t2>t_min && t.t2<t_max && t.t2<closest_t)
        {
            closest_t=t.t2;
            closest_sphere=SPHERES[i];
        }
    }
    if(closest_sphere==nullptr)
    {
        return Back_ground_color;
    }
    return closest_sphere->sph_color;

}
class Vec3 CanvasToViewport(int x, int y)
{
    class Vec3 view((x*view_port_W)/500, (y*view_port_H)/500, 1);
    return view;

}
struct pixel screen_pos(int px,int py,int width,int height)
{
    struct pixel p={(int)(px+(width/2)),(int)((height/2)-py)};
    return p;

}

