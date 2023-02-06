#include "ray.h"

ray::ray(glm::vec3 startPoint, glm::vec3 endPoint) {
	start = startPoint;
	end = endPoint;
	dir = glm::normalize(endPoint - startPoint);
	length = glm::distance(glm::vec3(endPoint), glm::vec3(startPoint));
}