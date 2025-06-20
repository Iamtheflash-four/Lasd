
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/linear.hpp"
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : 
  virtual public OrderedDictionaryContainer<Data>,
  virtual public LinearContainer<Data>, 
  virtual public ClearableContainer
{
  // Must extend OrderedDictionaryContainer<Data>,
  //             LinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Set() =default;

  /* ************************************************************************ */
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;
  // Copy assignment
  Set& operator=(const Set<Data>&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Set& operator=(Set<Data>&&)  noexcept =delete; // Move assignment of abstract types is not possible.

};

/* ************************************************************************** */

}

#endif
// lista 2 nodi
