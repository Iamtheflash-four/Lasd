
#include <iostream>
#include "test.hpp"

/* ************************************************************************** */

// #include "..."

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */
void mytest() {
  srand(time(NULL));
  mytest1();
  mytest2();
  std::cout << "\nMytest completo";
}

void mytest1()
{
  myTraversableTestInt1();
  std::cout << "\nTest TraversableContainer<int> completo, nessun errore.";
  
  std::cout << "\nTest MappableContainer<string> su Vector.\n";
  myMappableTestString<lasd::Vector<std::string>>();

  std::cout << "\nTest MappableContainer<string> su List.\n";
  myMappableTestString<lasd::List<std::string>>();

  std::cout << "\nTest MappableContainer<string> completo, nessun errore.";

  myTestSet();
  std::cout << "\nTest Set<int>completo, nessun errore.";

  myTestDictionaryC<lasd::SetVec<int>>();
  std::cout << "\nTest SetVec<int>completo, nessun errore.";

  myTestDictionaryC<lasd::SetLst<int>>();
  std::cout << "\nTest SetLst<int>completo, nessun errore.";

  std::cout << "\nMytest1 completo";
}

void mytest2()
{
  std::cout << "Test HeapVec<Int>\n";
  HeapVectIntTest();

  std::cout << "Test HeapVec<Double>\n";
  HeapVecDoubleTest();

  std::cout << "Test HeapVec<String>\n";
  HeapVecStringTest();

  HeapVecSortTest();
  std::cout << "\nTest Sort completo, nessun errore.";

  PQTestInt();
  std::cout << "\nTest PQ<int>completo, nessun errore.n";

  myTraversableTestInt2();
  std::cout << "\nTest TraversableContainer<int> completo, nessun errore.";

  std::cout << "\nTest MappableContainer<string> su Heapvec.\n";
  myMappableTestString<lasd::HeapVec<std::string>>();


  std::cout << "\nTest MappableContainer<string> completo, nessun errore.";

  std::cout << "\nMytest2 completo";
}

void HeapVectIntTest()
{
  lasd::Vector<int> vec(10);
  for(unsigned int i=0; i<vec.Size(); i++)
  	vec[i] = 2*i;

  std::cout << "Traverse on Vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<int> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<int> heap2(std::move(vec));
  
  std::cout << "Traverse on Vector heap2...\n";
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
  std::cout << "HeapSort:\n";
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

  std::cout << "\nTraverse on Vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'

  heap2.Clear();
  assert(heap2.Empty());
  heap2.Heapify();
  assert(heap2.IsHeap());

  std::cout << "HeapVec su int completo\n";
}

void HeapVecDoubleTest()
{
  lasd::Vector<double> vec(10);
  for(unsigned int i=0; i<vec.Size(); i++)
  	vec[i] = 3.5 * (double) i;

  std::cout << "Traverse on Vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<double> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<double> heap2(std::move(vec));
  
  std::cout << "Traverse on Vector heap2...\n";
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
  std::cout << "HeapSort:\n";
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

  std::cout << "\nTraverse on Vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'

  int sum = 0;
  sum = heap1.Fold(&FoldAdd<double>, sum);
  std::cout << "Somma elementi heap1: " << sum << std::endl;
  std::cout << "HeapVec su double completo\n";
}

void HeapVecStringTest()
{
  lasd::Vector<std::string> vec(10);
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

  std::cout << "Traverse on Vector vec...\n";
  PrintAllTraverse(vec);

  lasd::HeapVec<std::string> heap1(vec);

  assert( heap1.IsHeap() );
  assert( !vec.Empty() );
  assert( !heap1.Empty() );
   
  
  lasd::HeapVec<std::string> heap2(std::move(vec));
  
  std::cout << "Traverse on Vector heap2...\n";
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
  
  heap2[0] = ""; 
  assert( heap2.IsHeap() );
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
      val = std::string();
      for (int i = 0; i < 5; ++i)
        val += (char) ((rand() % 26) + 97);  //Letta minuscola random
    }
  );

  heap1 = lasd::HeapVec<std::string>(vec);
  heap1.Sort();
  assert( Is_Sorted(heap1) );

  heap1.Resize(10);
  std::cout << "Traverse on heap1..\n";
  PrintAllTraverse(heap1);

  lasd::HeapVec<std::string> heap5(vec);
  assert( !vec.Empty() );
  assert( !heap5.Empty() );
  assert( vec.Size() == heap5.Size() );
  assert( heap5.IsHeap());

  heap5.Heapify();
  std::cout << "Costruzuine Heap:\n";
  PrintAllTraverse(heap5);

  heap5.Sort();
  std::cout << "HeapSort:\n";
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

  std::cout << "\nTraverse on Vector heap2...\n";
  PrintAllTraverse(heap2);

  assert( heap1 == heap2);
  assert( heap2 == heap1);  //Commutativita'
  
  std::cout << "HeapVec su stringhe completo\n";
}

