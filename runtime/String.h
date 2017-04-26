#ifndef __String_H__
#define __String_H__

#include "Reference.h"
#include "Integer.h"

struct String : Reference
{
  void Call(); /* Call string as scenario */
  Integer Char(Integer i /* = 0 by default */);
  Integer Find(String s, Integer i /* = 0 by default*/);
  Integer GetLength();
  String Left(Integer i);
  void MakeUpper();
  String Middle(Integer i, Integer c /* = -1 by default */);
  String Replace(String strOld, String strNew, Integer nFlag /* = 0 by default*/);
};

#endif // __String_H__

