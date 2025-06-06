#include "setlst.hpp"
namespace lasd {

/* ************************************************************************** */

   template<typename Data>
   SetLst<Data> :: SetLst(const TraversableContainer<Data>& con)
   {
      size = 0;
      head = tail = nullptr;
      con.Traverse(
         [this](const Data& dat)
         {
            Insert(dat);
         }
      );
   }  

   template<typename Data>
   SetLst<Data> :: SetLst(MappableContainer<Data>&& con) noexcept
   {
      size=0;
      head = tail = nullptr;
      con.Map(
         [this](const Data& dat)
         {
            Insert(std::move(dat));
         }
      );
   }

   template<typename Data>
   SetLst<Data> :: ~SetLst() 
   {
      while(head != nullptr)
      {
         typename List<Data>::Node *t = head;
         head = head->next;
         delete t;
      }
   }

   template<typename Data>
   inline SetLst<Data>& SetLst<Data> :: operator=(SetLst<Data>&& ls) noexcept
   {
      std::swap(size, ls.size);
      std::swap(head, ls.head);
      std::swap(tail, ls.tail); 
      return *this;
   }

   template<typename Data>
   inline SetLst<Data>& SetLst<Data> :: operator=(const SetLst<Data>& ls) 
   {
      while(head != nullptr)
      {
         typename List<Data>::Node* t = head;
         head = head->next;
         delete t;
      }
      size = ls.size;
      while(head != nullptr)
      tail = head;
      typename List<Data>::Node *t = head, t2 = ls.head;

      for(unsigned long int i=0; i<size; i++)
      {
         t = new typename List<Data>::Node;
         t->elements = t2->elements;
         t->next = nullptr;
         tail = t;
         t2 = t2->next;
         t = t->next;
      }
      return *this;
   }

   template <typename Data>
   inline bool SetLst<Data> :: operator==(const SetLst<Data>& ls) const noexcept
   {
      return List<Data>::operator==(ls);
   }

