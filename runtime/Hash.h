#ifndef __Hash_H__
#define __Hash_H__

#include "Array.h"
#include "Integer.h"
#include "String.h"

struct Hash : Array
{
  String GetTagName(Integer a);
};

#endif // __Hash_H__

