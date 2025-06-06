
namespace lasd {

/* ************************************************************************** */
	//Constructors
	template<typename Data>
	SetVec<Data> :: SetVec()
	{
		size = head =  count =0;
		elements = nullptr;
	}
	
	template<typename Data>
	SetVec<Data> :: SetVec(const TraversableContainer<Data>& con)
	{
		head = count = size = 0;
		elements = nullptr;
		con.Traverse
		(
			[this](const Data& dat)
			{
				Insert(dat);
			}
		);
	}
	
	template<typename Data>
	SetVec<Data> :: SetVec(MappableContainer<Data>&& con) noexcept
	{
		count = head  = size = 0;
		elements = nullptr;
		con.Traverse
		(
			[this](const Data& dat)
			{
				this->Insert( std::move(dat) );
			}
		);
	}
	
	// Copy
	template<typename Data>
	SetVec<Data> :: SetVec(const SetVec<Data>& vec)
	{
		size = vec.size;
		count = vec.count;
		head = 0;
		elements = new Data[size];
		unsigned long int i;
		for(i=0; i < vec.count; i++)
			elements[i] = vec[i];
	}
	
	// Move
	template<typename Data>
	SetVec<Data> :: SetVec(SetVec<Data>&& vec) noexcept
	{
		size = count = 0;
		head = 0;
		elements = nullptr;
		std :: swap(count, vec.count);
		std :: swap(head, vec.head);
		std :: swap(size, vec.size);
		std :: swap(elements, vec.elements);
	}
	
	// Destructor
	template<typename Data>
	SetVec<Data> :: ~SetVec() 
	{
		delete[] elements;
	}
	
	// Copy assigment
	template<typename Data>
	inline SetVec<Data>& SetVec<Data> :: operator= (const SetVec<Data>& vec) 
	{
		delete[] elements;
		elements = new Data[size];
		head = 0;
		for(count=0; count < size; count++)
			elements[count] = vec[count];
		return *this;
	}
	
	template<typename Data>
	inline SetVec<Data>& SetVec<Data> :: operator= (SetVec<Data>&& vec) noexcept 
	{
		std :: swap(count, vec.count);
		std :: swap(head, vec.head);
		std :: swap(size, vec.size);
		std :: swap(elements, vec.elements);
		return *this;
	}
	//Comparison operators
	template<typename Data>
	inline bool SetVec<Data> :: operator == (const SetVec<Data>& vec) const noexcept
	{
		if(count != vec.count)
			return false;
		for(unsigned long int i=0; i < count; i++)
			if( (*this)[i] != vec[i] )
				return false;
		return true;
	}
	
	template<typename Data>
	inline bool SetVec<Data> :: operator != (const SetVec<Data>& vec) const noexcept
	{
		return !( (*this) == vec );
	}
	
	// TestableContainer function
	template<typename Data>
	inline bool SetVec<Data> :: Exists(const Data& dat) const noexcept
	{
		// bool found = false;
		// unsigned long int i=0;
		// while ( i < count && found == false)
		// {	
		// 	if( (*this)[i] == dat )
		// 		found = true;
		// 	i++;
		// }
		// return found;
		unsigned long pos = binSearch(dat);
		return  pos!=count && (*this)[pos]== dat;
	}
	
	// OrderedDictionaryContainer
	template<typename Data>
	inline const Data& SetVec<Data> :: Min() const
	{
		if( Empty() )
			throw std :: length_error("Container vuoto");
		return elements[head];
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: MinNRemove() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		const Data  *min = &Min();
		Data mincopy = *min;
		RemoveMin();
		return mincopy;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveMin() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		head = (head +1 ) % size;
		count--;
	}

