
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, virtual protected HeapVec<Data>
{
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  using Container::size;
	unsigned long int capacity=0;	
  using Vector<Data>::elements;

public:

  // Default constructor
  PQHeap() =default;

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data>&&) noexcept; // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap<Data>&) ;

  // Move constructor
  PQHeap(PQHeap<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() =default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap<Data>& operator=(const PQHeap<Data>&);

  // Move assignment
  PQHeap<Data>& operator=(PQHeap<Data>&&) noexcept;

  void Clear() noexcept override;
  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)
  using Container::Size;
  using Container::Empty;
  using HeapVec<Data>::IsHeap;
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;
  using Vector<Data>::Exists;

  const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data&) override; // Override PQ member (Copy of the value)
  void Insert(Data&&) noexcept override; // Override PQ member (Move of the value)

  void Change(unsigned long int, const Data&) override; // Override PQ member (Copy of the value)
  void Change(unsigned long int, Data&&) noexcept override; // Override PQ member (Move of the value)

  const Data& operator[](unsigned long int) const override; 

protected:
  void HeapifyUp(unsigned long int) noexcept;
  void Resize(unsigned long int);
};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
