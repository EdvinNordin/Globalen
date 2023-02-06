#include "sphere.h"
sphere::sphere() { };

sphere::sphere(glm::vec3 thePos, float theRadius) {
	pos = thePos;
	radius = theRadius;
};

glm::vec3 sphere::getPos() {
	return glm::vec3(pos);
}

glm::vec3 sphere::getColor()
{
	return glm::vec3(color);
}

float sphere::getRadius() {
	return radius;
}