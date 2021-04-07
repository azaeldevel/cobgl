

#ifndef OCTETOS_COBGL_CORE_HH
#define OCTETOS_COBGL_CORE_HH


// Include standard headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <octetos/core/Exception.hh>
#include <string>


namespace octetos::cobgl
{

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();
	operator GLFWwindow*();

	void MakeContextCurrent();
private:
	void initGLFW();
	void initGLEW();

	
	GLFWwindow* window;
	GLuint VertexArrayID;
};

}

#endif