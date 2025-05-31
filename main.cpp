
#include "zlasdtest/test.hpp"
#include "set/vec/setvec.hpp"
#include "set/lst/setlst.hpp"
#include "heap/vec/heapvec.hpp"
#include "zmytest/test.hpp"
#include <cassert> 
#include <ctime>
/* ************************************************************************** */

#include <iostream>
#include "zlasdtest/container/traversable.hpp"
/* ************************************************************************** */


int main() {
  std::cout << "LASD Libraries 2025" << std::endl;
  //lasdtest();
  lasd::Vector<int> v(10);
  for(int i=0; i<10; i++)
    v[i] = 2*i;

  lasd::SetLst<int> s(std::move(v));

  for(int i=0; i<10; i++)
    std::cout << s[i] << ", ";
  std::cout << "\nConcluso";
  
  
  
  
  return 0;
  
  
}
