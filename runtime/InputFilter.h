#ifndef __InputFilter_H__
#define __InputFilter_H__

#include <string>

struct InputFilter
{
  void CloseFilter();
  void DeleteInputFilter();
  void FlushInputQueue(int nLimit);
  int FlushJoyButtonPushed(int iDevNum = 0, int iKeyNum = -1);
  int GetJoyButtonPushed(int iKeyNum, int iDevNum = 0);
  int IsJoyButtonPushing(int iKeyNum, int iDevNum = 0);
  int LoadInputFilter(std::string filename);
  void OpenFilter(int nFilterType = 0);
  void OpenFilter(int nFilterType /*= 0 by def*/, void* refWindow);
};

#endif // __InputFilter_H__

