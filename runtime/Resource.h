#ifndef __Resource_H__
#define __Resource_H__

#include <string>

class Bezier2D;

struct Resource
{
  //Resource res; /* Maybe should emulate this smthing? */

  void* GetInfo(); /* doublely ImageInfo/SoundInfo */
  int IsPlaying();
  int IsPendingEnvelope();
  int LoadImage(std::string filename);
  int LoadSound(std::string filename);
  int LoadSound(std::string filename, int nThreshold = -1);
  int Play(int nIntroSample = -1, int flag = 0 /*=ptfMusic by def*/); 
  void Release();
  void Pause();
  void Restart();
  void SetTotalVolume(int flag, double rTotalVol);
  void SetVolumeEnvelope(Bezier2D& bezier, int nDurationTime);
  void GetVolume(double& left, double& right);
  void SetVolume(const double& left, const double& right);
  void Stop();
};

#endif // __Resource_H__

