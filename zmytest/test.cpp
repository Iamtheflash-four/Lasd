
#include <iostream>
#include "test.hpp"

/* ************************************************************************** */

// #include "..."

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */
void mytest() {
  std::cout << "Test HeapVec<Int>\n";
  //HeapVectIntTest();

  std::cout << "Test HeapVec<Double>\n";
  HeapVecDoubleTest();

  std::cout << "Test HeapVec<String>\n";
  HeapVecStringTest();

  //HeapVecSortTest();
  std::cout << "\nTest completo, nessun errore.";
}

void HeapVectIntTest()
{
  lasd::Vector<int> vec(10);
  for(unsigned int i=0; i<vec.Size(); i++)
  	vec[i] = 2*i;

  srand(time(NULL));

  std::cout << "Traverse on vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<int> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<int> heap2(std::move(vec));
  
  std::cout << "Traverse on vector heap2...\n";
  PrintAllTraverse(heap2);

 	assert( !heap2.Empty() );
 	
  lasd::HeapVec<int> heap3 (std::move(heap1) );
 	assert( heap1.Empty() ); 
 	assert( !heap3.Empty() );
 	assert( heap3 == heap2);
  assert( heap3 != heap1);
 	
  assert( heap1.IsHeap() );
  assert( heap2.IsHeap() );
  assert( heap3.IsHeap() );

  heap3[0] = 0;
  assert( !heap3.IsHeap() );
  heap3.Resize(1);
  assert( !heap3.Empty() );
  assert( heap3.IsHeap() );
  
  heap2.Resize(1);
  assert( !heap2.Empty() );
  assert( heap2 != heap3);
  heap2[0] = 10; 
  assert( heap2.IsHeap() );
  
  heap2[0] = 0; 
  assert( heap2 == heap3);

  heap3.Resize(0);
  assert( heap3.Empty() );
  assert( heap3.IsHeap() );
  assert( heap2 != heap3);

  heap2.Resize(0);
  assert( heap2 == heap3);

  vec.Clear();
  assert( vec.Empty() );
  assert( vec.Size() == 0 );

  vec.Resize(100);
  assert( !vec.Empty() );
  assert( vec.Size() == 100 );

  vec.Map(
    [](int& val){
      val = rand() % 40 - 20;
    }
  );

  std::cout << "Traverse on vec..\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<int> heap5(vec);
  heap5.Map(
    [](int& val){
      val = rand() % 40 - 20;
    }
  );

  heap5.Heapify();
  std::cout << "Costruzuine Heap:\n";
  PrintAllTraverse(heap5);

  heap5.Sort();
  std::cout << "Heapsort:\n";
  PrintAllTraverse(heap5);
  assert(Is_Sorted(heap5));

  assert( !vec.Empty() );
  assert( !heap5.Empty() );

  heap1 = heap5;
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
  assert( heap1 == heap5); 

  heap1.Heapify();
  assert( heap1.IsHeap() );
  

  heap2 = ( std::move(heap5) );
  assert( !vec.Empty() );
  assert( heap5.Empty() );
  heap2.Heapify();
  assert( heap2.IsHeap() );

  assert( heap1 != heap5);  
  assert( heap2 != heap5);  
  assert( heap5 != heap1);  //Commutativita'
  assert( heap5 != heap2);  

  std::cout << "\nTraverse on heap1...\n";
  PrintAllTraverse(heap1); 

  std::cout << "\nTraverse on vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'

  std::cout << "Somma elementi heap1: " << sum << std::endl;
}

void HeapVecDoubleTest()
{
  lasd::Vector<double> vec(10);
  for(unsigned int i=0; i<vec.Size(); i++)
  	vec[i] = 3.5 * (double) i;

  srand(time(NULL));

  std::cout << "Traverse on vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<double> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<double> heap2(std::move(vec));
  
  std::cout << "Traverse on vector heap2...\n";
  PrintAllTraverse(heap2);

 	assert( !heap2.Empty() );
 	
  lasd::HeapVec<double> heap3 (std::move(heap1) );
 	assert( heap1.Empty() ); 
 	assert( !heap3.Empty() );
 	assert( heap3 == heap2);
  assert( heap3 != heap1);
 	
  assert( heap1.IsHeap() );
  assert( heap2.IsHeap() );
  assert( heap3.IsHeap() );

  heap3[0] = 0;
  assert( !heap3.IsHeap() );
  heap3.Resize(1);
  assert( !heap3.Empty() );
  assert( heap3.IsHeap() );
  
  heap2.Resize(1);
  assert( !heap2.Empty() );
  assert( heap2 != heap3);
  heap2[0] = 10; 
  assert( heap2.IsHeap() );
  
  heap2[0] = 0; 
  assert( heap2 == heap3);

  heap3.Resize(0);
  assert( heap3.Empty() );
  assert( heap3.IsHeap() );
  assert( heap2 != heap3);

  heap2.Resize(0);
  assert( heap2 == heap3);

  vec.Clear();
  assert( vec.Empty() );
  assert( vec.Size() == 0 );

  vec.Resize(100);
  assert( !vec.Empty() );
  assert( vec.Size() == 100 );

  vec.Map(
    [](double& val){
      val = (rand() % 120 - 60) * 4.5;
    }
  );

  std::cout << "Traverse on vec..\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<double> heap5(vec);
  heap5.Map(
    [](double& val){
      val = ( rand() % 40 - 20 ) * 2.9;
    }
  );

  heap5.Heapify();
  std::cout << "Costruzuine Heap:\n";
  PrintAllTraverse(heap5);

  heap5.Sort();
  std::cout << "Heapsort:\n";
  PrintAllTraverse(heap5);
  assert(Is_Sorted(heap5));

  assert( !vec.Empty() );
  assert( !heap5.Empty() );

  heap1 = heap5;
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
  assert( heap1 == heap5); 

  heap1.Heapify();
  assert( heap1.IsHeap() );
  

  heap2 = ( std::move(heap5) );
  assert( !vec.Empty() );
  assert( heap5.Empty() );
  heap2.Heapify();
  assert( heap2.IsHeap() );

  assert( heap1 != heap5);  
  assert( heap2 != heap5);  
  assert( heap5 != heap1);  //Commutativita'
  assert( heap5 != heap2);  

  std::cout << "\nTraverse on heap1...\n";
  PrintAllTraverse(heap1); 

  std::cout << "\nTraverse on vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'

  unsigned int a, b; 
  int sum = 0;
  sum = heap1.Fold(&FoldAdd<double>, sum);
  std::cout << "Somma elementi heap1: " << sum << std::endl;
}

