



#ifndef OCTETO_CORE_DATA_HH
#define OCTETO_CORE_DATA_HH

#include <stdlib.h>
#include <octetos/core/Exception.hh>

namespace octetos::core
{

template<typename T> class Array
{
public:
	Array(unsigned short size)
	{
		head = new T[size];
		if(!head) throw core::Exception("Fallo la adquisicion de meoria.",__FILE__,__LINE__);
		this->size = size;
	}
	~Array()
	{
		if(head) 
		{
			delete [] head;
			head = NULL;
		}
	}
	T& operator [](unsigned short index)
	{
		if(index >= size) throw core::Exception("El valor del indice apunta fuera del arreglo.",__FILE__,__LINE__);
		
		return head[index];
	};

	void resize(unsigned short size)
	{
		if(head) delete [] head;
		head = new T[size];
		if(!head) throw core::Exception("Fallo la adquisizion de meoria.",__FILE__,__LINE__);
		this->size = size;
	}
	unsigned short getSize()const
	{
		return size;
	}
	operator T* ()
	{
		return head;
	};
private:
	T* head;
	unsigned short size;
};

}

#endif