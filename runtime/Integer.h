#ifndef __Integer_H__
#define __Integer_H__

#include "Reference.h"

struct Integer : Reference
{
  Integer();
  Integer(int i);

  friend int operator==(const Integer& one, const Integer& other);
  friend int operator!=(const Integer& one, const Integer& other);
  friend int operator<(const Integer& one, const Integer& other);
  friend int operator>(const Integer& one, const Integer& other);
  friend int operator<=(const Integer& one, const Integer& other);
  friend int operator>=(const Integer& one, const Integer& other);
  friend int operator+(const Integer& one, const Integer& other);
  friend int operator-(const Integer& one, const Integer& other);
  friend int operator*(const Integer& one, const Integer& other);
  friend int operator/(const Integer& one, const Integer& other);
  friend int operator%(const Integer& one, const Integer& other);
  friend int operator&(const Integer& one, const Integer& other);
  friend int operator|(const Integer& one, const Integer& other);

  Integer SetBit(Integer a);
  Integer ShiftLeft(Integer a);
  Integer TestBit(Integer a);
};

#endif // __Integer_H__

