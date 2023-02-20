#pragma warning(disable:4996)

#include "camera.h"
#include <iostream>

camera::camera() {};

void camera::setPlane(scene &myScene) {
	triangle myTriangle;
	sphere theSphere;
	float SS = 10.0f;
	float sqrtSS = sqrt(SS);
	int out = 0;
	glm::vec3 eyePos = glm::vec3(-2, 0, 0);
	for (int i = 0; i < dim; i++) {
		if (i % (dim / 100) == 0) {
			std::cout << out << "%" << std::endl;
			out++;
		}
		for (int j = 0; j < dim; j++) {
			
			glm::vec3 ssColor = glm::vec3(0, 0, 0);


			float randomY = (rand() % 1000 / 10000.0f) * 2.0f - 1.0f;
			float randomZ = (rand() % 1000 / 10000.0f) * 2.0f - 1.0f;
			for (int l = 0; l < SS; l++)
			{
				glm::vec3 pixelPos = glm::vec3(0, i * (2.0f / dim) - (1 - (1 / dim)), j * (2.0f / dim) - (1 - (1 / dim))); //skillnaden är 2/dim
				pixelPos = glm::vec3(pixelPos.x, pixelPos.y + randomY * 2 / dim, pixelPos.z + randomZ*2/dim);
				glm::vec3 dir = pixelPos - eyePos;

				triangle triangleHit = myScene.getTriangle(0);
				sphere mySphere = myScene.getSphere();
				bool hitSphere = false;
				glm::vec3 color = glm::vec3(0,0,0);
				if (i == dim - 117.0f && j == dim - 187.0f) {
					bool hej = true;
				}
				
				color = getColorOfBounces(triangleHit, hitSphere, myScene, dir, color, 0, eyePos);					
				
				ssColor += glm::clamp(color, 0.01f, 0.99f);
			}
			plane[i][j] = ssColor / SS;
		}
	}
};

glm::vec3 camera::getColorOfBounces(triangle &myTriangle, bool &isSphere, scene &myScene, glm::vec3 dir, glm::vec3 currentColor, int bounces, glm::vec3 oldHitPos) {
	
	glm::vec3 hitPos;
	glm::vec3 newHitPos = glm::vec3(-99999, -99999, -99999);

	float distance;
	float min = 999999;

	triangle newTriangle = myTriangle;
	sphere mySphere = myScene.getSphere();
	isSphere = false;

	float bounceCoef = 0.8f;

	if (bounces > 6) {
		return currentColor * bounceCoef;
	}

	if (myTriangle.getColor() == myScene.getTriangle(24).getColor()) {
		return myScene.getTriangle(24).getColor();
	}


	for (int k = 0; k < 30; k++) {
		myTriangle = myScene.getTriangle(k);
		if(rayTriangleIntersect(oldHitPos, dir, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), distance, hitPos)){
			if (distance < min && distance > 0) {
				min = distance;
				currentColor = myTriangle.getColor();
				newTriangle = myTriangle;
				newHitPos = hitPos;
			}
		}
	}
	if (IntersectRaySphere(oldHitPos, dir, mySphere, distance, hitPos)) {
		if (distance < min && distance > 0) {
			min = distance;
			newHitPos = hitPos;
			isSphere = true;
			bounceCoef = 1;
		}
	}

	if (newHitPos == glm::vec3(-99999, -99999, -99999)) {
		//std::cout << oldHitPos.x << std::endl;
	}

	glm::vec3 indirectColor = glm::vec3(0.001f, 0.001f, 0.001f);
	glm::vec3 finalColor = glm::vec3(0.001f, 0.001f, 0.001f);
	glm::vec3 directLight = calculateDirectLight(newHitPos, newTriangle, mySphere, isSphere, myScene);

	bounces++;
	float random = rand()%1000 / 1000.0f;
	//std::cout << random << std::endl;

	if (isSphere) {
		dir = getSphereBounceDir(mySphere, newHitPos, dir);
		return getColorOfBounces(newTriangle, isSphere, myScene, dir, currentColor, bounces, newHitPos);
	}
	else if (random > 0.75f) {
		dir = getBounceDir(newTriangle, dir);
		indirectColor = getColorOfBounces(newTriangle, isSphere, myScene, dir, currentColor, bounces, newHitPos);
	}
	else {
		return directLight * bounceCoef;
	}

	finalColor = indirectColor;
	return finalColor;
};


