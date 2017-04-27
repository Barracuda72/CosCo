#ifndef __String_H__
#define __String_H__

#include "Reference.h"
#include "Integer.h"

struct String : Reference
{
  String();
  String(const char *s);

  friend int operator==(String& one, String& other);
  friend int operator==(String& one, const char *other);
  friend int operator==(const char* one, String& other);
  friend int operator!=(String& one, String& other);
  friend int operator!=(String& one, const char *other);
  friend int operator!=(const char* one, String& other);
  friend String operator+(String& one, String& other);
  friend String operator+(String& one, const char *other);
  friend String operator+(const char* one, String& other);

  String operator=(Integer& i);

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

