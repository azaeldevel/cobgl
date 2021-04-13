



#ifndef OCTETO_CORE_DATA_HH
#define OCTETO_CORE_DATA_HH

#include <stdlib.h>
#include <octetos/core/Exception.hh>

namespace octetos::core
{
struct FlagsDS
{
	unsigned short OwnMemory : 1;
};
template<typename T> class Array
{
public:
	Array(unsigned short size)
	{
		head = new T[size];
		if(!head) throw core::Exception("Fallo la adquisicion de meoria.",__FILE__,__LINE__);
		this->size = size;
		flags.OwnMemory = true;
	}
	Array(T* h,unsigned short sz ) : head(h),size(sz)
	{
		flags.OwnMemory = false;
	}
	~Array()
	{
		if(head and flags.OwnMemory) 
		{
			delete[] head;
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
		if(not flags.OwnMemory) throw core::Exception("No es posible redimensionar un arreglo cuya memoria no es propia",__FILE__,__LINE__);
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
	FlagsDS flags;
};

}

#endif