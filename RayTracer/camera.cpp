#pragma warning(disable:4996)

#include "camera.h"
#include <iostream>

camera::camera() {};

void camera::setPlane(scene &myScene) {
	triangle myTriangle;
	sphere theSphere;
	float SS = 16.0f;
	float sqrtSS = sqrt(SS);
	glm::vec3 eyePos = glm::vec3(-1, 0, 0);
	for (int i = 0; i < dim; i++) {
		
		for (int j = 0; j < dim; j++) {
			if (i%(dim/10) == 0 && j == 0) {
				std::cout << i/ (dim / 100) << "%" << std::endl;
			}
			glm::vec3 ssColor = glm::vec3(0, 0, 0);

			int SScoefI = 0;
			int SScoefJ = -1;
			for (int l = 0; l < SS; l++)
			{
				
				SScoefI = (l % (int)sqrtSS) / sqrtSS;
				if (SScoefI == 0) SScoefJ++;

				glm::vec3 pixelPos = glm::vec3(0, i * (2.0f / dim) - (1 - (1 / dim)), j * (2.0f / dim) - (1 - (1 / dim))); //skillnaden är 2/dim
				//pixelPos = glm::vec3(pixelPos.x, pixelPos.y + 2.0f/(dim*3.0f) * SScoefI, pixelPos.z + 2.0f / (dim * 3.0f) * SScoefJ);
				glm::vec3 dir = pixelPos - eyePos;

				glm::vec3 intersect;
				glm::vec3 hitPos = glm::vec3(0,0,0);
				glm::vec3 hitDir;
				glm::vec3 color = glm::vec3(0,0,0);
				float t;
				float min = 999999;
				triangle triangleHit = myScene.getTriangle(0);
				bool hitSphere = false;
				sphere sphereHit;

				//find intersection point and object
				for (int k = 0; k < 30; k++) {
				
					myTriangle = myScene.getTriangle(k);
					if (rayTriangleIntersect(eyePos, dir, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), t, intersect))
					{
						if (t < min && t > 0) {
							min = t;
							color = myTriangle.getColor();
							triangleHit = myTriangle;
							hitPos = intersect;
							color = myTriangle.getColor();
						}
					}
				}
				sphere mySphere = myScene.getSphere();
				if (IntersectRaySphere(eyePos, dir, mySphere, t, intersect)) {
					if (t < min && t > 0) {
						min = t;
						color = mySphere.getColor();
						hitPos = intersect;
						hitSphere = true;
					}
				}
				if (j == 4 && l == 12) {
						bool hej = true;
				}
				glm::vec3 directColor = glm::clamp(calculateDirectLight(hitPos, triangleHit, mySphere, hitSphere, myScene), 0.0f, 1.0f);
				
				if (hitSphere == true) {
					dir = getSphereBounceDir(mySphere, eyePos, dir, hitPos);
					glm::vec3 indirectColor = glm::clamp(getColorOfBounces(triangleHit, hitSphere, myScene, dir, color, 0, eyePos), 0.0f, 1.0f);
					color = indirectColor;
				}
				else if (glm::linearRand(0.0f, 1.0f) > 0.75f) {
					dir = getBounceDir(triangleHit, dir);
					glm::vec3 indirectColor = glm::clamp(getColorOfBounces(triangleHit, hitSphere, myScene, dir, color, 0, eyePos), 0.0f, 1.0f);
					color = directColor * indirectColor*0.8f;
				}
				else {
					color = directColor;
				}
					
				
				ssColor += glm::clamp(color, 0.0f, 1.0f);
			}
			plane[i][j] = ssColor / SS;

		}
	}

};

glm::vec3 camera::getSphereBounce(triangle& myTriangle, bool isSphere, scene& myScene, glm::vec3 dir, glm::vec3 currentColor, int bounces, glm::vec3 oldHitPos) {

	glm::vec3 newHitPos = glm::vec3(-9999, -9999, -9999);
	glm::vec3 hitPos;
	glm::vec3 finalColor = currentColor;
	float distance;
	float min = 999999;
	float bounceCeof = 0.25;
	triangle newTriangle;
	sphere newSphere;
	for (int k = 0; k < 30; k++) {

		myTriangle = myScene.getTriangle(k);
		if (rayTriangleIntersect(oldHitPos, dir, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), distance, hitPos)) {
			if (distance < min && distance > 0) {
				min = distance;
				finalColor = myTriangle.getColor();
				newTriangle = myTriangle;
				newHitPos = hitPos;
			}
		}
	}
	return finalColor;
}

glm::vec3 camera::getColorOfBounces(triangle &myTriangle, bool isSphere, scene &myScene, glm::vec3 dir, glm::vec3 currentColor, int bounces, glm::vec3 oldHitPos) {
	
	float bounceCeof = 0.8f;
	
	if (bounces >= 5) {
		return currentColor * bounceCeof;
	}

	if (myTriangle.getColor() == myScene.getTriangle(24).getColor()) {
		return myScene.getTriangle(24).getColor();
	}

	glm::vec3 newHitPos = oldHitPos;
	glm::vec3 hitPos;
	glm::vec3 finalColor = currentColor;
	float distance;
	float min = 999999;
	triangle newTriangle = myTriangle;
	sphere newSphere;
	isSphere = false;
	for (int k = 0; k < 30; k++) {

		myTriangle = myScene.getTriangle(k);
		if(rayTriangleIntersect(oldHitPos, dir, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), distance, hitPos)){
			if (distance < min && distance > 0) {
				min = distance;
				finalColor = myTriangle.getColor();
				newTriangle = myTriangle;
				newHitPos = hitPos;
			}
		}
	}
	sphere mySphere = myScene.getSphere();
	if (IntersectRaySphere(oldHitPos, dir, mySphere, distance, hitPos)) {
		if (distance < min && distance > 0) {
			min = distance;
			newHitPos = hitPos;
			isSphere = true;
			bounceCeof = 1;
		}
	}

	if (isSphere) {
		dir = getSphereBounceDir(mySphere, newHitPos, dir, oldHitPos);
	}
	else {
		dir = getBounceDir(newTriangle, dir);
	}

	glm::vec3 directLight = calculateDirectLight(newHitPos, newTriangle, mySphere, isSphere, myScene);

	bounces++;
	if (isSphere) {
		finalColor += getColorOfBounces(newTriangle, isSphere, myScene, dir, finalColor, bounces, newHitPos);
	}
	else if (glm::linearRand(0.0f, 1.0f) > 0.5f) {
		finalColor += getColorOfBounces(newTriangle, isSphere, myScene, dir, finalColor, bounces, newHitPos);
	}

	finalColor = (directLight * finalColor) * bounceCeof;
	return finalColor;
};


