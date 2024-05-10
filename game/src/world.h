#pragma once
//#include "body.h" regular stuff
#include "raylib.h"
#include "body.h"
typedef struct ncBody ncBody;//forward declaration

extern ncBody* ncBodies;
extern int ncBodyCount;
extern Vector2 ncGravity;

ncBody* CreateBody(Vector2 position, float mass, ncBodyType bodytype);
void AddBody(ncBody* body);
void DestroyBody(ncBody* body);