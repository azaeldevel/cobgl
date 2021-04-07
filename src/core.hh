

#ifndef OCTETOS_COBGL_CORE_HH
#define OCTETOS_COBGL_CORE_HH


// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>



namespace octetos::cobgl
{

class Window
{
public:
	Window();
	~Window();
	operator GLFWwindow*();
private:
	GLFWwindow* window;
};



}

#endif