glm::vec3 camera::calculateDirectLight(glm::vec3 point, triangle triangleHit, sphere sphereHit, bool isSphere, scene& myScene) {
	if (triangleHit.getColor() == myScene.getTriangle(24).getColor()) {
		return triangleHit.getColor();
	}
	glm::vec3 Ld, L = glm::vec3(0.0f);
	int const numberOfShadowRays = 1;
	float pi = 3.1415926535897f;
	triangle myTriangle;

	glm::vec3 v0 = myScene.getTriangle(24).getv0();
	glm::vec3 v1 = myScene.getTriangle(24).getv1();
	glm::vec3 v2 = myScene.getTriangle(24).getv2();

	glm::vec3 LightSourceNormal = glm::vec3(0, 0, -1);

	float A = glm::length(glm::cross(v1 - v0, v2 - v0)) * 0.5f;
	glm::vec3 q = glm::vec3(0.0f);
	glm::vec3 DirToPoint = glm::vec3(0.0f);

	float cosAlpha, cosBeta, u, v, d, Vk = 0.0f;
	glm::vec3 hit;
	float t;

	v = -1;
	//Direct light
	//Check if the intersection is visible with multiple shadowrays
	for (int i = 0; i < numberOfShadowRays; i++) {

		u = i % (int)sqrt(numberOfShadowRays) / sqrt(numberOfShadowRays);
		if (u == 0) v++;
		//q = u * (v1 - v0) + v * (v2 - v0);

		q.x = 4.0f + 2 * (u / sqrt(numberOfShadowRays));
		q.y = -1.0f + 2 * (v / sqrt(numberOfShadowRays));
		q.z = 4.99f;


		DirToPoint = glm::normalize(point - q);
		d = glm::length(point - q);

		float min = 999999;
		float minSphere = 999999;
		glm::vec3 hitPoint;
		triangle hitTriangle;
		if (!isSphere) {
			for (int j = 26; j < 30; j++) {

				myTriangle = myScene.getTriangle(j);
				if (rayTriangleIntersect(q, DirToPoint, myTriangle.getv0(), myTriangle.getv1(), myTriangle.getv2(), t, hit)) {
					if (t < min && t > 0) {
						min = t;
						hitPoint = hit;
						hitTriangle = myTriangle;
					}
				}
			}

			
			if (IntersectRaySphere(q, DirToPoint, sphereHit, t, hit)) {
				if (t < minSphere && t > 0) {
					min = t;
					hitPoint = hit;
				}
			}

			if (min == 999999) {
				hitTriangle = triangleHit;
				Vk = 1.0f;
			}
			else if (hitTriangle.getv0() == triangleHit.getv0() && hitTriangle.getv1() == triangleHit.getv1() && hitTriangle.getv2() == triangleHit.getv2()) {
				Vk = 1.0f;
			}
			else if (minSphere != 999999) {
				Vk = 0.0f;
			}
			else {
				Vk = 0.0f;
			}

			if (point.z > 4.99f) {
				Vk = 0.0f;
			}

			cosAlpha = glm::dot((LightSourceNormal), (DirToPoint));
			cosBeta = glm::dot((hitTriangle.getNormal()), (-DirToPoint));
			L += glm::abs(hitTriangle.getColor() * ((cosAlpha * cosBeta * Vk) / (d * d))) *100.0f;
		}
		else {
			cosAlpha = glm::dot((LightSourceNormal), (DirToPoint));
			cosBeta = glm::dot((point - sphereHit.getPos()), (-DirToPoint));
			L += glm::abs(((cosAlpha * cosBeta * Vk) / (d * d)));
		}
	}

	Ld = L * (1.0f / numberOfShadowRays);
	return glm::clamp(Ld, 0.0f, 1.0f);
}

glm::vec3 camera::getBounceDir(triangle &myTriangle, glm::vec3 incomingDir) {

	glm::vec3 localX = glm::cross(incomingDir, myTriangle.getNormal());
	glm::vec3 localY = glm::cross(localX, incomingDir);
	glm::vec3 localZ = myTriangle.getNormal();

	float randX = glm::linearRand(0.0f, 1.0f);
	float randY = glm::linearRand(-1.0f, 1.0f);
	float randZ = glm::linearRand(-1.0f, 1.0f);

	glm::vec3 randDir = glm::vec3((localX * randX) + (localY * randY) + (localZ * randZ));
	glm::vec3 normRandDir = glm::normalize(randDir);

	return normRandDir;
};

glm::vec3 camera::getSphereBounceDir(sphere& mySphere, glm::vec3 prevHit, glm::vec3 incomingDir, glm::vec3 hitPos) {
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

