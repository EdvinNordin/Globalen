// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "camera.h"
#include <time.h>

int main()
{

    clock_t tStart = clock();
    srand(time(0));
    //std::cout << glm::triangleNormal(glm::vec3(8, 1, -2), glm::vec3(10, 5, -2), glm::vec3(12, 1, -2)).x << " " << glm::triangleNormal(glm::vec3(8, 1, -2), glm::vec3(12, 1, -2), glm::vec3(10, 5, -2)).y << " " << glm::triangleNormal(glm::vec3(8, 1, -2), glm::vec3(12, 1, -2), glm::vec3(10, 5, -2)).z << " ";
    scene scene;
    scene.setScene();

    camera camera;
    camera.setPlane(scene);
    camera.makeImage();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
