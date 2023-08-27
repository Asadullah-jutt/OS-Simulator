//
//  Minheap.h
//  OS Project
//
//  Created by MAC on 24/04/2023.
//

#ifndef Minheap_h
#define Minheap_h
#include <iostream>
using namespace std ;

// A class for Min Heap
template <typename T>
class MinHeap{
    int* heap ;
    T* harr;
    int capacity;
    int heap_size;
    
    int parent(int i)
    {
        return (i-1)/2;
    }
    int left(int i)
    {
        return (2*i + 1);
    }
    int right(int i)
    {
        return (2*i + 2);
    }
    void swap(T &a , T &b)
    {
        T temp = a ;
        a = b ;
        b = temp ;
    }
    void swap(int &a , int &b)
    {
        int temp = a ;
        a = b ;
        b = temp ;
    }
    

    void MinHeapify(int i)
    {
        int l = left(i) , r = right(i) , smallest = i;
        if (l < heap_size && heap[l] < heap[i])
            smallest = l;
        if (r < heap_size && heap[r] < heap[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            swap(harr[i], harr[smallest]);
            MinHeapify(smallest);
        }
    }
      

    void heapup(int i)
    {
          while (i != 0 && heap[parent(i)] > heap[i])
          {
             swap(heap[i], heap[parent(i)]);
             swap(harr[i], harr[parent(i)]);
             i = parent(i);
          }
      }
    

public:
  MinHeap(int cap)
  {
      heap_size = 0;
      capacity = cap;
      heap = new int[cap] ;
      harr = new T[cap];
  }
    
  void insertKey(int key , T k)
  {
      if(capacity > heap_size)
      {
          heap[heap_size] = key;
          harr[heap_size++] = k;
          heapup(heap_size-1);
      }
      else
          cout<<"Heap is Full"<<endl;
    
  }
  bool isEmpty()
  {
       if(heap_size == 0)
           return true ;
      return false ;
  }
    int size()
    {
        return heap_size;
    }
  void decreaseKey(int i, int new_val)
  {
      harr[i].pirority = new_val;
      heapup(i);
  }
    int getmin()
    {
        return heap[0] ;
    }
    int getMinA()
    {
        if(heap_size > 0)
            return harr[0].arival_time;
        else
            return -1 ;
    }
    int getpid()
    {
        return harr[0].pid ;
    }
    int getB()
    {
        return harr[0].brust_time ;
    }
    
    T extractMin()
  {
      if(heap_size == 0)
      {
          T p ;
          return p ;
      }
          
      if (heap_size == 1)
      {
          heap_size--;
          return harr[0];
      }
      T temp = harr[0];
      heap[0] = heap[heap_size-1];
      harr[0] = harr[heap_size-1];
      heap_size--;
      MinHeapify(0);
    
      return temp;
    }
    ~MinHeap()
    {
        if(harr != nullptr)
        {
            delete [] harr ;
            delete [] heap ;
        }
        
    }
    
  
};




#endif /* Minheap_h */
