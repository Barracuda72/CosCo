#ifndef __Array_H__
#define __Array_H__

#include "Reference.h"
#include "Integer.h"
#include "String.h"

struct Array : Reference
{
  Reference operator[](const Reference& idx);
  Reference operator[](int idx);
  void operator+(const String& s);
  void operator+(const Integer& i);

  Integer GetLength();
  void RemoveAll();
  void Remove();
  void Remove(Integer a, Integer b);
  void Swap(Integer a, Integer b);
  Integer IsEmpty();
};

#endif // __Array_H__

