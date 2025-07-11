#include<iostream>
namespace lasd {

/* ************************************************************************** */
	
//Constructors
	//Initial size
	template<typename Data>
	Vector<Data> :: Vector(unsigned long int length)
	{
		size = length;
		elements = new Data[size];
	}
	
	//Vector by TraversableContainer
	template<typename Data>
	Vector<Data> :: Vector(const TraversableContainer<Data>& container)
	{
		size = container.Size();
		elements = new Data[size];
		unsigned long int i = 0;
		container.Traverse
		(
			[this, &i](const Data& dat)
			{
				this->operator[](i) = dat;
				i++;
			}
		);
	}
	//Vector by MappableContainer
	template<typename Data>
	Vector<Data> :: Vector(MappableContainer<Data>&& container)
	{	
		size = container.Size();
		elements = new Data[size];
		unsigned long int i = 0;
		container.Map
		(
			[&i, this](Data& dat)
			{
				elements[i] = std::move(dat);
				i++;
			}
		);
	}		
		
	//Copy constructor
	template<typename Data>
	Vector<Data> :: Vector(const Vector<Data>& vec) 
	{
		size = vec.size;
		elements = new Data[size];
		for(unsigned long int i=0; i < size; i++)
			elements[i] = vec[i];		
	}
	
	//Move constructor
	template<typename Data>
	Vector<Data> :: Vector(Vector<Data>&& vec) noexcept
	{
		std :: swap(size, vec.size);
		std :: swap(elements, vec.elements);
	}

// Destructor	
	template<typename Data>
	Vector<Data> :: ~Vector()
	{
		Clear();
	}

// Operators
	//Move assigment
	template<typename Data>
	inline Vector<Data>& Vector<Data> :: operator=(const Vector<Data>& vec)
	{
		delete[] elements;
		size = vec.size;
		elements = new Data[size];
		for(unsigned long int i=0; i < size; i++)
			elements[i] = vec[i];
		return (*this);
	}
	
	//Move assigment
	template<typename Data>
	inline Vector<Data>& Vector<Data> :: operator=(Vector<Data>&& vec) noexcept
	{
		std :: swap(size, vec.size);
		std :: swap(elements, vec.elements);
		return (*this);
	}
	
	//Comparison
	template<typename Data>
	inline bool Vector<Data> :: operator==(const Vector<Data>& v) const noexcept
	{
		if(size != v.size)
			return false;
		for(unsigned long int i=0; i<size; i++)
			if(elements[i] != v.elements[i])
				return false;
		return true;
	}

	template<typename Data>
	inline bool Vector<Data> :: operator!=(const Vector<Data>& v) const noexcept
	{
		return !( *this == v);
	}

//MutableLinearContainer functions
	template<typename Data>
	inline Data& Vector<Data> :: operator[](unsigned long int i)
	{
		if (i>= size)
			throw std::out_of_range("Indice non valido");
		else
			return elements[i];
	}
	
	template<typename Data>
	inline Data& Vector<Data> :: Front()
	{
		if(Empty())
			throw std::length_error("Container vuoto");
		else
			return elements[0];
	}
	
	template<typename Data>
	inline Data& Vector<Data> :: Back()
	{
		if(Empty())
			throw std::length_error("Container vuoto");
		else
			return elements[size-1];
	}

// LinearContainer functions
	template<typename Data>
	inline const Data& Vector<Data> :: operator[](unsigned long int i) const
	{
		if (i>= size)
			throw std::out_of_range("Indice non valido");
		else
			return elements[i];
	}
	
	template<typename Data>
	inline const Data& Vector<Data> :: Front() const
	{
		if(Empty())
			throw std::length_error("Container vuoto");
		else
			return elements[0];
	}
	
	template<typename Data>
	inline const Data& Vector<Data> :: Back() const
	{
		if(Empty())
			throw std::length_error("Container vuoto");
		else
			return elements[size-1];
	}
//ResizableContainer functions
	template<typename Data>
	inline void Vector<Data> :: Resize(unsigned long int newSize)  
	{
		Data* newVec = nullptr; 
		if(newSize !=0 )
		{
			newVec = new Data[newSize];
			unsigned long int min;
			if(newSize < size)
				min = newSize;
			else
				min = size;
			for(unsigned long int i=0; i < min; i++)
				newVec[i] = elements[i] ;
		}
		delete[] elements;
		elements = newVec;
		size = newSize;
	}

	template<typename Data>
	inline void Vector<Data> :: Clear() noexcept 
	{
		size = 0;
		delete[] elements;
		elements = nullptr;
	}

//SortableVector
	//Constructors
	template<typename Data>
	SortableVector<Data> :: SortableVector(unsigned long int n)
	{
		size = n;
		elements = new Data[n];
	}

	template<typename Data>
	SortableVector<Data> :: SortableVector(const TraversableContainer<Data>& con)
		: Vector<Data>(con)
	{
		//SortableLinearContainer<Data>::Sort();
	}

	template<typename Data>
	SortableVector<Data> :: SortableVector(MappableContainer<Data>&& con) noexcept
		: Vector<Data>(std::move(con))
	{
		//SortableLinearContainer<Data>::Sort();
	}

	//Copy constructor
	template<typename Data>
	SortableVector<Data> :: SortableVector(const SortableVector<Data>& vec)
		: Vector<Data>(vec) {}

	//Move constructor
	template<typename Data>
	SortableVector<Data> :: SortableVector(SortableVector<Data>&&  vec) noexcept
		: Vector<Data>(std::move(vec) ) {}
   //Opetator =
	template<typename Data>
	SortableVector<Data>& SortableVector<Data> :: operator=(const SortableVector<Data>& vec) 	//copy
	{
		Vector<Data>::operator=(vec);
		return (*this);
	}
	
	template<typename Data>
	SortableVector<Data>& SortableVector<Data> :: operator=(SortableVector<Data>&& vec) noexcept	//move
	{
		Vector<Data>::operator=(std::move(vec));
		return (*this);
	}
}
/* ************************************************************************** */