   template <typename Data>
   inline bool SetLst<Data> :: operator!=(const SetLst<Data>& ls) const noexcept
   {
      return !((*this) == ls);
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Min() const  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
   {
      if(size==0)
         throw std::length_error("Lista vuota");
      return head->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::MinNRemove() 
   {
      Data t = Min();
      RemoveMin();
      return t;
   }

   template <typename Data>
   inline void SetLst<Data>::RemoveMin() 
   {
      if(size==0)
         throw std::length_error("Lista vuota");
      typename List<Data>::Node* t = head;
      head = head->next;
      delete t;
      size--;
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Max() const  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
   {
      if(size==0)
         throw std::length_error("Lista vuota");
      return tail->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::MaxNRemove() 
   {
      Data t = Max();
      RemoveMax();
      return t;
   }

   template <typename Data>
   inline void SetLst<Data>::RemoveMax() 
   {
      Remove(Max());
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Predecessor(const Data& dat) const 
   {
      typename List<Data>::Node *prev=head, *t = binSearch(dat, &prev);;
      if(size==0 || dat <= head->elements)
         throw std::length_error("Non esiste");
      if(t->elements == dat)
         return prev->elements;
      else if (t->elements < dat)
         return t->elements;
      else
         throw std::length_error("Non esiste");
   }

   template <typename Data>
   inline Data SetLst<Data>::PredecessorNRemove(const Data& dat)
   {
      if(size ==0 || dat <= head->elements)
         throw std::length_error("Non esiste");
      Data elem = Predecessor(dat);
      Remove(elem);
      return elem;
   }

   template <typename Data>
   inline void SetLst<Data> :: RemovePredecessor(const Data& dat)
   {
      if(size ==0 || dat <= head->elements)
         throw std::length_error("Non esiste");
      Remove(Predecessor(dat));
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Successor(const Data& dat) const 
   {
      if(size==0 || tail->elements <= dat)
         throw std::length_error("Non esiste");

      typename List<Data>::Node *t = binSearch(dat, nullptr);
      if(t==nullptr)
         return head->elements;
      if(t->next)                   
         return t->next->elements;  
      else
         return t->elements;  //tail e il successore
   }

   template <typename Data>
   inline Data SetLst<Data>::SuccessorNRemove(const Data& dat)
   {
      if(size==0 || tail->elements <= dat)
         throw std::length_error("Non esiste");
      typename List<Data>::Node *t = binSearch(dat, nullptr), *t2 = t->next;
      Data elem = t2->elements;
      t -> next = t2->next;
      delete t2;
      size--;
      return elem;
   }

   template <typename Data>
   inline void SetLst<Data> :: RemoveSuccessor(const Data& dat)
   {
      if(size==0 || tail->elements <= dat)
         throw std::length_error("Non esiste");
      typename List<Data>::Node *t = binSearch(dat, nullptr), *t2 = t->next;
      t -> next = t2->next;
      delete t2;
      size--;
   }

   template<typename Data>
   inline bool SetLst<Data>::Insert(const Data& dat)
   {
      typename List<Data>::Node  *t = binSearch(dat, nullptr), *newNode;
      if(t!=nullptr && dat == t->elements)
         return false;
      else
      {
         newNode = new typename List<Data>::Node(dat);
         if(t == nullptr)
         {
            newNode -> next = head;
            head = newNode; 
            if(tail == t)
               tail = head;
         }
         else
         {
            newNode->next = t->next;
            t->next = newNode;
            if(tail == t)
               tail = tail->next;
         }
      }
      size++;
      return true;
   }
   
   template<typename Data>
   inline bool SetLst<Data>::Insert(Data&& dat) noexcept
   {
      typename List<Data>::Node *t = binSearch(dat, nullptr), *newNode;
      if(t!=nullptr && dat == t->elements)
         return false;
      else
      {
         newNode = new typename List<Data>::Node(std::move(dat));
         if(t == nullptr)
         {
            newNode -> next = head;
            head = newNode; 
            if(tail == t)
               tail = head;
         }
         else
         {
            newNode->next = t->next;
            t->next = newNode;
            if(tail == t)
               tail = tail->next;
         }
      }
      size++;
      return true;
   }

   template<typename Data>
   inline bool SetLst<Data>::Remove(const Data& dat)
   {
      
      typename List<Data>::Node *prev = nullptr;
      typename List<Data>::Node *t = binSearch(dat, &prev); 
      if ( t == nullptr || t -> elements != dat )
         return false;
      if (t==head)
         head = head->next;
      else
         prev->next = t->next;
      if(tail == t)
         tail = prev;
      delete t;
      size--;
      return true;
   }

   template<typename Data>
   inline const Data& SetLst<Data> :: operator[](unsigned long int i) const 
   {
      if( i>=size)
         throw std::out_of_range("Indice errato");
      typename List<Data>::Node *t = head;
      for(unsigned long j=0; j<i; j++)
         t = t->next;
      return t -> elements;
   }

   template <typename Data>
   inline typename List<Data>::Node* SetLst<Data>::binSearch(const Data& val, typename List<Data>::Node **prev) const
   {
      int i =0, j=size, q =0;
      if( head == nullptr || val < head->elements)
         return nullptr;
      
      typename List<Data>::Node *t = head, *ret = head;
      while( i < j)
      {
         q = (i+j)/2;
         t = getIndex(q, prev);	//Avanza fino a q
         if(t->elements == val)
            return t;
         else if(t->elements < val)
         {
            ret = t;
            i = q + 1;
         } 
         else
            j = q;
      }
      return ret;
   }

   template <typename Data>
   inline typename List<Data>::Node* SetLst<Data>::getIndex(unsigned long int n, typename List<Data>::Node **prev) const
   {
      typename List<Data>::Node* t = head;
      if(prev == nullptr)
         for(unsigned long int i=0; i<n; i++)
            t = t->next;
      else
      {
         for(unsigned long int i=0; i<n; i++)
         {
            *prev = t;
            t = t->next;
         }
      }
      return t;
   }

   template <typename Data>
   inline bool SetLst<Data>::Exists(const Data& dat) const noexcept
   {
      typename List<Data>::Node *t =  binSearch(dat, nullptr);
      return ( t != nullptr && t->elements == dat);
   }
   
   template <typename Data>
   inline void SetLst<Data>::Clear() noexcept
   {
      *this = SetLst<Data>();
   }
/* ************************************************************************** */

}