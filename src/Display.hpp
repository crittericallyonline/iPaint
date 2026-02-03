#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#ifndef GLFW_NO_INCLUDE
#include "glad/glad.h"
#define GLFW_NO_INCLUDE
#include <GLFW/glfw3.h>
#endif

#include "Sprite.hpp"

#include <iostream>
#include "Font.hpp"

struct Display
{
	GLFWwindow* window;
	void Create(int width, int height, const char* title);
	void SetTitle(const char* title) const;
} Display;

void Display::Create(int width, int height, const char *title)
{
	if(!glfwInit())
	{
		std::cout << "Failed to initialize glfw." << std::endl;
		return;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
        return;
	}


    glfwMakeContextCurrent(window);

	gladLoadGL();


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

#endif // DISPLAY_HPP