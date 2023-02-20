#pragma once

#include "scene.h"
#include "sphere.h"
#include "ray.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include <cmath>;
//4194304 
const int dim = 800;
//4194304
const float pi = 3.1415926535897f;
class camera
{
public:
	camera();
	void setPlane(scene &myScene);
	void makeImage();
	glm::vec3 getColorOfBounces(triangle &myTriangle, bool &isSphere, scene &myScene, glm::vec3 dir, glm::vec3 currentColor, int bounces, glm::vec3 oldTrianglePos);
	glm::vec3 getBounceDir(triangle &myTriangle, glm::vec3 incomingDir);
	glm::vec3 getSphereBounceDir(sphere& mySphere, glm::vec3 prevHit, glm::vec3 incomingDir);
	bool rayTriangleIntersect(
		const glm::vec3& orig, const glm::vec3& dir,
		const glm::vec3& v0, const glm::vec3& v1, const glm::vec3 &v2,
		float &t, glm::vec3& P);

	bool IntersectRaySphere(glm::vec3 p, glm::vec3 d, sphere s, float& t, glm::vec3& q);

	glm::vec3 calculateDirectLight(glm::vec3 point, triangle triangleHit, sphere sphereHit, bool isSphere, scene &myScene);
private:
	glm::vec3 pos = glm::vec3(-1, 0, 0);
	glm::vec3 plane[dim][dim];
};

