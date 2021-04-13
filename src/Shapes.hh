

#ifndef OCTETOS_COBGL_SHAPES_PP
#define OCTETOS_COBGL_SHAPES_PP

#include "Vertex.hh"


namespace octetos::cobgl
{


template<typename T> class Triangle
{
public:
	Triangle() : vertex(3)
	{

	};

	VertexList<T,octetos::cobgl::Vertex3D,3>& getVertex()
	{
		return vertex;
	};
	
private:
	octetos::cobgl::VertexList<T,octetos::cobgl::Vertex3D,3> vertex;
};

template<typename T> class Cube
{
public:
	Cube() : vertex(36)
	{

	};

	Triangle<T> operator [](unsigned short index)
	{
		T* h = (T*)vertex;
		h = h + (index * 3);
		Triangle<T> t(h,3);
		return t;
	};
	
	VertexList<T,octetos::cobgl::Vertex3D,3>& getVertex()
	{
		return vertex;
	};
private:
	octetos::cobgl::VertexList<T,octetos::cobgl::Vertex3D,3> vertex;
};

}

#endif