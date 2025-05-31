
namespace lasd {

/* ************************************************************************** */
	// Constructors
	template <typename Data>
	HeapVec<Data> :: HeapVec(const TraversableContainer<Data>& c)
		: Vector<Data>(c) 
	{
		Heapify();
	}
		
	template <typename Data>		
	HeapVec<Data> :: HeapVec(MappableContainer<Data>&& c) noexcept
		: Vector<Data>( std::move(c) ) 
	{
		Heapify();	
	}
		
	template <typename Data>
	HeapVec<Data> :: HeapVec(const HeapVec<Data>& vec)
	 : Vector<Data>(vec) {}
	
	template <typename Data>		
	HeapVec<Data> :: HeapVec(HeapVec<Data>&& vec) noexcept
	 : Vector<Data>( std::move(vec) ) {}
	
	// Assigment operator
	template <typename Data> 				
	HeapVec<Data>& HeapVec<Data> :: operator=(const HeapVec<Data>& vec)  
	{
		Vector<Data> :: operator=(vec);	
		return *this;
	}

	template <typename Data>
	HeapVec<Data>& HeapVec<Data> :: operator=(HeapVec<Data>&& vec)  
	{
		Vector<Data> :: operator=( std::move(vec) );	
		return *this;
	}
	
	//Comparison operators
	template <typename Data>
	bool HeapVec<Data> :: operator==(const HeapVec<Data>& vec) const noexcept
	{
		 return Vector<Data> :: operator==(vec);
	}
	
	template <typename Data>
	bool HeapVec<Data> :: operator!=(const HeapVec<Data>& vec) const noexcept
	{
		 return Vector<Data> :: operator!=(vec);
	}	
	
	//Heap methods
	template <typename Data>
	bool HeapVec<Data> :: IsHeap() const noexcept 
	{
		for(unsigned int i=0; i<(size/2); i++)
			if( 	( isLeftNode(i) && elements[i] < elements[2*i +1] )					// left 
			  ||  ( isRigthNode(i) && elements[i] < elements[2*i+2] )	 		// rigth
			 )
			 return false;
		return true;
	}
	
	template <typename Data>
	void HeapVec<Data> :: Heapify() noexcept
	{
		unsigned long int middle = size/2;
		for( unsigned long int i=middle+1; i>0; i-- )	
			Heapify(i-1);
	}
	
	// SortableLinearcontaier methods
	template<typename Data>
	void HeapVec<Data> :: Sort() noexcept
	{
		Heapify();
		unsigned long int temp = size;	//Dovra' essere ripristinata size' 
		for( unsigned i=Size()-1; i>0; i--)
		{
			std :: swap(elements[0], elements[i]);
			size--;
			Heapify(0);
			
		}
		size = temp;
	}
	
	//Auxiliary
	template <typename Data>
	bool HeapVec<Data> :: isLeftNode(unsigned long int i) const noexcept
	{
		return (i * 2 + 1 )  < size;
	}
	
	template <typename Data>
	bool HeapVec<Data> :: isRigthNode(unsigned long int i) const noexcept
	{
		return (i * 2 + 2)  < size;
	}
	
	template <typename Data>
	void HeapVec<Data> :: Heapify(unsigned long int i) noexcept
	{
		unsigned long int largest = i, left = 2*i+1, rigth=2*i+2;
		if ( isLeftNode(i) && elements[left] > elements[largest]  )
			largest = left;
		if ( isRigthNode(i) &&  elements[rigth] > elements[largest] )
			largest = rigth;
		if (i != largest) 
		{
			std :: swap (elements[i], elements[largest]);
			Heapify(largest);
		}			
	}
/* ************************************************************************** */

}
