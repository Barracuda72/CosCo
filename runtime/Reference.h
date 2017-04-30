#ifndef __Reference_H__
#define __Reference_H__

#include "Object.h"
#include "Real.h"
#include "Integer.h"
#include "String.h"

class Reference 
{
private:
  Object object;

public:
  Reference();
  Reference(Object o);

  String GetType();

  Reference & operator=(const Real &rhs);
  Reference & operator=(const String &rhs);
  Reference & operator=(const Object &rhs);
  //Reference & operator=(const Integer &rhs);
  
  /* Real operations */
  friend Real & operator+(const Reference& one, const Real& other);
  friend Real & operator+(const Real& one, const Reference& other);
  friend Real & operator-(const Reference& one, const Real& other);
  friend Real & operator-(const Reference& one, const Reference& other);
  friend Real & operator*(const Reference& one, const Real& other);

  /* String operations */
  friend String & operator+(const Reference& one, const String& other);
};

#endif // __Reference_H__