glm::vec3 camera::calculateDirectLight(glm::vec3 point, triangle triangleHit, sphere sphereHit, bool isSphere, scene& myScene) {
	if (triangleHit.getColor() == myScene.getTriangle(24).getColor()) {
		return triangleHit.getColor();
	}
	glm::vec3 totalL, L = glm::vec3(0.0f);
	int const numberOfShadowRays = 1;
	float pi = 3.1415926535897f;
	triangle myTriangle;

		glm::vec3 v0 = myScene.getTriangle(24).getv0();
		glm::vec3 v1 = myScene.getTriangle(24).getv1();
		glm::vec3 v2 = myScene.getTriangle(24).getv2();

		glm::vec3 LightSourceNormal = glm::vec3(0, 0, -1);

		float A = glm::length(glm::cross(v1 - v0, v2 - v0));
		glm::vec3 lightPoint = glm::vec3(0.0f);
		glm::vec3 DirToPoint = glm::vec3(0.0f);

		float Alpha, Beta, u, v, d, directLight = 0.0f;
		glm::vec3 hit;
		float t;
		//Direct light
		//Check if the intersection is visible with multiple shadowrays
		for (int i = 0; i < numberOfShadowRays; i++) {


			float randomX = (rand() % 1000 / 10000.0f) * 2.0f - 1.0f;
			float randomY = (rand() % 1000 / 10000.0f) * 2.0f - 1.0f;


			lightPoint.x = 5.0f + randomX * 2.0f;
			lightPoint.y = 0.0f + randomY * 2.0f;
			lightPoint.z = 4.99f;

			DirToPoint = glm::normalize(point - lightPoint);
			d = glm::length(point - lightPoint);

			float min = 999999;
			float minSphere = 999999;
			glm::vec3 hitPoint;
			triangle hitTriangle;
			bool sphereIsHit = false;
			bool triangleIsHit = false;
			directLight = 1.0f;

			for (int j = 0; j < 30; j++) {

				myTriangle = myScene.getTriangle(j);
				if (rayTriangleIntersect(lightPoint, DirToPoint, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), t, hit)) {
					if (t < min && t > 0) {
						min = t;
						hitPoint = hit;
						hitTriangle = myTriangle;
						triangleIsHit = true;
					}
				}
			}
			if (IntersectRaySphere(lightPoint, DirToPoint, sphereHit, t, hit)) {
				if (t < min && t > 0) {
					min = t;
					hitPoint = hit;
					sphereIsHit = true;
				}
			}

			if (d < min + 0.001f && d > min - 0.001f) {
				directLight = 1.0f;
			}
			else {
				directLight = 0.01f;
			}

			if (!sphereIsHit) {
				Alpha = glm::dot((LightSourceNormal), (DirToPoint));
				Beta = glm::dot((hitTriangle.getNormal()), (-DirToPoint));
				L += glm::abs(hitTriangle.getColor() * ((Alpha * Beta * directLight) / (d * d))) * 100.0f;
			}
			else {
				Alpha = glm::dot((LightSourceNormal), (DirToPoint));
				Beta = glm::dot((point - sphereHit.getPos()), (-DirToPoint));
				L += glm::abs(((Alpha * Beta * directLight) / (d * d))) * 100.0f;
			}
		}
	
	totalL = L * (1.0f / (numberOfShadowRays));
	return glm::clamp(totalL, 0.01f, 1.0f);
}

glm::vec3 camera::getBounceDir(triangle &myTriangle, glm::vec3 incomingDir) {

	/*glm::vec3 localX = glm::cross(incomingDir, myTriangle.getNormal());
	glm::vec3 localY = glm::cross(localX, incomingDir);
	glm::vec3 localZ = myTriangle.getNormal();*/

	glm::vec3 localZ = myTriangle.getNormal();
	glm::vec3 localX = glm::normalize(myTriangle.getv1() - myTriangle.getv0());
	glm::vec3 localY = glm::cross(localX, localZ);

	float randX = 2.0f * (float)rand() / RAND_MAX - 1.0f;
	float randY = 2.0f * (float)rand() / RAND_MAX - 1.0f;
	float randZ = (float)rand() / RAND_MAX;

	glm::vec3 randDir = glm::vec3((localX * randX) + (localY * randY) + (localZ * randZ));
	glm::vec3 normRandDir = glm::normalize(randDir);

	return normRandDir;
};

