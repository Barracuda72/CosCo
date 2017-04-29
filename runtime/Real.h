#ifndef __Real_H__
#define __Real_H__

#include "Reference.h"

struct Real : Reference
{

  Real();
  Real(double d);
  Real(Integer i);

  friend Real operator+(const Real& one, const Real& other);
  friend Real operator-(const Real& one, const Real& other);
  friend Real operator*(const Real& one, const Real& other);
  friend Real operator/(const Real& one, const Real& other);

  Real ACos();
  Real ASin();
  Real ATan();
  Real ATan(Real a); /* Also atan2 */
  Real Abs();
  Real Cos();
  Real Log();
  Real Log(Real a);
  Real Power(Real a);
  Real Sin();
  Real Sqrt();
  Real Tan();
};

#endif // __Real_H__

