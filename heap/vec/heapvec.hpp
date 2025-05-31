
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */
#include "../../vector/vector.hpp"
#include "../heap.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>, virtual public SortableVector<Data>
{
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elements;
  // ...

public:

  // Default constructor
  HeapVec() =default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&&) noexcept; // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec<Data>&);

  // Move constructor
  HeapVec(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() =default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec<Data>& operator=(const HeapVec<Data>&);

  // Move assignment
	HeapVec<Data>& operator=(HeapVec<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
	  bool operator==(const HeapVec<Data>&) const noexcept;
  	bool operator!=(const HeapVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override; // Override Heap member

  void Heapify() noexcept override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

  using Container::Size;
protected:

  // Auxiliary functions, if necessary!
  void Heapify(unsigned long int) noexcept;
	bool isLeftNode(unsigned long int) const noexcept;
	bool isRigthNode(unsigned long int) const noexcept;
};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
