
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../zlasdtest/container/traversable.hpp"
#include "../heap/vec/heapvec.hpp"
#include <string>
#include <cassert>
#include <ctime>

/* ************************************************************************** */
template<class T>
void PrintAllTraverse(const lasd::Vector<T>& c);

template<class T>
void PrintFunc(const T& val);

void HeapVectIntTest();

void HeapVecDoubleTest();

void HeapVecStringTest();

void mytest();

template<class T>
bool Is_Sorted(const lasd::Vector<T>& c);

/* ************************************************************************** */

#endif
