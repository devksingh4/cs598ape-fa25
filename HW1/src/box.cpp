#include "box.h"
#include "constants.h"

Box::Box(const Vector &c, Texture* t, double ya, double pi, double ro, double tx, double ty):Plane(c, t, ya, pi, ro, tx, ty){}
Box::Box(const Vector &c, Texture* t, double ya, double pi, double ro, double tx):Plane(c, t, ya, pi, ro, tx,tx){}

double Box::getIntersection(Ray ray){
   double time = Plane::getIntersection(ray);
   Vector dist = solveScalers(right, up, vect, ray.point+ray.vector*time-center);
   if(time==inf) 
      return time;
   return ( ((dist.x>=0)?dist.x:-dist.x)>textureX * over2 || ((dist.y>=0)?dist.y:-dist.y)>textureY * over2 )?inf:time;
}

bool Box::getLightIntersection(Ray ray, double* fill){
   const double t = ray.vector.dot(vect);
   if (t == 0) return false;
   const double norm = vect.dot(ray.point)+d;
   const double r = -norm/t;
   if(r<=0. || r>=1.) return false;
   Vector dist = solveScalers(right, up, vect, ray.point+ray.vector*r-center);
   if( ((dist.x>=0)?dist.x:-dist.x)>textureX * over2|| ((dist.y>=0)?dist.y:-dist.y)>textureY * over2 ) return false;

   if(texture->opacity>1-1E-6) return true;   
   unsigned char temp[4];
   double amb, op, ref;
   texture->getColor(temp, &amb, &op, &ref,fix(dist.x/textureX-.5), fix(dist.y/textureY-.5));
   if(op>1-1E-6) return true;
   fill[0]*=temp[0] * over255;
   fill[1]*=temp[1] * over255;
   fill[2]*=temp[2] * over255;
   return false;
}