#pragma once
//#define GLM_ENABLE_EXPERIMENTAL
#include "triangle.h"
#include "sphere.h"
#include "glm/gtx/normal.hpp"
#include <iostream>
class scene
{
public:
	
	scene();
	void setScene();
	triangle getTriangle(int x);
	sphere getSphere();

private:
	triangle* triangles = new triangle[30];
	sphere theSphere;
};