	template<typename Data>
	inline const Data& SetVec<Data> :: Max() const
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		return (*this)[count-1];
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: MaxNRemove()
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		const Data  *max = &Max();
		Data maxCopy = *max;
		RemoveMax();
		return maxCopy;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveMax() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		count--;
	}

	//Predecessor
	template<typename Data>
	inline const Data& SetVec<Data> :: Predecessor(const Data& dat) const
	{
		unsigned long int i = predecessorPos(dat); 
		return (*this)[i];
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: PredecessorNRemove (const Data& dat) 
	{
		unsigned long int i = predecessorPos(dat); 
		Data val = operator[](i);
		Remove((*this)[i]);
		return val;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemovePredecessor (const Data& dat) 
	{
		unsigned long int i = predecessorPos(dat); 
		Remove( (*this)[i] );
	}
	
	
	//Successor
	template<typename Data>
	inline const Data& SetVec<Data> :: Successor(const Data& dat) const
	{
		unsigned long int i = successorPos(dat);
		return (*this)[i];	
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: SuccessorNRemove (const Data& dat) 
	{
		unsigned long int i = successorPos(dat);
		Data val = operator[](i);
		Remove( (*this)[i] );
		return val;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveSuccessor (const Data& dat) 
	{
		unsigned long int i = successorPos(dat);
		Remove( (*this)[i] );
	}

	// DictionaryContainer functions
	template<typename Data>
	inline bool SetVec<Data> :: Insert(const Data& dat)
	{
		unsigned long index = binSearch(dat);
		if(count!= index)
		{
			if ( (*this)[index] == dat)
				return false;
		}
			
		if(size == count)	//Buffer pieno
			Resize( 2*size +1 );
		
		count++;
		if(index == count)
		{
			head = (size + head -1) % size;
			elements[head] = dat;
		}
		else
		{
			for(unsigned long int i=count-1; i>index; i--)
				at(i) = (*this)[i-1];
			at(index) = dat;	
		}
		return true;
	}



	// DictionaryContainer functions
	template<typename Data>
	inline bool SetVec<Data> :: Insert(Data&& dat) noexcept
	{
		unsigned long index = binSearch(dat);
		if(count != index)
		{
			if ( (*this)[index] == dat)
				return false;
		}
			
		if(size == count)	//Buffer pieno
		{
			Resize( 2*size +1 );
		}
		count++;
		if(index == count)
		{
			head = (size + head -1) % size;
			elements[head] = std::move(dat);
		}
		else
		{
			for(unsigned long int i=count-1; i>index; i--)
				at(i) = (*this)[i-1];
			at(index) = std::move(dat);	
		}
		return true;
	}

	template<typename Data>
	inline bool SetVec<Data> :: Remove(const Data& dat)
	{
		unsigned long int i = binSearch(dat);
		if((*this)[i] != dat)
			return false;
		for(;i < count-1; i++)
			at(i) = (*this)[i+1];
		count--;
		return true;
	}

	template<typename Data>
	inline const Data& SetVec<Data> :: operator[](unsigned long int i)  const
	{
		if(i >= count)
			throw std :: out_of_range("Indice errato");
		return elements[ (head + i ) % size ];
	}

	// ResizableContainer function
	template<typename Data>
	inline void SetVec<Data> :: Resize(unsigned long int N)
	{
		Data *vec = nullptr; 
		if(N==0)
			count = 0;
		else
		{
			vec = new Data[N];
			if(count > N)
				count = N;
			if(elements)
			{
				for(unsigned long int i=0; i<count; i++)
					vec[i] = (*this)[i];// elements[ (head+i)%size ];
			}
		}
		delete[] elements;
		elements = vec;
		head = 0;
		size = N;
	}

	template<typename Data>
	inline void SetVec<Data> :: Clear() noexcept
	{	Resize(0);	}

	
	//Auxiliary functions
	template<typename Data>	//binary search, return size if dat will not be found
	inline unsigned long int SetVec<Data> :: binSearch( const Data& dat) const
	{
		unsigned long int i=0, j=count, q=0;
		while( i < j){
			q = (i+j)/2;
			if( (*this)[q] == dat )
				return q;
			else if ( (*this)[q] < dat )
				i = q + 1;
			else
				j = q;
		}
		return i;	// se dat non e presente
	}

	template<typename Data>
	inline Data& SetVec<Data> :: at(unsigned long int i) 
	{
		if(i >= count)
			throw std :: out_of_range("Indice errato");
		return elements[ (head + i) % size ];
	}

	template<typename Data>
	inline unsigned long int SetVec<Data> :: predecessorPos(const Data& dat) const 
	{
		unsigned long int i = binSearch(dat);
		if(Empty() || dat <= (*this)[0] )
			throw std::length_error("Non esiste il predecessore.");
		if(count == i || (*this)[i] == dat)
			i--;
		return i;
	}

	template<typename Data>
	inline unsigned long int SetVec<Data> :: successorPos(const Data& dat) const 
	{
		if(Empty() || dat >= (*this)[count-1] )
			throw std::length_error("Non esiste il sucecessore.");
		unsigned long int i = binSearch(dat);
		if( (*this)[i] == dat)
			i++;
		return i;
 	}
}