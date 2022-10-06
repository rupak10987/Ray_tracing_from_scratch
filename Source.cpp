#include<vector>
#include<math.h>
#include<graphics.h>
#include"Vec3.h"
#include"sphere.h"
#include"Col.h"
#include"Light_Source.h"
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
struct Shadow_elem
{
    class sphere* sph;
    double closest_TT;
};
std::vector<class sphere*> SPHERES;
std::vector<class Light_Source*> Lights;
class Col Back_ground_color(255,255,255);
class Vec3 O(-1,0,0);
double inf=100.0000000;
double view_port_W=1;
double view_port_H=1;
double View_port_D=1;

struct solution_T intersect_ray_sphere(class Vec3 O, class Vec3 D,class sphere* sph);
class Col TraceRay(class Vec3 O,class Vec3 D,double t_min,double t_max,int recursion_lim);
class Vec3 CanvasToViewport(int x, int y);
struct pixel screen_pos(int px,int py,int width,int height);
double calculate_light(class Vec3 N,class Vec3 P,class Vec3 V,double s);
struct Shadow_elem Closest_inersection(class Vec3 O,class Vec3 D,double t_min,double t_max);
class Vec3 reflected_ray(class Vec3 R,class Vec3 N);
int main()
{   //sphere1
    class Col col1(255,0,0);
    class Vec3 C1(0,0,3);
    class sphere *sph1=new sphere(1,C1,col1);
    sph1->reflective=0.9;
    SPHERES.push_back(sph1);
    delete &col1;//RELEASING memory
    delete &C1;//RELEASING memory
    //sphere2
    class Col col2(0,255,0);
    class Vec3 C2(2, 0, 4);
    class sphere *sph2=new sphere(1,C2,col2);
    sph2->specular=-1;//-1 for not specular
    SPHERES.push_back(sph2);
    delete &col2;//RELEASING memory
    delete &C2;//RELEASING memory
    //sphere3
    class Col col3(0,0,255);
    class Vec3 C3(-2, 0, 4);
    class sphere *sph3=new sphere(1,C3,col3);
    SPHERES.push_back(sph3);
    delete &col3;//RELEASING memory
    delete &C3;//RELEASING memory
    //sphere4
    class Col col4(100,100,100);
    class Vec3 C4(0, -5001, 0);
    class sphere *sph4=new sphere(5000,C4,col4);
    SPHERES.push_back(sph4);
    delete &col4;//RELEASING memory
    delete &C4;//RELEASING memory



    //adding lights to scene phong reflection model
    class Vec3 l(2, 1, 0);
    class Light_Source* point_l=new Light_Source(0.9,point,l);
    l.x=0;l.y=0;l.z=0;
    class Light_Source* ambient_l=new Light_Source(0.5,ambient,l);
    l.x=-5;l.y=4;l.z=4;
    class Light_Source* directional_l=new Light_Source(0.8,directional,l);
    Lights.push_back(point_l);
    Lights.push_back(ambient_l);
    Lights.push_back(directional_l);


//rendering part
    int gd = DETECT, gm, color;
    initgraph(&gd, &gm, (const char*)"");
    for(int i=-250;i<400;i++)//canvas X
    {
        for(int j=-249;j<250;j++)//canvas Y
        {
            class Vec3 D(CanvasToViewport(i,j));//in range of[-1to1], the point the ray intersects the viewport
            class Col col=TraceRay(O,D,(int)View_port_D,inf,3);//if the ray and any sphere collides this function will return the color of the sphere
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

struct Shadow_elem Closest_inersection(class Vec3 O,class Vec3 D,double t_min,double t_max)
{
    double closest_t=inf;
    class sphere *closest_sphere=nullptr;
    for(int i=0;i<4;i++)
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
   struct Shadow_elem shadow={closest_sphere,closest_t} ;
   return shadow;
};

class Col TraceRay(class Vec3 O,class Vec3 D,double t_min,double t_max,int recursion_lim)
{
    struct Shadow_elem my_shadow=Closest_inersection(O,D,t_min,t_max);
    double closest_t=my_shadow.closest_TT;
    class sphere *closest_sphere=my_shadow.sph;
    if(closest_sphere==nullptr)
    {
        return Back_ground_color;
    }
    class Vec3 P;
    P=O.addition_Vec(O,O.Scaler_Mul_Vec(closest_t,D));
    class Vec3 N;
    N=N.Direction_Vec(P,closest_sphere->Center);
    N=N.Normalized_Vec(N);
    class Vec3 cc;
    class Vec3 col_to_vec;
    col_to_vec.x=closest_sphere->sph_color.r;
    col_to_vec.y=closest_sphere->sph_color.g;
    col_to_vec.z=closest_sphere->sph_color.b;

    class Vec3 V;
    V=V.Direction_Vec(O,D);
    cc=N.Scaler_Mul_Vec(calculate_light(N,P,V,closest_sphere->specular),col_to_vec);
    class Col new_col;
    new_col.r=(int)ceil(cc.x);
    if(new_col.r>255)
        new_col.r=255;
    new_col.g=(int)ceil(cc.y);
    if(new_col.g>255)
        new_col.g=255;
    new_col.b=(int)ceil(cc.z);
    if(new_col.b>255)
        new_col.b=255;

    //reflections
    if(recursion_lim<=0)
    return new_col;
    class Col reflected_col;
    reflected_col=TraceRay(P,reflected_ray(D.Negate(D),N),0.001,inf,(recursion_lim-1));
    reflected_col=reflected_col.Mix(new_col,reflected_col,closest_sphere->reflective);
    if(reflected_col.r>255)
    reflected_col.r=255;
    if(reflected_col.g>255)
    reflected_col.g=255;
    if(reflected_col.b>255)
    reflected_col.b=255;
    return reflected_col;


}

class Vec3 reflected_ray(class Vec3 R,class Vec3 N)
{
    class Vec3 Rt;
    Rt=N.Direction_Vec(N.Scaler_Mul_Vec(2*N.DOT_PRODUCT(N,R),N),R);
    return Rt;
}
double calculate_light(class Vec3 N,class Vec3 P,class Vec3 V,double s)
{
double intense=0;
for(int i=0;i<3;i++)//point+ambient+directional
{
if(Lights[i]->type==ambient)
{
    intense+=Lights[i]->intensity;
}
else
{
    double t_max;
    class Vec3 L;
    if(Lights[i]->type==point)
    {
    L=L.Direction_Vec(Lights[i]->pos,P);
    t_max=1;
    }
    else
    {
    L=Lights[i]->pos;
    t_max=inf;
    }
    //shadow
    struct Shadow_elem m_shadow=Closest_inersection(P,L,0.001,t_max);
   if(m_shadow.sph!=nullptr)
    {
        continue;
    }

    double n_dot_l=L.DOT_PRODUCT(N,L);
    if(n_dot_l>0)
    {
        intense+=(Lights[i]->intensity * n_dot_l)/(sqrt(N.DOT_PRODUCT(N,N))*sqrt(L.DOT_PRODUCT(L,L)));
    }

    //specular calculatins

    if(s!=-1)
    {
        class Vec3 R;
        R=R.Direction_Vec(R.Scaler_Mul_Vec(2*R.DOT_PRODUCT(N,L),N),L);
        double r_dot_v=R.DOT_PRODUCT(R,V);
        intense+=Lights[i]->intensity*pow(r_dot_v/(sqrt(R.DOT_PRODUCT(R,R))*sqrt(R.DOT_PRODUCT(V,V))),s);
    }


}

}
return intense;
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


