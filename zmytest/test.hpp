
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../zlasdtest/container/traversable.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include "../pq/heap/pqheap.hpp"
#include <string>
#include <cassert>
#include <ctime>
#include <cctype>

/* ************************************************************************** */
template<class T>
void PrintAllTraverse(const lasd::LinearContainer<T>& c);

template<class T>
void PrintFunc(const T& val);

void HeapVectIntTest();

void HeapVecDoubleTest();

void HeapVecStringTest();

void HeapVecSortTest();

void PQTestInt();

template <class T>
void myTestDictionaryC();

void myTestSet();

template<class T>
bool EqualLinearC( const lasd::LinearContainer<T>& c1, const lasd::LinearContainer<T>& c2);

template<class T>
bool NotEqualLinearC( const lasd::LinearContainer<T>& c1, const lasd::LinearContainer<T>& c2);

template<class T>
void myTraversableTestInt(const lasd::LinearContainer<T>&);

void myTraversableTestInt1();

void myTraversableTestInt2();


template <class T>
void myMappableTestString();

void mytest1();

void mytest2();

void mytest();

template<class T>
bool Is_Sorted(const lasd::Vector<T>& c);

template< class T>
void Increment(T&);

template<class T>
bool parity(const T& val, bool inival);

template<class T>
T sumMultiple3(const T&, T&);

/* ************************************************************************** */

#endif
