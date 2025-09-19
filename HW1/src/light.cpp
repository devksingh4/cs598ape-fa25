#include <algorithm>
#include <vector>

#include "camera.h"
#include "constants.h"
#include "light.h"
#include "shape.h"

Light::Light(const Vector& cente, unsigned char* colo) : center(cente) {
   color = colo;
}

unsigned char* Light::getColor(unsigned char a, unsigned char b,
                               unsigned char c) {
   unsigned char* r = (unsigned char*)malloc(sizeof(unsigned char) * 3);
   r[0] = a;
   r[1] = b;
   r[2] = c;
   return r;
}

Autonoma::Autonoma(const Camera& c) : camera(c) {
   depth = 10;
   skybox = BLACK;
}

Autonoma::Autonoma(const Camera& c, Texture* tex) : camera(c) {
   depth = 10;
   skybox = tex;
}

void Autonoma::addShape(Shape* r) { shapes.push_back(r); }

void Autonoma::removeShape(Shape* s) {
   auto it = std::find(shapes.begin(), shapes.end(), s);
   if (it != shapes.end()) {
      shapes.erase(it);
   }
}

void Autonoma::addLight(Light* r) { lights.push_back(r); }

void Autonoma::removeLight(Light* l) {
   auto it = std::find(lights.begin(), lights.end(), l);
   if (it != lights.end()) {
      lights.erase(it);
   }
}

void getLight(double* tColor, Autonoma* aut, Vector point, Vector norm,
              unsigned char flip) {
   tColor[0] = tColor[1] = tColor[2] = 0.;
   if (aut->lights.empty()) return;

   for (size_t lightIdx = 0; lightIdx < aut->lights.size(); ++lightIdx) {
      Light* light = aut->lights[lightIdx];

      double lightColor[3];
      lightColor[0] = light->color[0] * over255;
      lightColor[1] = light->color[1] * over255;
      lightColor[2] = light->color[2] * over255;

      Vector ra = light->center - point;
      bool hit = false;
      Ray shadowRay(point + ra * .01, ra);

      for (size_t shapeIdx = 0; shapeIdx < aut->shapes.size(); ++shapeIdx) {
         if (aut->shapes[shapeIdx]->getLightIntersection(shadowRay,
                                                         lightColor)) {
            hit = true;
            break;
         }
      }

      if (!hit) {
         double perc = (norm.dot(ra) / (ra.mag() * norm.mag()));
         if (flip && perc < 0) perc = -perc;

         if (perc > 0) {
            const auto percmul = perc * (lightColor[0]);  // OPTIM: do mul once
            tColor[0] += percmul;
            tColor[1] += percmul;
            tColor[2] += percmul;
            if (tColor[0] > 1.) tColor[0] = 1.;
            if (tColor[1] > 1.) tColor[1] = 1.;
            if (tColor[2] > 1.) tColor[2] = 1.;
         }
      }
   }
}