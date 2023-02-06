#pragma once
#include "glm/glm.hpp"

class ray
{
public:
	ray(glm::vec3 startPoint, glm::vec3 endPoint);

private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 dir;
	float length;
};