void HeapVecStringTest()
{
  lasd::Vector<string> vec(10);
  vec[0] = "";
  vec[1] = "Sasy";
  vec[2] = "Emma";
  vec[3] = "sasy";
  vec[4] = "Gimmy";
  vec[5] = "a";
  vec[6] = " ";
  vec[7] = "3j30";
  vec[8] = "11";
  vec[9] = "ily34";

  srand(time(NULL));

  std::cout << "Traverse on vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<string> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<string> heap2(std::move(vec));
  
  std::cout << "Traverse on vector heap2...\n";
  PrintAllTraverse(heap2);

 	assert( !heap2.Empty() );
 	
  lasd::HeapVec<string> heap3 (std::move(heap1) );
 	assert( heap1.Empty() ); 
 	assert( !heap3.Empty() );
 	assert( heap3 == heap2);
  assert( heap3 != heap1);
 	
  assert( heap1.IsHeap() );
  assert( heap2.IsHeap() );
  assert( heap3.IsHeap() );

  heap3[0] = "";
  assert( !heap3.IsHeap() );
  heap3.Resize(1);
  assert( !heap3.Empty() );
  assert( heap3.IsHeap() );
  
  heap2.Resize(1);
  assert( !heap2.Empty() );
  assert( heap2 != heap3);
  heap2[0] = 10; 
  assert( heap2.IsHeap() );
  
  heap2[0] = " "; 
  assert( heap2 == heap3);

  heap3.Resize(0);
  assert( heap3.Empty() );
  assert( heap3.IsHeap() );
  assert( heap2 != heap3);

  heap2.Resize(0);
  assert( heap2 == heap3);

  vec.Clear();
  assert( vec.Empty() );
  assert( vec.Size() == 0 );

  vec.Resize(100);
  assert( !vec.Empty() );
  assert( vec.Size() == 100 );

  vec.Map(
    [](string& val){
      val = string("          ");
      for(unsigned i=0; i<val.size(); i++)
        val[i] = (char) rand()% 128;
    }
  );

  std::cout << "Traverse on vec..\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<string> heap5(vec);
  assert( !vec.Empty() );
  assert( !heap5.Empty() );
  assert( vec.Size() == heap5.Size() );
  assert( heap5.IsHeap());

  heap5.Heapify();
  std::cout << "Costruzuine Heap:\n";
  PrintAllTraverse(heap5);

  heap5.Sort();
  std::cout << "Heapsort:\n";
  PrintAllTraverse(heap5);
  assert(Is_Sorted(heap5));

  assert( !vec.Empty() );
  assert( !heap5.Empty() );

  heap1 = heap5;
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
  assert( heap1 == heap5); 

  heap1.Heapify();
  assert( heap1.IsHeap() );
  

  heap2 = ( std::move(heap5) );
  assert( !vec.Empty() );
  assert( heap5.Empty() );
  heap2.Heapify();
  assert( heap2.IsHeap() );

  assert( heap1 != heap5);  
  assert( heap2 != heap5);  
  assert( heap5 != heap1);  //Commutativita'
  assert( heap5 != heap2);  

  std::cout << "\nTraverse on heap1...\n";
  PrintAllTraverse(heap1); 

  std::cout << "\nTraverse on vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'

  

}

template<class T>
void PrintFunc(const T& val)
{
  std::cout << val <<", ";
}

template<class T>
void PrintAllTraverse(const lasd::Vector<T>& c)
{
  std::cout << "Traverse: ";
  c.Traverse(&PrintFunc<T>);
    std::cout << std::endl;

  std::cout << "Traverse pre order: ";
  c.PreOrderTraverse(&PrintFunc<T>);
    std::cout << std::endl;

  std::cout << "Traverse post order: ";
  c.PostOrderTraverse(&PrintFunc<T>);
    std::cout << std::endl;
  std::cout << "\n\n";
}





template<class T>
bool Is_Sorted(const lasd::Vector<T>& c)
{
  for(unsigned long i=0; i<c.Size()-1; i++)
    if(c[i] > c[i+1])
      return false;
  return true;
}

int main()
{
  mytest();
}