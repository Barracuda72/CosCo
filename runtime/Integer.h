#ifndef __Integer_H__
#define __Integer_H__

#include "Object.h"

class Integer : public Object
{
private:
  int value;

public:
  Integer();
  Integer(int i);
  Integer(const char* s); /* Really dummy */

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
  Integer ShiftRight(Integer a);
  Integer TestBit(Integer a);
};

#endif // __Integer_H__