void HeapVecSortTest()
{
  lasd::Vector<int> vec(10);
  for(unsigned i=0; i<vec.Size(); i++)
    vec[i] = i+1;
  lasd::HeapVec<int> heap1(vec);
  heap1.Sort();
  assert(Is_Sorted(heap1));

  vec[0] = 6; vec[9] = 0;
  for(unsigned i=1; i<vec.Size()-1; i++)
    vec[i] = 3;
  heap1.Sort();
  assert(Is_Sorted(heap1));

  lasd::Vector<int> vec2(10);
  for(unsigned i= vec2.Size() -1; i>0; i--)
    vec2[i-1] = i;
  lasd::HeapVec<int> heap2(vec2);
  heap2.Sort();
  assert(Is_Sorted(heap2));

  lasd::Vector<int> duplicati(11);
  int duplicates[] = {3, 7, 7, 1, 1, 4, 4, 9, 9, 2, 2};
  for (int i = 0; i < 11; i++) 
    duplicati[i] = duplicates[i];
  lasd::HeapVec<int> heap3( std::move(duplicati) );
  heap3.Sort();
  assert( Is_Sorted(heap3) );
  
  for (int i = 4; i <= 20; i++) 
  {
    lasd::Vector<int> randVec(20);
    for (int j = 0; j < 20; j++) 
        randVec[j] = rand() % 100; 
    lasd::HeapVec<int> heap1(randVec);
    heap1.Sort();
    assert(Is_Sorted(heap1));
  }
  
  for (int i = 21; i <= 30; i++) 
  {
    lasd::Vector<float> randVec(20);
    for (int j = 0; j < 20; j++) 
      randVec[j] = static_cast<float>(rand() % 100) / 10.0; // Float tra 0.0 e 9.9
      
    lasd::HeapVec<float> heap1(randVec);
    heap1.Sort();
    assert(Is_Sorted(heap1));
  }
  
  for (int i = 31; i <= 40; i++) 
  {
    lasd::Vector<double> randVec(20);
    for (int j = 0; j < 20; j++) 
      randVec[j] = (rand() % 200) - 100; // Double tra -100 e 100
    
    lasd::HeapVec<double> heap1(randVec);
    heap1.Sort();
    assert(Is_Sorted(heap1));
  }
  
  const char* stringSets[5][5] = 
  {
      {"banana", "apple", "cherry", "date", "fig"},
      {"zebra", "lion", "tiger", "elephant", "giraffe"},
      {"aaa", "ccc", "bbb", "eee", "ddd"},
      {"car", "bus", "bike", "truck", "plane"},
      {"dog", "cat", "mouse", "rabbit", "fox"}
  };
  for (int i = 0; i < 5; i++) 
  {
    lasd::Vector<std::string> stringData(5);
    for (int j = 0; j < 5; j++) 
      stringData[j] = stringSets[i][j];
    lasd::HeapVec<std::string> heap1(stringData);
    heap1.Sort();
    assert(Is_Sorted(heap1));
  }
  
  lasd::HeapVec<int> heap1Empty{};
  heap1Empty.Sort();
  assert( Is_Sorted(heap1Empty) ); 

  lasd::Vector<int> singleton(1);
  singleton[0] = 42;
  lasd::HeapVec<int> heapSingle(singleton);
  heapSingle.Sort();
  assert( Is_Sorted(heapSingle) );

  lasd::Vector<int> twoElements(2);
  twoElements[0] = 99;
  twoElements[1] = -99;
  lasd::HeapVec<int> heap1Two(twoElements);
  heap1Two.Sort();
  assert(Is_Sorted(heap1Two));

  std::cout << "Tutti i test di Sort completati con successo!\n";
}

