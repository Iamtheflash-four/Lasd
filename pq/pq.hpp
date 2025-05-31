
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : virtual public LinearContainer<Data>, ClearableContainer
{
  // Must extend LinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
 virtual ~PQ() specifiers

  /* ************************************************************************ */

  // Copy assignment
  PQ& operator=(const PQ&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PQ& operator=(PQ&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Tip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveTip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type TipNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)

  // type Insert(argument) specifiers; // Copy of the value
  // type Insert(argument) specifiers; // Move of the value

  // type Change(argument) specifiers; // Copy of the value
  // type Change(argument) specifiers; // Copy of the value

};

/* ************************************************************************** */

}

#endif
