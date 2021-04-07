

#ifndef OCTETOS_COBGL_CORE_HH
#define OCTETOS_COBGL_CORE_HH


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <octetos/core/Exception.hh>

namespace octetos::cobgl
{

template<class T> struct Vertex
{
};
template<class T> struct Vertex2D : public Vertex<T>
{
	T x;
	T y;
};
template<class T> struct Vertex3D : public Vertex<T>
{
	T x;
	T y;
	T z;
};
template<class T> class VertexList : public std::vector<T>
{
public:
	VertexList(unsigned short dimension, unsigned short size) : std::vector<T>(dimension * size)
	{
		if( size < 2 or size > 3)
		{
			std::string msg = "Solo se pueden crear objetos de 2 y 3 dimensiones, usted especifico '";
			msg += std::to_string(size) + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
		this->dimension = dimension;
		this->size = size;
	};
	T* getHeader()
	{
		std::vector<T>& vl = *this;
		return &vl[0];
	}
	Vertex<T>& operator[](unsigned short index)
	{
		std::vector<T>& vl = *this; 
		if(dimension == 2) 
		{
			T* t = getHeader();
			t = t + (sizeof(Vertex2D<T>) * index);
			Vertex2D<T>* v = (Vertex2D<T>*) t ;
			return *v;
		}
		else if(dimension == 3) 
		{
			T* t = getHeader();
			t = t + ((sizeof(Vertex3D<T>)/sizeof(T)) * index);
			Vertex3D<T>* v = (Vertex3D<T>*) t ;
			return *v;
		}
		else
		{
			std::string msg = "Solo se pueden crear objetos de 2 y 3 domensiones, usted especifico '";
			msg += std::to_string(size) + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
private:
	unsigned short dimension;
	unsigned short size;
};

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