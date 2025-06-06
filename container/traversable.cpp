#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */
//TraversableContainer method
    template<typename Data>
    inline bool TraversableContainer<Data> :: Exists(const Data& val) const noexcept
    {
        bool found = false;
        Traverse
        (
            [val, &found](const Data& dat)
            {
                found |= (val == dat);
            }
        );
        return found;
    }

    template<typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data> :: Fold(FoldFun<Accumulator> func, Accumulator acc) const
    {
        Traverse
        (
            [func, &acc](const Data& dat)
            {
                acc = func(dat, acc);
            }
        );
        return acc;
    }


//PreOrderTraversableContainer
    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data> :: PreOrderFold (FoldFun<Accumulator> func, Accumulator acc) const
    {
        PreOrderTraverse
        (
            [func, &acc](const Data& dat)
            {
                acc = func(dat, acc);
            }
        );
        return acc;
    }

    template<typename Data>
    inline void PreOrderTraversableContainer<Data> :: Traverse(TraverseFun func) const
    {
        PreOrderTraverse(func);
    }

//PostOrderTraversableContainer
    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data> :: PostOrderFold(FoldFun<Accumulator> func, Accumulator acc) const
    {
        PostOrderTraverse
        (
            [func, &acc](const Data& dat)
            {
                acc = func(dat, acc);
            }
        );
        return acc;
    }
    
    template<typename Data>
    inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun func) const 
    {
        PostOrderTraverse(func);
    }
    
/* ************************************************************************** */
}
