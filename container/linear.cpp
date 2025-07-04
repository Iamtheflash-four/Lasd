// #include "linear.hpp"
#include <exception>
#include <stdexcept>
namespace lasd {

/* ************************************************************************** */
//LinearContainer methods
	//operator != e ==
	template<typename Data>
	inline bool LinearContainer<Data> :: operator==  (const LinearContainer<Data>& l2) const noexcept
	{
		if(this->Size() != l2.Size())
			return false;
		for(unsigned long int i=0; i<Size(); i++)
		{
			if((*this)[i] != l2[i])
				return false;	
		}
		return true;
	}
	
	template<typename Data>
	inline bool LinearContainer<Data> :: operator!= (const LinearContainer<Data>& l2) const noexcept
	{
		return ! ( *this == l2);
	}

	//Front and Back
	template<typename Data>
	inline const Data& LinearContainer<Data> :: Front() const 
	{	
		if( Empty() )	//Se il container e' vuoto getta length_error 
			throw std::length_error("Is empty");
		return operator[](0);
	}
	
	template<typename Data>
	inline const Data& LinearContainer<Data> :: Back() const 
	{
		if( Empty() )	//Se il container e' vuoto getta length_error 
			throw std::length_error("Is empty");
		return operator[](Size()-1);
	}
	
	//Traverse
	template<typename Data>
	inline void LinearContainer<Data> :: Traverse(TraverseFun func) const
	{
		PreOrderTraverse(func);
	}
	
	template<typename Data>
	inline void LinearContainer<Data> :: PreOrderTraverse(TraverseFun func) const
	{
		for(unsigned long int i=0; i<Size(); i++)	// [0, size)
			func ( this->operator[](i) );
	}
	
	template<typename Data>
	inline void LinearContainer<Data> :: PostOrderTraverse(TraverseFun func) const
	{
		unsigned long int i=Size();
		while(i>0)	// (size, 0]
		{
			i--;
			func ( operator[](i) );
		}
	}

// MutableLinearContainer methods
	template<typename Data>
	inline Data& MutableLinearContainer<Data> :: Front()
	{
		return operator[](0); 
	}
	
	template<typename Data>
	inline Data& MutableLinearContainer<Data> :: Back()
	{
		return operator[]( Size()-1 );
	}
	
	template<typename Data>
	inline void MutableLinearContainer<Data> :: Map(MapFun func) noexcept
	{
		PreOrderMap(func);	
	}
	
	template<typename Data>
	inline void MutableLinearContainer<Data> :: PreOrderMap(MapFun func) noexcept
	{
		for(unsigned long int i=0; i<Size(); i++)
			func( operator[](i) );
	}

	template<typename Data>
	inline void MutableLinearContainer<Data> :: PostOrderMap(MapFun func) noexcept
	{
		unsigned long int i=Size();
		while(i>0)	// (size, 0]
		{
			i--;
			func( operator[](i) );
		}
	}

	
// SortableLinearContainer 
	template <typename Data>
	void SortableLinearContainer<Data> :: Sort() noexcept
	{
		for(unsigned long int i=1; i<Size(); i++)
		{
			unsigned long int j=i;
			Data x = operator[](i);
			
			while( j>0 && x < operator[](j-1) )
			{
				operator[](j) = operator[](j-1);
				j--;
			}
			operator[](j) = x;
		}
	}

/* ************************************************************************** */

}
