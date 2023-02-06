#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"
#include "glm/gtx/normal.hpp"
#include <string>
class triangle
{
public:
	triangle();

	void setTriangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 theColor);
	//void setName(float name);
	glm::vec3 getv0();
	glm::vec3 getv1();
	glm::vec3 getv2();
	glm::vec3 getColor();
	glm::vec3 getNormal();
	float getName();
private:
	glm::vec3 v0, v1, v2;
	glm::vec3 color;
	glm::vec3 normal;
	std::string material = "lambertian";
};

