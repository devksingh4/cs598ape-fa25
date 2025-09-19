#ifndef __LIGHT_H__
#define __LIGHT_H__
#include <vector>
#include "vector.h"
#include "camera.h"
#include "Textures/texture.h"
#include "Textures/colortexture.h"

class Light {
public:
    unsigned char* color;
    unsigned char* getColor(unsigned char a, unsigned char b, unsigned char c);
    Vector center;
    Light(const Vector& cente, unsigned char* colo);
};

class Shape;
struct LightNode {
    Light* data;
    LightNode* prev, *next;
};

struct ShapeNode {
    Shape* data;
    ShapeNode* prev, *next;
};

class Autonoma {
public:
   Camera camera;
   Texture* skybox;
   unsigned int depth;
   
   // OPTIM: Replaced linked lists with vectors
   std::vector<Shape*> shapes;
   std::vector<Light*> lights;
   
   Autonoma(const Camera& c);
   Autonoma(const Camera& c, Texture* tex);

   void addShape(Shape* s);
   void removeShape(Shape* s);
   void addLight(Light* l);
   void removeLight(Light* l);
};

void getLight(double* toFill, Autonoma* aut, Vector point, Vector norm, unsigned char r);

#endif