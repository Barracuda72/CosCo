#ifndef __InputFilter_H__
#define __InputFilter_H__

#include "Reference.h"
#include "Integer.h"
#include "String.h"

struct InputFilter : Reference
{
  void CloseFilter();
  void DeleteInputFilter();
  void FlushInputQueue(Integer nLimit);
  Integer FlushJoyButtonPushed(Integer iDevNum = 0, Integer iKeyNum = -1);
  Integer GetJoyButtonPushed(Integer iKeyNum, Integer iDevNum = 0);
  Integer IsJoyButtonPushing(Integer iKeyNum, Integer iDevNum = 0);
  Integer LoadInputFilter(String filename);
  void OpenFilter(Integer nFilterType = 0);
  void OpenFilter(Integer nFilterType /*= 0 by def*/, Reference refWindow);
};

#endif // __InputFilter_H__

