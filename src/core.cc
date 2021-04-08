
#include "core.hh"

namespace octetos::cobgl
{

Window::Window(int w, int h, const std::string& t)
{
	// Initialise GLFW
	initGLFW();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( w, h, t.c_str(), NULL, NULL);
	if( window == NULL )
	{
		glfwTerminate();
		throw core::Exception("Fallo la creacion de la venta.",__FILE__,__LINE__);
	}
	MakeContextCurrent();

	// Initialize GLEW
	initGLEW();
}	
void Window::initGLFW()
{
	glewExperimental = true; // Needed for core profile
	if( !glfwInit() )
	{
		glfwTerminate();
		throw core::Exception("Fallo la inicializacion de GLFW.",__FILE__,__LINE__);
	}
}
void Window::initGLEW()
{
	if (glewInit() != GLEW_OK) 
	{
		throw core::Exception("Fallo la inicializacion de GLEW.",__FILE__,__LINE__);
	}
}
Window::~Window()
{
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
}

Window::operator GLFWwindow*()
{
	return window;
}


void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(window);
}
}