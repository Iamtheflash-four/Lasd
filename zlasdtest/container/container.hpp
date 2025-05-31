
#ifndef CONTAINERTEST_HPP
#define CONTAINERTEST_HPP
#ifndef uint
   #define uint unsigned int
#endif
#ifndef ulong
   #define ulong unsigned long int
#endif
#include "../../container/container.hpp"

/* ************************************************************************** */

// Container member functions!

void Empty(uint &, uint &, const lasd::Container &, bool);

void Size(uint &, uint &, const lasd::Container &, bool, ulong);

/* ************************************************************************** */

#endif
