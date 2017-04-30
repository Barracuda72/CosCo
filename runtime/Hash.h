#ifndef __Hash_H__
#define __Hash_H__

#include "Array.h"
#include "Integer.h"
#include "String.h"

template <class T>
class Hash : Array<T>
{
public:
  String GetTagName(Integer a);
};

#endif // __Hash_H__