void PQTestInt()
{
  lasd::List<int> ls;
  for(int i=0; i<10; i++)
    ls.InsertAtBack(i*3);

  std::cout << "Traverse ls\n";
  PrintAllTraverse(ls);
  assert(ls.Size() == 10);
  assert( !ls.Empty() );
  
  lasd::PQHeap<int> pq1(ls), pq2( std::move(ls) );
  assert(pq1.Size() == 10);
  assert( !pq2.Empty() );
  assert(pq1.IsHeap());

  assert(pq2.Size() == 10);
  assert( !pq2.Empty() );
  assert(pq2.IsHeap());

  std::cout << "Traverse pq1\n";
  PrintAllTraverse(pq1);

  std::cout << "Traverse pq2\n";
  PrintAllTraverse(pq1);

  pq1 = ls, pq2 = std::move(ls);
  assert(pq1.Size() == 10);
  assert( !pq2.Empty() );
  assert(pq1.IsHeap());

  assert(pq2.Size() == 10);
  assert( !pq2.Empty() );
  assert(pq2.IsHeap());

  //Test random numer
  for(unsigned i=0; i<10; i++)
  {
    lasd::Vector<int> v(100);
    assert( v.Size()==100 );

    for(unsigned j=0; j<v.Size(); j++)
      v[i] = rand() % 10000-50000;

    lasd::HeapVec<int> heap(std::move(v) );
    assert( !heap.Empty() );
    assert( heap.Size() == 100);
    assert(heap.IsHeap());

    lasd::PQHeap<int> queue(std::move(v) );
    assert( !queue.Empty() );
    assert( queue.Size() == 100);
    assert( queue.IsHeap() );
  }

  for(unsigned i=0; i<100; i++)
  {
    lasd::PQHeap<int> pq3;
    assert( pq3.Empty() );
    assert( pq3.Size() == 0 );
    
    for(unsigned j=0; j<100; j++)
    {
      int val = rand() % 10000 -50000; 
      pq3.Insert( val );
    }
    assert( !pq3.Empty() );
    assert( pq3.Size() == 100);
    assert( pq3.IsHeap() );
    
    for(unsigned j=0; j<100; j++)
    {
      int val = rand() % 10000 - 5000; 
      pq3.Change(j, val);
      pq3.IsHeap();
    }
    assert( !pq3.Empty() );
    assert( pq3.Size() == 100);
    assert( pq3.IsHeap() );
  
    lasd::PQHeap<int> pq4;
    assert( pq4.Empty() );
    assert( pq4.Size() == 0);
    assert( pq4.IsHeap() );

    for(unsigned j=0; j<100; j++)
    {
      int val = rand() % 10000 - 5000; 
      pq4.Insert( std::move(val) );
    }

    assert( !pq4.Empty() );
    assert( pq4.Size() == 100);
    assert( pq4.IsHeap() );
  
    for(unsigned j=0; j<100; j++)
    {
      int val = rand() % 10000 - 5000; 
      pq4.Change(j, std::move(val) );
      pq4.IsHeap();
    }
    assert( !pq4.Empty() );
    assert( pq4.Size() == 100);
    assert( pq4.IsHeap() );

    pq1 = pq3;
    assert(pq1 == pq3);
    
    pq2 = std::move( pq3 );
    assert(pq1 == pq2);
    assert(pq1 != pq3);
    lasd::PQHeap<int> pq5( std::move(pq3) );
    assert( pq3.Empty() );
  }
}

