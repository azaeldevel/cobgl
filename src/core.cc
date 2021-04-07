
#include "core.hh"

namespace octetos::cobgl
{

Window::Window()
{
	// Initialise GLFW
	initGLFW();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}
	MakeContextCurrent();

	// Initialize GLEW
	initGLEW();

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
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