glm::vec3 camera::getSphereBounceDir(sphere& mySphere, glm::vec3 hitPos, glm::vec3 incomingDir) {
	//R= I - 2(I * N)N specular bounce

	incomingDir = glm::normalize(incomingDir);
	glm::vec3 sphereNormal = glm::normalize(hitPos - mySphere.getPos());

	glm::vec3 outRay = incomingDir - 2.0f * glm::dot(sphereNormal, incomingDir) * sphereNormal;
	outRay = glm::normalize(outRay);

	return outRay;
};

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
bool camera::rayTriangleIntersect(
	const glm::vec3& orig, const glm::vec3& dir,
	const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
	float &t, glm::vec3 &P)
{
	// compute the plane's normal
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	// no need to normalize
	glm::vec3 N = glm::cross(v0v1, v0v2); // N
	float area2 = glm::length(N);

	// Step 1: finding P

	// check if the ray and plane are parallel.
	float NdotRayDirection = glm::dot(N, dir);
	if (fabs(NdotRayDirection) < 0.0001) // almost 0
		return false; // they are parallel, so they don't intersect! 

	// compute d parameter using equation 2
	float d = glm::dot(-N, v0);

	// compute t (equation 3)
	t = -(glm::dot(N, orig) + d) / NdotRayDirection;

	// check if the triangle is behind the ray
	if (t < 0) return false; // the triangle is behind

	// compute the intersection point using equation 1
	P = orig + t * dir;

	// Step 2: inside-outside test
	glm::vec3 C; // vector perpendicular to triangle's plane

	// edge 0
	glm::vec3 edge0 = v1 - v0;
	glm::vec3 vp0 = P - v0;
	C = glm::cross(edge0, vp0);
	if (glm::dot(N, C) < 0) return false; // P is on the below

	// edge 1
	glm::vec3 edge1 = v2 - v1;
	glm::vec3 vp1 = P - v1;
	C = glm::cross(edge1, vp1);
	if (glm::dot(N, C) < 0)  return false; // P is on the right side

	// edge 2
	glm::vec3 edge2 = v0 - v2;
	glm::vec3 vp2 = P - v2;
	C = glm::cross(edge2, vp2);
	if (glm::dot(N, C) < 0) return false; // P is on the left side;

	return true; // this ray hits the triangle


	//sphere scratchapixel minimal ray tracer rnedering simples shapes / ray sphere intersection
};

// Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting, 
// returns t value of intersection and intersection point q 
//https://gamedev.stackexchange.com/questions/96459/fast-ray-sphere-collision-code
bool camera::IntersectRaySphere(glm::vec3 start, glm::vec3 d, sphere s, float& t, glm::vec3& q)
{
	d = glm::normalize(d);
	// Calculate ray start's offset from the sphere center
	glm::vec3 p = start - s.getPos();

	float rSquared = s.getRadius() * s.getRadius();
	float p_d = dot(p, d);

	// The sphere is behind or surrounding the start point.
	if (p_d > 0 || dot(p, p) < rSquared)
		return false;

	// Flatten p into the plane passing through c perpendicular to the ray.
	// This gives the closest approach of the ray to the center.
	glm::vec3 a = p - p_d * d;

	float aSquared = glm::dot(a, a);

	// Closest approach is outside the sphere.
	if (aSquared > rSquared)
		return false;

	// Calculate distance from plane where ray enters/exits the sphere.    
	float h = sqrt(rSquared - aSquared);

	// Calculate intersection point relative to sphere center.
	glm::vec3 i = a - h * d;

	q = s.getPos() + i;
	glm::vec3 normal = i / s.getRadius();
	// We've taken a shortcut here to avoid a second square root.
	// Note numerical errors can make the normal have length slightly different from 1.
	// If you need higher precision, you may need to perform a conventional normalization.

	return true;// (intersection, normal);
}

void camera::makeImage() {
	FILE* fp = fopen("rendering.ppm", "wb"); /* b - binary mode */
	fprintf(fp, "P6\n%d %d\n255\n", dim, dim);
	for (int j = dim - 1; j > -1; --j)
	{
		for (int i = dim - 1; i > -1; --i)
		{			
			static unsigned char color[3];
			color[0] = (unsigned char)(glm::clamp(plane[i][j].x, 0.0f, 1.0f) * 255.0f);  /* red */
			color[1] = (unsigned char)(glm::clamp(plane[i][j].y, 0.0f, 1.0f) * 255.0f);  /* green */
			color[2] = (unsigned char)(glm::clamp(plane[i][j].z, 0.0f, 1.0f) * 255.0f);  /* blue */
			fwrite(color, 1, 3, fp);
		}
	}
	fclose(fp);
};