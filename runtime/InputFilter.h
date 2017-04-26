#ifndef __InputFilter_H__
#define __InputFilter_H__

#include "Reference.h"

struct InputFilter : Reference
{
  Reference CloseFilter(); /* Unknown return */
  Reference DeleteInputFilter(); /* Unknown return */
  Reference FlushInputQueue(Integer a); /* Unknown return */
  Reference FlushJoyButtonPushed(); /* Unknown return */
  Integer GetJoyButtonPushed(Integer a);
  Integer IsJoyButtonPushing(Integer a);
  Reference LoadInputFilter(String a); /* Unknown return */
  Reference OpenFilter(Integer a); /* Unknown return */
};

#endif // __InputFilter_H__

