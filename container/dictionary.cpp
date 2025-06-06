#include "dictionary.hpp"
namespace lasd {

/* ************************************************************************** */

//OrderedDictionaryContainer
   template<typename Data>
   bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& con) 
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = Insert(dat) && all ;
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data> :: InsertAll(MappableContainer<Data>&& con) noexcept
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = Insert(std::move(dat)) && all ;
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& con) 
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = Remove(dat) && all  ;
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = Insert(dat) || inserted ;
         }
      );
      return inserted; 
   }

   template<typename Data>
   bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = Insert( std::move(dat)) || inserted;
         }
      );
      return inserted;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = Remove(dat) || inserted;
         }
      );
      return inserted;
   }
/* ************************************************************************** */

}
