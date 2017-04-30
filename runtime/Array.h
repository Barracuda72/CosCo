#ifndef __Array_H__
#define __Array_H__

#include "Object.h"
#include "Reference.h"
#include "Integer.h"

template <class T>
class Array : Object
{
public:
  T operator[](const Object& idx);
  T operator[](int idx);
  T operator[](const char* idx);
  void operator+(const Object& s);

  Integer GetLength();
  void RemoveAll();
  void Remove();
  void Remove(Integer a, Integer b);
  void Swap(Integer a, Integer b);
  Integer IsEmpty();
};

#endif // __Array_H__