void myTestSet()
{
  for(unsigned i=0; i<20;  i++)
	{
		lasd::Vector<int> vec(20);
		assert( !vec.Empty() );
		assert( vec.Size() == 20 );
		
		lasd::SetVec<int> st1, st2;
		assert( st1.Empty() && st2.Empty() );
		assert( st1.Size() == 0 && 0 == st2.Size() );
    assert( st1==st2 );

    lasd::SetLst<int> lst1, lst2;
		assert( lst1.Empty() && lst2.Empty() );
		assert( lst1.Size() == 0 && 0 == lst2.Size() );
    assert( lst1==lst2 );
		
    assert( EqualLinearC(st1, lst1) );
    assert( EqualLinearC(st2, lst2) );

    for(unsigned j=0; j<vec.Size(); j++)
		{
			int val = rand()% 100-500;
      vec[j] = val;
    }

    for(unsigned j=0; j<vec.Size(); j++)
    { 
      assert( !st1.Exists(vec[j]) == st1.Insert(vec[j]) );
      assert( !lst1.Exists(vec[j]) == lst1.Insert(vec[j]) );

      assert( !st2.Exists(vec[j]) == st2.Insert( std::move(vec[j])) );
      assert( !lst2.Exists(vec[j]) == lst2.Insert(std::move(vec[j])) );

    }

		assert( st1.Size() == lst1.Size() );	
    assert( st2.Size() == lst2.Size() );

    assert( EqualLinearC(st1, lst1) );
    assert(EqualLinearC(st1, lst2));

    lasd::SetLst<int> lst3( std::move(vec)), lst4 = (std::move(lst3));
    assert( NotEqualLinearC(lst3, lst4) );
    assert( lst3.Empty() );
	}

  lasd::SetVec<int> setVec1, setVec2;
  lasd::SetLst<int> setLst1, setLst2;

  assert(setVec1 == setVec2);
  assert(setLst1 == setLst2);
  assert( EqualLinearC(setVec1,setLst1) );

  setVec1.Insert(5);
  setLst1.Insert(5);
  assert( EqualLinearC(setVec1, setLst1));

  setVec2.Insert(7);
  assert(NotEqualLinearC(setVec1, setVec2));

  setVec1.Insert(3);
  setLst1.Insert(3);
  assert( EqualLinearC(setVec1, setLst1));

  setVec1.Remove(5);
  assert( NotEqualLinearC(setVec1, setLst1));

  assert(setLst1.Min() == 3);
  assert(setLst1.Max() == 5);

  lasd::SetVec<int> sv1, sv2;
  lasd::SetLst<int> sl1, sl2;

  assert(sv1 == sv2);
  assert(sl1 == sl2);
  assert( EqualLinearC(sv1,sl1) ); 

  sv1.Insert(5);
  sl1.Insert(5);
  assert( EqualLinearC(sv1,sl1) );  

  sv2.Insert(5);
  sv2.Insert(3);
  sl2.Insert(3);
  sl2.Insert(5);
  assert( EqualLinearC(sv2, sl2) ); 
  
  sv2.Insert(10);
  assert( NotEqualLinearC(sv2, sl2) );

  sl2.Remove(3);
  assert( NotEqualLinearC(sv2, sl2) );

  sv1.Insert(7);
  sl1.Insert(7);
  sv1.Remove(5);
  sl1.Remove(5);
  assert( EqualLinearC(sv1, sl1) );

  int minVec = sv1.Min();
  int minLst = sl1.Min();
  assert(minVec == minLst);

  lasd::SetVec<int> sv;
  lasd::SetLst<int> sl;
  assert( EqualLinearC(sv, sl) ); 

  lasd::Set<int>& set1 = sv;
  lasd::Set<int>& set2 = sl;
  assert(set1 == set2);
}

void myTraversableTestInt1()
{
  lasd::Vector<int> vec(50);
  for(unsigned i =0; i<vec.Size(); i++)
    vec[i] = 2*i;

  vec.Map(&Increment<int>);
  assert( vec.Fold( &parity<bool>, false) == false );

  lasd::SetVec<int> st1 (std::move(vec)); 
  myTraversableTestInt(st1);
  

  lasd::SetLst<int> lst1 (std::move(vec)); 
  myTraversableTestInt(lst1);

  lasd::List<int> lst, ls2;
  assert(lst.Empty());
  for(unsigned i =0; i<vec.Size(); i++)
    lst.InsertAtBack(2*i);

  lst.Map(&Increment<int>);
  assert( lst.Fold(&parity<bool>, false) == false );

  for(unsigned i =vec.Size(); i>0; i--)
    ls2.InsertAtFront(2*(i-1));

  ls2.Map(&Increment<int>);
  assert( ls2.Fold(&parity<bool>, false) == false );

  assert(lst == ls2);

  lasd::SetVec<int> st2 (std::move(lst)); 
  myTraversableTestInt(st2);
  
  lasd::SetLst<int> lst2 (std::move(lst)); 
  myTraversableTestInt(lst2);
}

template<class T>
void myTraversableTestInt(const lasd::LinearContainer<T>& con)
{
  for(unsigned i =0; i<con.Size(); i++)
  {
    if( i%2 == 0)
      assert( !con.Exists(i) );
    else
      assert( con.Exists(i) );
  }

  int sum = con.Fold(&sumMultiple3<int>, 0);
  assert( sum == 867 );
  
  sum = con.PreOrderFold(&sumMultiple3<int>, 0);
  assert( sum == 867 );

  sum = con.PostOrderFold(&sumMultiple3<int>, 0);
  assert( sum == 867 );
}

void myTraversableTestInt2()
{
  lasd::Vector<int> vec(50);
  for(unsigned i =0; i<vec.Size(); i++)
    vec[i] = 2*i;

  vec.Map(&Increment<int>);
  assert( vec.Fold( &parity<bool>, false) == false );

  lasd::PQHeap<int> pq1 (std::move(vec)); 
  myTraversableTestInt(pq1);

  lasd::HeapVec<int> hp1 (std::move(vec)); 
  myTraversableTestInt(hp1);
}

