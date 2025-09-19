#include "triangle.h"
#include <algorithm>
#include "constants.h"

Triangle::Triangle(Vector c, Vector b, Vector a, Texture* t)
    : Plane(Vector(0,0,0), t, 0., 0., 0., 0., 0.),
      min_v(std::min({a.x, b.x, c.x}), std::min({a.y, b.y, c.y}), std::min({a.z, b.z, c.z})),
      max_v(std::max({a.x, b.x, c.x}), std::max({a.y, b.y, c.y}), std::max({a.z, b.z, c.z}))
{
   center = c;
   Vector righta = (b-c);
   textureX = righta.mag();
   right = righta/textureX;
   vect = right.cross(b-a).normalize();

   xsin = -right.z;
   if(xsin<-1.)xsin = -1;
   else if (xsin>1.)xsin=1.;
   yaw = asin(xsin);
   xcos = sqrt(1.-xsin*xsin);

   zcos = right.x/xcos;
   zsin = -right.y/xcos;
   if(zsin<-1.)zsin = -1;
   else if (zsin>1.)zsin=1.;
   if(zcos<-1.)zcos = -1;
   else if (zcos>1.)zcos=1.;
   roll = asin(zsin);

   ycos = vect.z/xcos;
   if(ycos<-1.)ycos = -1;
   else if (ycos>1.)ycos=1.;
   pitch = acos(ycos);
   ysin = sqrt(1-ycos*ycos);

   up.x = -xsin*ysin*zcos+ycos*zsin;
   up.y = ycos*zcos+xsin*ysin*zsin;
   up.z = -xcos*ysin;
   Vector temp = vect.cross(right);
   Vector np = solveScalers(right, up, vect, a-c);
   textureY = np.y;
   thirdX = np.x;

   d = -vect.dot(center);
}

double Triangle::getIntersection(Ray ray){
   // Bounding box start
   const auto overX = 1/ray.vector.x;
   const auto overY = 1/ray.vector.y;
   const auto overZ = 1/ray.vector.z;
   float tmin = (min_v.x - ray.point.x) * overX;
   float tmax = (max_v.x - ray.point.x) * overX;
   if (tmin > tmax) std::swap(tmin, tmax);

   float tymin = (min_v.y - ray.point.y) * overY;
   float tymax = (max_v.y - ray.point.y) * overY;
   if (tymin > tymax) std::swap(tymin, tymax);

   if ((tmin > tymax) || (tymin > tmax))
      return inf;

   if (tymin > tmin)
      tmin = tymin;
   if (tymax < tmax)
      tmax = tymax;

   float tzmin = (min_v.z - ray.point.z) * overZ;
   float tzmax = (max_v.z - ray.point.z) * overZ;
   if (tzmin > tzmax) std::swap(tzmin, tzmax);

   if ((tmin > tzmax) || (tzmin > tmax))
      return inf;
   // Bounding box end

   double time = Plane::getIntersection(ray);
   if(time==inf)
      return time;
   Vector dist = solveScalers(right, up, vect, ray.point+ray.vector*time-center);
   unsigned char tmp = (thirdX - dist.x) * textureY + (thirdX-textureX) * (dist.y - textureY) < 0.0;
   return((tmp!=(textureX * dist.y < 0.0)) || (tmp != (dist.x * textureY - thirdX * dist.y < 0.0)))?inf:time;
}

bool Triangle::getLightIntersection(Ray ray, double* fill){
   const double t = ray.vector.dot(vect);
   const double norm = vect.dot(ray.point)+d;
   const double r = -norm/t;
   if(r<=0. || r>=1.) return false;
   Vector dist = solveScalers(right, up, vect, ray.point+ray.vector*r-center);
   unsigned char tmp = (thirdX - dist.x) * textureY + (thirdX-textureX) * (dist.y - textureY) < 0.0;
   if ((tmp!=(textureX * dist.y < 0.0)) || (tmp != (dist.x * textureY - thirdX * dist.y < 0.0))) return false;

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