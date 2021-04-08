
#ifndef OCTETOS_COBGL_VERTEX_HH
#define OCTETOS_COBGL_VERTEX_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <octetos/core/Exception.hh>
#include <vector>
#include <string.h>

#include "data.hh"


namespace octetos::cobgl
{


template<typename T> struct Vertex
{
};
template<typename T> struct Vertex2D : public Vertex<T>
{
	T x;
	T y;
};
template<typename T> struct Vertex3D : public Vertex<T>
{
	T x;
	T y;
	T z;
};
template<typename T, template <typename> class S> class VertexList : public octetos::core::Array<T>
{
public:
	VertexList(unsigned short length) : octetos::core::Array<T>(3 * length)
	{
		if(strcmp(typeid(S<T>).name(),typeid(Vertex2D<T>).name()) == 0)
		{
			this->dimension = 2;
			octetos::core::Array<T>::resize(2 * length);//TODO: Se asumio en el contructor que la demiencion era 3, si no es asi se corrge
		}
		else if(strcmp(typeid(S<T>).name(),typeid(Vertex3D<T>).name()) == 0)
		{
			this->dimension = 3;
		}
		else
		{			
			std::string msg = "La clase '";
			msg = msg + typeid(S<T>).name() + "', no es una clase valida.";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
		//std::cout << "Size of sz = " << dimension * length << ", size = " << std::vector<T>::size() << "\n";
		this->dimension = dimension;
		this->length = length;
	};
	~VertexList()
	{
		glDeleteBuffers(1,&vBuff);
	}
	S<T>& operator[] (unsigned short index)
	{
		if(dimension == 3) 
		{
			T* t = (T*)*this;
			t = t + ((sizeof(S<T>)/sizeof(T)) * index);
			return (S<T>&) *t ;
		}
		else
		{
			std::string msg = "El vertice tiene dimension '";
			msg += std::to_string(length) + "', pero usted especifico 3.";
			throw core::Exception(msg,__FILE__,__LINE__);
		}		
	}
	
	void GenBuffers(GLsizei n)
	{
		glGenBuffers(n, &vBuff);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * length * dimension, (T*)*this, GL_STATIC_DRAW);
	}
	void BindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vBuff);
	}
	operator GLuint()
	{
		return vBuff;
	};

private:
	unsigned short dimension;
	unsigned short length;
	GLuint vBuff;
};


}

#endif