template<class T>
void myTraversableTestInt2(const lasd::LinearContainer<T>& con)
{

}

template <class T>
void myMappableTestString()
{
  lasd::Vector<std::string> vec(10);
  vec[0] = "a";
  vec[1] = "b";
  vec[2] = "c";
  vec[3] = "d";
  vec[4] = "e";
  vec[5] = "f";
  vec[6] = "g";
  vec[7] = "h";
  vec[8] = "i";
  vec[9] = "j";

  T container1(vec), container2(std::move(vec)), container3 = container1;
  container1.Map(
    [](std::string& str ){
      str = toupper(str[0]);
    }
  );
  
  container2.PreOrderMap(
    [](std::string& str ){
      str = toupper(str[0]);
    }
  );

  container3.PostOrderMap(
    [](std::string& str ){
      str = toupper(str[0]);
    }
  );
  
  PrintAllTraverse(container3);
}

template<class T>
void myTestDictionaryC()
{
  T set;
  assert(set.Empty());
  assert(set.Size() == 0);

  assert(set.Insert(10));
  assert(set.Insert(5));
  assert(!set.Insert(10)); // niente duplicati
  assert(set.Size() == 2);

  assert(set.Exists(5));
  assert(!set.Exists(99));

  assert(set.Min() == 5);
  assert(set.Max() == 10);

  assert(set[0] == 5);
  assert(set[1] == 10);
  try {
      set[100];
      assert(false); 
  } catch (const std::out_of_range& e) {}

  assert(set.Successor(5) == 10);
  assert(set.Predecessor(10) == 5);
  try {
      set.Predecessor(5);
      assert(false);
  } catch (const std::length_error&) {}

  try {
      set.Successor(10);
      assert(false);
  } catch (const std::length_error&) {}
  
  assert(set.Remove(5));
  assert(!set.Remove(5));
  assert(set.Size() == 1);
  
  set.Insert(7);
  set.Insert(15);
  
  assert(set.MinNRemove() == 7);
  assert(set.MaxNRemove() == 15);
  
  assert(set.Size() == 1);
  set.Insert(20);
  set.RemoveMin();
  assert(set.Size() == 1);
  set.RemoveMax();
  assert(set.Size() == 0);
  
  set.Insert(1);
  set.Insert(2);
  
  set.Clear();
  assert(set.Empty());
  
  try{
    set.Predecessor(9);
    assert(false);
  }catch(std::length_error&) {}
  
  try{
    set.Successor(9);
    assert(false);
  }catch(std::length_error&) {}
    
  T set2;
  set2.Insert(99);
  
  assert(set != set2);
  set.Insert(99);
  assert(set == set2);
  
  assert(set.Predecessor(100) == 99); 
  assert(set.Successor(7) == 99);

  lasd::Vector<int> vec(20);
  for(unsigned i=0; i<vec.Size(); i++)
    vec[i] = (vec.Size() - i) *2;

  set.Clear();
  set2.Clear();
  assert(set.Empty());
  assert(set2.Empty());

  assert( set.InsertAll(vec) );
  assert(set.Size() == 20);
 
  assert( set2.InsertAll(std::move(vec)) );
  assert(set2.Size() == 20);

  assert(set == set2);
}

template<class T>
bool EqualLinearC( const lasd::LinearContainer<T>& c1, const lasd::LinearContainer<T>& c2)
{
  return c1 == c2;
}

template<class T>
bool NotEqualLinearC( const lasd::LinearContainer<T>& c1, const lasd::LinearContainer<T>& c2)
{
  return c1 != c2;
}

template<class T>
bool parity(const T& val, bool inival)
{
  return inival && (val%2) == 0;
}

template<class T>
void PrintFunc(const T& val)
{
  std::cout << val <<", ";
}

template<class T>
void PrintAllTraverse(const lasd::LinearContainer<T>& c)
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

template< class T>
void Increment(T& val)
{
  val++;
}

template<class T>
bool Is_Sorted(const lasd::Vector<T>& c)
{
  if( c.Empty() )
    return true;
  for(unsigned long i=0; i<c.Size()-1; i++)
    if(c[i] > c[i+1])
      return false;
  return true;
}

template <class T>
T sumMultiple3(const T& val, T& sum)
{
  if(val %3 ==0)
    sum+=val;
  return sum;
}

// int main()
// {
//   mytest();
// }