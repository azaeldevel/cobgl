
#ifndef OCTETOS_COBGL_VERTEX_HH
#define OCTETOS_COBGL_VERTEX_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <octetos/core/Exception.hh>
#include <vector>
#include <string.h>


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
template<typename T, template <typename = T> class S> class VertexList : public std::vector<T>
{
public:
	VertexList(unsigned short length) : std::vector<T>(3 * length)
	{
		if(strcmp(typeid(S<T>).name(),typeid(Vertex2D<T>).name()) == 0)
		{
			this->dimension = 2;
			std::vector<T>::resize(2 * length);//TODO: Se asumio en el contructor que la demiencionera 3, si no es asi se corrge
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
		std::cout << "Size of sz = " << dimension * length << ", size = " << std::vector<T>::size() << "\n";
		this->dimension = dimension;
		this->length = length;
	};
	~VertexList()
	{
		glDeleteBuffers(1,&vBuff);
	}
	T* getHeader()
	{
		std::vector<T>& vl = *this;
		return &vl[0];
	}
	S<T>& operator[] (unsigned short index)
	{
		std::vector<T>& vl = *this; 
		if(dimension == 3) 
		{
			T* t = getHeader();
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
	/*S<T>& get3D(unsigned short index)
	{
		std::vector<T>& vl = *this; 
		if(dimension == 3) 
		{
			T* t = getHeader();
			t = t + ((sizeof(Vertex3D<T>)/sizeof(T)) * index);
			return (Vertex3D<T>&) *t ;
		}
		else
		{
			std::string msg = "El vertice tiene dimension '";
			msg += std::to_string(length) + "', pero usted especifico 3.";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	S<T>& get2D(unsigned short index)
	{
		std::vector<T>& vl = *this; 
		if(dimension == 2) 
		{
			T* t = getHeader();
			t = t + ((sizeof(Vertex2D<T>)/sizeof(T)) * index);
			Vertex2D<T>* v = (Vertex2D<T>*) t ;
			return *v;
		}
		else
		{
			std::string msg = "El vertice tiene dimension '";
			msg += std::to_string(length) + "', pero usted especifico 2.";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}*/
	void GenBuffers(GLsizei n)
	{
		glGenBuffers(n, &vBuff);
		glBindBuffer(GL_ARRAY_BUFFER, vBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * length * dimension, getHeader(), GL_STATIC_DRAW);
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