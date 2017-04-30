#ifndef __String_H__
#define __String_H__

#include "Reference.h"
#include "Integer.h"

template <class T> struct Array;

struct String : Object
{
  String();
  String(const char *s);

  friend int operator==(const String& one, const String& other);
  friend int operator==(const String& one, const char *other);
  friend int operator==(const char* one, const String& other);
  friend int operator!=(const String& one, const String& other);
  friend int operator!=(const String& one, const char *other);
  friend int operator!=(const char* one, const String& other);
  friend String operator+(const String& one, const String& other);
  friend String operator+(const String& one, const char *other);
  friend String operator+(const char* one, const String& other);

  String operator=(Integer& i);

  Integer Call(); /* Call string as scenario */
  Integer Char(Integer i = 0);
  Integer Find(String s, Integer i = 0);
  Integer GetLength();
  String Left(Integer i);
  void MakeUpper();
  String Middle(Integer i, Integer c = -1 );
  String Replace(String strOld, String strNew, Integer nFlag = 0);
  void TrimLeft();
  void TrimRight();
  String IsMatchUsage(String strUsage, Array <String> aParam /*Integer nIndex*/);
};

#endif // __String_H__

