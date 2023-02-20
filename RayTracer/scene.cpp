#include "scene.h"

scene::scene(){}

void scene::setScene() {
	//floor
	triangles[0].setTriangle(glm::vec3(-3, 0, -5), glm::vec3(0, -6, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));
	triangles[1].setTriangle(glm::vec3(0, -6, -5), glm::vec3(10, -6, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));
	triangles[2].setTriangle(glm::vec3(10, -6, -5), glm::vec3(13, 0, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));
	triangles[3].setTriangle(glm::vec3(13, 0, -5), glm::vec3(10, 6, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));
	triangles[4].setTriangle(glm::vec3(10, 6, -5), glm::vec3(0, 6, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));
	triangles[5].setTriangle(glm::vec3(0, 6, -5), glm::vec3(-3, 0, -5), glm::vec3(5, 0, -5), glm::vec3(0.9f, 0.9f, 0.9f));

	//left wall
	triangles[6].setTriangle(glm::vec3(-3, 0, -5), glm::vec3(0, 6, -5), glm::vec3(-3, 0, 5), glm::vec3(0.9f, 0.1f, 0.1f)); //bak
	triangles[7].setTriangle(glm::vec3(0, 6, -5), glm::vec3(0, 6, 5), glm::vec3(-3, 0, 5), glm::vec3(0.9f, 0.1f, 0.1f));
	triangles[8].setTriangle(glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), glm::vec3(0, 6, 5), glm::vec3(0.1f, 0.9f, 0.1f)); //vänster
	triangles[9].setTriangle(glm::vec3(10, 6, -5), glm::vec3(10, 6, 5), glm::vec3(0, 6, 5), glm::vec3(0.1f, 0.9f, 0.1f));
	triangles[10].setTriangle(glm::vec3(10, 6, -5), glm::vec3(13, 0, -5), glm::vec3(10, 6, 5), glm::vec3(0.1f, 0.1f, 0.9f)); //fram
	triangles[11].setTriangle(glm::vec3(13, 0, -5), glm::vec3(13, 0, 5), glm::vec3(10, 6, 5), glm::vec3(0.1f, 0.1f, 0.9f));

	//right wall
	triangles[12].setTriangle(glm::vec3(13, 0, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, 5), glm::vec3(0.75f, 0.75f, 0.1f)); //fram
	triangles[13].setTriangle(glm::vec3(10, -6, -5), glm::vec3(10, -6, 5), glm::vec3(13, 0, 5), glm::vec3(0.75f, 0.75f, 0.1f));
	triangles[14].setTriangle(glm::vec3(10, -6, -5), glm::vec3(0, -6, -5), glm::vec3(10, -6, 5), glm::vec3(0.75f, 0.1f, 0.75f)); //höger
	triangles[15].setTriangle(glm::vec3(0, -6, -5), glm::vec3(0, -6, 5), glm::vec3(10, -6, 5), glm::vec3(0.75f, 0.1f, 0.75f));
	triangles[16].setTriangle(glm::vec3(-3, 0, -5), glm::vec3(0, -6, 5), glm::vec3(0, -6, -5), glm::vec3(0.1f, 0.75f, 0.75f)); //bak
	triangles[17].setTriangle(glm::vec3(-3, 0, -5), glm::vec3(-3, 0, 5), glm::vec3(0, -6, 5), glm::vec3(0.1f, 0.75f, 0.75f));

	//roof
	triangles[18].setTriangle(glm::vec3(-3, 0, 5), glm::vec3(5, 0, 5), glm::vec3(0, -6, 5), glm::vec3(0.1f, 0.1f, 0.1f));
	triangles[19].setTriangle(glm::vec3(0, -6, 5), glm::vec3(5, 0, 5), glm::vec3(10, -6, 5), glm::vec3(0.1f, 0.1f, 0.1f));
	triangles[20].setTriangle(glm::vec3(10, -6, 5), glm::vec3(5, 0, 5), glm::vec3(13, 0, 5), glm::vec3(0.1f, 0.1f, 0.1f));
	triangles[21].setTriangle(glm::vec3(13, 0, 5), glm::vec3(5, 0, 5), glm::vec3(10, 6, 5), glm::vec3(0.1f, 0.1f, 0.1f));
	triangles[22].setTriangle(glm::vec3(10, 6, 5), glm::vec3(5, 0, 5), glm::vec3(0, 6, 5), glm::vec3(0.1f, 0.1f, 0.1f));
	triangles[23].setTriangle(glm::vec3(0, 6, 5), glm::vec3(5, 0, 5), glm::vec3(-3, 0, 5), glm::vec3(0.1f, 0.1f, 0.1f));

	//light
	triangles[24].setTriangle(glm::vec4(4, 1, 4.99f, 1), glm::vec4(6, 1, 4.99f, 1), glm::vec4(6, -1, 4.99f, 1), glm::vec3(1.0f, 1.0f, 1.0f));
	triangles[25].setTriangle(glm::vec4(6, -1, 4.99f, 1), glm::vec4(4, -1, 4.99f, 1), glm::vec4(4, 1, 4.99f, 1), glm::vec3(1.0f, 1.0f, 1.0f));

	//tetrahedron
	triangles[26].setTriangle(glm::vec3(6, 0.5f, -2), glm::vec3(8, 4.5f, -2), glm::vec3(10, 0.5f, -2), glm::vec3(0.9f, 0.25f, 0.1f));
	triangles[27].setTriangle(glm::vec3(6, 0.5f, -2), glm::vec3(10, 0.5f, -2), glm::vec3(8, 2.5f, 2), glm::vec3(0.9f, 0.25f, 0.1f));
	triangles[28].setTriangle(glm::vec3(10, 0.5f, -2), glm::vec3(8, 4.5f, -2), glm::vec3(8, 2.5f, 2), glm::vec3(0.9f, 0.25f, 0.1f));
	triangles[29].setTriangle(glm::vec3(8, 4.5f, -2), glm::vec3(6, 0.5f, -2), glm::vec3(8, 2.5f, 2), glm::vec3(0.9f, 0.25f, 0.1f));//0.9f, 0.25f, 0.1f

	//sphere
	theSphere = sphere(glm::vec3(8, -2.5, -0.5), 2.0f);
};
triangle scene::getTriangle(int x)
{
	return triangles[x];
};

sphere scene::getSphere()
{
	return theSphere;
};

