#include <utility>
namespace lasd {

/* ************************************************************************** */
	// Constructors
	template <typename Data>
	PQHeap<Data> :: PQHeap(const TraversableContainer<Data>& con)
		: Vector<Data>(con), HeapVec<Data>(con)
	{
		capacity = size;	
	}
	
	template <typename Data>
	PQHeap<Data> :: PQHeap(MappableContainer<Data>&& con) noexcept
		: Vector<Data>(std::move(con)), HeapVec<Data>( std::move(con) ) 
	{
		capacity = size;
	}
	
	template <typename Data>
	PQHeap<Data> :: PQHeap(const PQHeap<Data>& queue)
		: Vector<Data>(queue), HeapVec<Data>(queue) 
	{
		capacity = queue.capacity;
	}
	
	template <typename Data>
	PQHeap<Data> :: PQHeap(PQHeap<Data>&&  queue) noexcept
		: Vector<Data>(std::move(queue)), HeapVec<Data>( std::move(queue) )
	{
		capacity = 0;
		std :: swap(capacity, queue.capacity);
	}
	
	// Assigment operator	
	template <typename Data>
	PQHeap<Data>& PQHeap<Data> :: operator= (const PQHeap<Data>& queue)
	{
		HeapVec<Data> :: operator= (queue);
		capacity = queue.capacity;
		return *this;	
	}
	
	template <typename Data>
	PQHeap<Data>& PQHeap<Data> :: operator= (PQHeap<Data>&& queue) noexcept
	{
		HeapVec<Data> :: operator= ( std::move(queue) );
		std::swap(capacity, queue.capacity);
		return *this;	
	}
	
	template <typename Data>
	const Data& PQHeap<Data> :: Tip() const
	{
		if( this->Empty() )
			throw std::length_error("Heap vuoto...");
		return (*this)[0];
	}
	
	// PQ methods
	template <typename Data>
	void PQHeap<Data> :: RemoveTip()
	{
		if( this->Empty() )
			throw std::length_error("Heap vuoto...");
		std::swap(elements[0],  elements[size-1]);
		size--;
		this->Heapify(0);
	}
	
	template <typename Data>
	Data PQHeap<Data> :: TipNRemove()
	{
		Data val = Tip();
		RemoveTip();
		return val;
	}
	
	template <typename Data>
	void PQHeap<Data> :: Insert(const Data& val)
	{
		if(size == capacity)
			Resize( size * 2 + 1  );
		elements[size] = val;
		size++;
		//this->Heapify();
		HeapifyUp(size -1);
	}
	
	template <typename Data>
	void PQHeap<Data> :: Insert(Data&& val) noexcept
	{
		if(size == capacity)
			Resize( size * 2 + 1 );
		elements[size] = std::move(val);
		size++;
		HeapifyUp(size -1);
		//this->Heapify();
	}
	
	template <typename Data>
	void PQHeap<Data> :: Change(unsigned long int i, const Data& val)
	{
		if(i < size)
		{
			Data old = elements[i];
			elements[i] = val;
			if(val > old)
				HeapifyUp(i);
			else if(val < old)
				this->Heapify(i);
		}
	}
	
	template <typename Data>
	void PQHeap<Data> :: Change(unsigned long int i, Data&& val) noexcept
 	{
		if(i < size)
			elements[i] = std::move(val);
		this->Heapify();
	}

	template <typename Data>
	const Data& PQHeap<Data> :: operator[](unsigned long int i) const 
	{
		if(i >= size)
			throw std::out_of_range("Indice errato");
		return elements[i];
	}

	template <typename Data>
	void PQHeap<Data> :: Clear() noexcept 
	{
		Vector<Data>::Clear();
		capacity = 0;
	}

	// Auxiliary
	template <typename Data>
	void PQHeap<Data> :: Resize(unsigned long int n)
	{
		Data *vec = nullptr;
		unsigned long int min;
		if( n < size)
			min = n;
		else 
			min = size;
		if( n > 0 )
		{
			vec = new Data[n];
			for(unsigned long int i=0; i<min; i++)
				vec[i] = elements[i];
		}
		size = min;
		capacity = n;
		delete[] elements;
		elements = vec;
	}

	template <typename Data>
	void PQHeap<Data> :: HeapifyUp(unsigned long int i) noexcept
	{
		while( i>0 )
		{
			unsigned long int radice = (i-1) /2;
			if(elements[i] <= elements[radice])
				i = 0;	//esci dal ciclo
			else{
				std::swap(elements[i], elements[radice]);
				i = radice;
			}
		}
	}

	// template <typename Data>
	// void PQHeap<Data> :: HeapifyDown(unsigned long int i) noexcept
	// {
	// 	Heao
	// }
/* ************************************************************************** */

}
