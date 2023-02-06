#pragma once

#include "glm/glm.hpp"
#include <string>

class sphere
{
public:
	sphere();
	sphere(glm::vec3 thePos, float theRadius);
	glm::vec3 getPos();
	glm::vec3 getColor();
	float getRadius();
private:
	glm::vec3 pos = glm::vec3(10, -2, 3);
	glm::vec3 color = glm::vec3(255.0f, 0.0f, 0.0f);
	float radius = 1.0f;
	std::string material = "mirror";

};

