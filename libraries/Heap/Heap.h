#ifndef __HEAP_H
#define __HEAP_H


#define STD_BUFFER 10

template<class T>
struct Greater{
  bool operator()(const T& lhs, const T& rhs)
  {
    return lhs > rhs;
  }
};

template<class T, class Compare = Greater<T> >
class Heap {
  typedef T* iterator;
  private:
  T* elem; // a pointer to the first object
  int space; //the index of the first free object
  int last;  // the index of one passed the last object
  
  int capacity();
  void reallocate();
  inline int freeSpace();
  void swap(int, int);

  bool bubbleDown(int&k);
  bool bubbleUp(int&k);
  Compare comp;

  public:
  Heap();
  ~Heap();

  T& top();
  T pop();
  void insert(T);
  void print();
  int size();

};

template<class T, class Compare>
Heap<T, Compare>::Heap()
{
  elem = new T[STD_BUFFER];
  space = 0;
  last = STD_BUFFER;
}

template<class T, class Compare>
Heap<T, Compare>::~Heap()
{
  delete[] elem;
}

template<class T, class Compare>
inline int Heap<T, Compare>::freeSpace()
{
  return last - space;
}

template<class T, class Compare>
void Heap<T, Compare>::reallocate()
{
  int s = size();
  int newSize = s*2;
  T* newElem = new T[newSize];
  for(int i = 0; i != s; i++)
  {
    newElem[i] = elem[i];
  }
  delete[] elem;
  elem = newElem;
  space = s;
  last = newSize; 
}


template<class T, class Compare>
void Heap<T, Compare>::swap(int i, int j)
{
  T temp = elem[i];
  elem[i] = elem[j];
  elem[j] = temp;
}

template<class T, class Compare>
bool Heap<T, Compare>::bubbleDown(int& k)
{
  int lc = k*2 +1, rc = lc +1;
  // it is possible that some of the childs are outside of the allocated space
  
  bool lb, rb;
  lb = lc < last;
  rb = rc < last;

  if(lb && rb)
  {
    if(comp(elem[k], elem[lc]) && comp(elem[k], elem[rc]))
    {
      return true; // no need to bubble down
    }

    if(comp(elem[lc], elem[rc])) // left child is greater 
    {
      swap(k, lc);
      k = lc;
      return false;
    } else { // right child is greater
      swap(k, rc);
      k = rc;
      return false;
    }
  }
  else if(lb) {
    if(comp(elem[lc], elem[k])) // left child is greater 
    {
      swap(k, lc);
      k = lc;
      return false;
    }
    else {
      return true;
    }
  }
  else {
    return true;
  }
}

template<class T, class Compare>
bool Heap<T, Compare>::bubbleUp(int& k)
{
  int ik = (k-1)/2; // parent index
  if(k == 0 || comp(elem[ik], elem[k]))
  {
    return true;
  }
  else { // parent is smaller 
   swap(k, ik);
   k = ik;
   return false;
  }
}


template<class T, class Compare>
T Heap<T, Compare>::pop()
{
  T temp = *elem;

  if (space == 0) return temp; // so that if you pop an empty heap the program does not crash. (but there is undefined behaviour)
  --space;
  elem[0] = elem[space];
  int k = 0;
  bool bubStop = false;
  while( bubStop == false)
  {
    bubStop = bubbleDown(k);
  }

  return temp;
}

template<class T, class Compare>
void Heap<T, Compare>::insert(T key)
{
  if( freeSpace() == 0) reallocate();

  elem[space] = key;
  int k = space;

  space ++;
  bool bubStop = false;
  while( bubStop == false)
  {
    bubStop = bubbleUp(k);
  }
}

template<class T, class Compare>
T& Heap<T, Compare>::top()
{
  return *elem;
}

template<class T, class Compare>
int Heap<T, Compare>::size()
{
  return space; 
}

/*
template<class Compare>
void Heap<ProcessHandle, Compare>::print()
{
  Serial.print("(");
  for(int i = 0; i!= space; i++)
  {
    Serial.print(elem[i]->pid);
    Serial.print(" ");
    //Serial.print(space);
  }
  Serial.print(")");
}
*/


#endif
