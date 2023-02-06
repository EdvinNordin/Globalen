#include "triangle.h"
#include "glm/gtx/intersect.hpp"

triangle::triangle() {};

void triangle::setTriangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 theColor)
{
	v0 = vert0;
	v1 = vert1;
	v2 = vert2;
    color = theColor;
}

glm::vec3 triangle::getv0() {
    return v0;
};

glm::vec3 triangle::getv1() {
    return v1;
};

glm::vec3 triangle::getv2() {
    return v2;
};

glm::vec3 triangle::getColor()
{
    return color;
}

glm::vec3 triangle::getNormal()
{
	// compute the plane's normal
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	// no need to normalize
	glm::vec3 N = glm::normalize(glm::cross(v0v1, v0v2)); // N
    return N;
}





