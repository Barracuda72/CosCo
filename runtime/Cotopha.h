#ifndef __COTOPHA_H__
#define __COTOPHA_H__

//#include "yosuga.h"
#include <string>
#include <cmath>

/*
 * Constants
 */

#define eslErrSuccess 0
#define eslErrNotSupported -1
#define eslErrGeneral 1
#define eslErrAbort 2
#define eslErrInvalidParam 3
#define eslErrTimeout 4
#define eslErrPending 5
#define eslErrContinue 6
#define EGL_DRAW_BLEND_ALPHA 1
#define EGL_DRAW_GLOW_LIGHT 2
#define EGL_WITH_Z_ORDER 4
#define EGL_SMOOTH_STRETCH 16
#define EGL_UNSMOOTH_STRETCH 32
#define EGL_FIXED_POSITION 64
#define EGL_APPLY_C_ADD 8388608
#define EGL_APPLY_C_MUL 8519680
#define EGL_APPLY_A_MUL 8912896
#define EGL_APPLY_C_MASK 8978432
#define EGL_DRAW_F_ADD -2147483648
#define EGL_DRAW_F_SUB -2130706432
#define EGL_DRAW_F_MUL -2113929216
#define EGL_DRAW_F_DIV -2097152000
#define EGL_DRAW_F_MAX -2080374784
#define EGL_DRAW_F_MIN -2063597568
#define EGL_DRAW_A_MOVE -2013265920
#define EGL_DRAW_A_MUL -1996488704
#define EIF_RGB_BITMAP 1
#define EIF_RGBA_BITMAP 67108865
#define EIF_GRAY_BITMAP 2
#define EIF_YUV_BITMAP 4
#define EIF_HSB_BITMAP 6
#define EIF_Z_BUFFER_R4 8197
#define EIF_TYPE_MASK 16777215
#define EIF_WITH_PALETTE 16777216
#define EIF_WITH_CLIPPING 33554432
#define EIF_WITH_ALPHA 67108864
#define effTransition 1
#define pfAnimationLoop 1
#define E3DSAF_NO_SHADING 0
#define E3DSAF_FLAT_SHADE 1
#define E3DSAF_GOURAUD_SHADE 2
#define E3DSAF_PHONG_SHADE 3
#define E3DSAF_SHADING_MASK 255
#define E3DSAF_TEXTURE_TILING 256
#define E3DSAF_TEXTURE_TRIM 512
#define E3DSAF_TEXTURE_SMOOTH 1024
#define E3DSAF_TEXTURE_MAPPING 4096
#define E3DSAF_ENVIRONMENT_MAP 8192
#define E3DSAF_GENVIRONMENT_MAP 16384
#define E3DSAF_SINGLE_SIDE_PLANE 65536
#define E3DSAF_NO_ZBUFFER 131072
#define E3DSAF_ZBUF_ONLY_COMPARE 262144
#define E3D_FOG_LIGHT 0
#define E3D_AMBIENT_LIGHT 1
#define E3D_VECTOR_LIGHT 2
#define E3D_POINT_LIGHT 4
#define E3D_FLAG_ANTIALIAS_SIDE_EDGE 1
#define E3D_FLAG_TEXTURE_SMOOTHING 2
#define E3D_SORT_TRANSPARENT 1
#define E3D_SORT_OPAQUE 2
#define idKeyboard 0
#define idMouse 1
#define idJoyStick 2
#define idCommand 3
#define VK_LBUTTON 1
#define VK_RBUTTON 2
#define VK_CANCEL 3
#define VK_MBUTTON 4
#define VK_BACK 8
#define VK_TAB 9
#define VK_CLEAR 12
#define VK_RETURN 13
#define VK_SHIFT 16
#define VK_CONTROL 17
#define VK_MENU 18
#define VK_PAUSE 19
#define VK_CAPITAL 20
#define VK_KANA 21
#define VK_HANGEUL 21
#define VK_HANGUL 21
#define VK_JUNJA 23
#define VK_FINAL 24
#define VK_HANJA 25
#define VK_KANJI 25
#define VK_ESCAPE 27
#define VK_CONVERT 28
#define VK_NONCONVERT 29
#define VK_ACCEPT 30
#define VK_MODECHANGE 31
#define VK_SPACE 32
#define VK_PRIOR 33
#define VK_NEXT 34
#define VK_END 35
#define VK_HOME 36
#define VK_LEFT 37
#define VK_UP 38
#define VK_RIGHT 39
#define VK_DOWN 40
#define VK_SELECT 41
#define VK_PRINT 42
#define VK_EXECUTE 43
#define VK_SNAPSHOT 44
#define VK_INSERT 45
#define VK_DELETE 46
#define VK_HELP 47
#define VK_LWIN 91
#define VK_RWIN 92
#define VK_APPS 93
#define VK_SLEEP 95
#define VK_NUMPAD0 96
#define VK_NUMPAD1 97
#define VK_NUMPAD2 98
#define VK_NUMPAD3 99
#define VK_NUMPAD4 100
#define VK_NUMPAD5 101
#define VK_NUMPAD6 102
#define VK_NUMPAD7 103
#define VK_NUMPAD8 104
#define VK_NUMPAD9 105
#define VK_MULTIPLY 106
#define VK_ADD 107
#define VK_SEPARATOR 108
#define VK_SUBTRACT 109
#define VK_DECIMAL 110
#define VK_DIVIDE 111
#define VK_F1 112
#define VK_F2 113
#define VK_F3 114
#define VK_F4 115
#define VK_F5 116
#define VK_F6 117
#define VK_F7 118
#define VK_F8 119
#define VK_F9 120
#define VK_F10 121
#define VK_F11 122
#define VK_F12 123
#define VK_F13 124
#define VK_F14 125
#define VK_F15 126
#define VK_F16 127
#define VK_F17 128
#define VK_F18 129
#define VK_F19 130
#define VK_F20 131
#define VK_F21 132
#define VK_F22 133
#define VK_F23 134
#define VK_F24 135
#define ckmShift 4096
#define ckmControl 8192
#define ckmMenu 16384
#define ckmCaptal 32768
#define ckmKeyCodeMask 255
#define jbUp 0
#define jbDown 1
#define jbLeft 2
#define jbRight 3
#define jbButton1 4
#define jbButton2 5
#define jbButton3 6
#define jbButton4 7
#define jbButtonMax (jbButton1 + 32)
#define EGL_TONE_BRIGHTNESS 0
#define EGL_TONE_INVERSION 1
#define EGL_TONE_LIGHT 2
#define tffFixZero 1
#define tffMaskWithAlpha 2
#define tffYUVFilter 4
#define INFINITE -1
#define csotAdd 0
#define csotSub 1
#define csotMul 2
#define csotDiv 3
#define csotMod 4
#define csotAnd 5
#define csotOr 6
#define csotXor 7
#define csotLogicalAnd 8
#define csoutLogicalOr 9
#define csuotPlus 0
#define csuotNegate 1
#define csuotBitNot 2
#define csuotLogicalNot 3
#define csctNotEqual 0
#define csctEqual 1
#define csctLessThan 2
#define csctLessEqual 3
#define csctGreaterThan 4
#define csctGreaterEqual 5
#define FromBegin 0
#define FromCurrent 1
#define FromEnd 2
#define modeCreateFlag 1
#define modeCreate 5
#define modeRead 2
#define modeWrite 4
#define modeReadWrite 6
#define shareRead 16
#define shareWrite 32
#define ptfMusic 0
#define ptfSE 1
#define ptfVoice 2
#define ptfSystem 3
#define ptfDevice -2147483648
#define animeNormal 1
#define animeAction 2
#define animeEffect 4
#define mpfDirectDraw 1
#define mpfLoopPlay 2
#define mpfNoLoopFilter 1024
#define mpfUseLoopFilter 2048
#define gfNegativeMask 1
#define gfGenerationPoints 2
#define gfRaySide 4
#define ctOnlyAngle 1
#define bsNormal 0
#define bsFocus 1
#define bsPushed 2
#define bsPushedFocus 3
#define bsDisabled 4
#define bsPushDisabled 5
#define bsActivePushed 6
#define ncGeneric 0
#define ncLineUp 1
#define ncLineDown 2
#define ncClickColumn 3
#define ncTracking 4
#define ncEndTracking 5
#define ncChange 0
#define ncKillFocus 1
#define levelWindow 0
#define levelNormal 1
#define levelFullScreen 3
#define levelExclusive 7
#define optfUseDblClick 1
#define optfAllowClose 2
#define optfBlackBack 4
#define optfEnableIME 8
#define optfAllowMinimize 16
#define optfGrantScreenSave 32
#define optfGrantMonitorSave 64
#define optfGrantPowerSuspend 128
#define optfOpenIME 65536
#define sysProcessorType 0
#define sysFontSmoothing 1
#define GLS_USE_MMX_PENTIUM 2
#define GLS_USE_XMM_SSE 8
#define GLS_USE_XMM_SSE2 16

/*
 * Class declarations (headers)
 */

struct Point;
struct Size;
struct Rect;
struct SpriteParam;
struct ImageInfo;
struct SoundInfo;
struct WndSpriteCmd;
struct Vector2D;
struct Vector;
struct InputEvent;
struct Bezier1D;
struct Bezier2D;
struct Bezier3D;
struct SurfaceAttribute;
struct E3DColor;
struct LightEntry;
struct Time;
struct MemoryStatus;
struct EffectParam;
struct ParticleFlick;
struct ParticleParam;
struct ParticleParam3D;
struct BezierR64;

/*
 * Class declarations (bodies)
 */

struct Point
{
  int x;
  int y;
  Point();
};

struct Size
{
  int w;
  int h;
  Size();
};

struct Rect
{
  int left;
  int top;
  int right;
  int bottom;
  Rect();
};

struct SpriteParam
{
  int nFlags;
  Point ptDstPos;
  Point ptRevCenter;
  double rHorzUnit;
  double rVertUnit;
  double rRevAngle;
  double rCrossingAngle;
  int rgbDimColor;
  int rgbLightColor;
  int nTransparency;
  double rZOrder;
  int rgbColorParam1;
  SpriteParam();
};

struct ImageInfo
{
  int nFormatType;
  int nImageWidth;
  int nImageHeight;
  int nBitsPerPixel;
  int nFrameCount;
  int xHotSpot;
  int yHotSpot;
  int nResourceBytes;
  ImageInfo();
};

struct SoundInfo
{
  int nSampleCount;
  int nSamplesPerSec;
  int nChannelCount;
  int nBitsPerSample;
  int nRewoundPosition;
  int nResourceBytes;
  SoundInfo();
};

struct WndSpriteCmd
{
  std::string strID;
  std::string strFullID;
  int nNotification;
  int nParameter;
  WndSpriteCmd();
};

struct Vector2D
{
  double x;
  double y;
  Vector2D();
  friend Vector2D operator+(const Vector2D& one, const Vector2D& other);
  friend Vector2D operator-(const Vector2D& one, const Vector2D& other);
  friend Vector2D operator*(const Vector2D& one, double other);
  friend Vector2D operator/(const Vector2D& one, double other);
  Vector2D Revolve(double r);
  double Abs();
  Vector2D RoundTo1();
};

struct Vector
{
  double x;
  double y;
  double z;
  Vector();
  friend Vector operator+(const Vector& one, const Vector& other);
  friend Vector operator-(const Vector& one, const Vector& other);
  friend Vector operator*(const Vector& one, double other);
  friend Vector operator/(const Vector& one, double other);
  double Abs();
  Vector RoundTo1();
};

struct InputEvent
{
  int idType;
  int iDevNum;
  int iKeyNum;
  std::string strCommand;
  InputEvent();
};

struct Bezier1D
{
  double parent[4];
  Bezier1D();
  void SetLinear(double r0, double r1);
  void SetAcceleration(double a0, double a1);
  double pt(double t);
};

struct Bezier2D
{
  Vector2D parent[4];
  Bezier2D();
  void SetLinear(double x0, double y0, double x1, double y1);
  void SetAcceleration(double a0, double a1);
  void SetCurve(double r0, double r1);
  Vector2D pt(double t);
};

struct Bezier3D
{
  Vector parent[4];
  Bezier3D();
  void SetLinear(double x0, double y0, double z0, double x1, double y1, double z1);
  void SetAcceleration(double a0, double a1);
  Vector pt(double t);
};

struct SurfaceAttribute
{
  int nShadingFlags;
  int rgbColorMul;
  int rgbColorAdd;
  int nAmbient;
  int nDiffusion;
  int nSpecular;
  int nTransparency;
  int nDeepness;
  SurfaceAttribute();
};

struct E3DColor
{
  int rgbMul;
  int rgbAdd;
  E3DColor();
};

struct LightEntry
{
  int nLightType;
  int rgbColor;
  double rBrightness;
  Vector vecLight;
  LightEntry();
};

struct Time
{
  int nYear;
  int nMonth;
  int nDay;
  int nWeek;
  int nHour;
  int nMinute;
  int nSecond;
  Time();
};

struct MemoryStatus
{
  int nTotalPhys;
  int nAvailPhys;
  int nTotalVirtual;
  int nAvailVirtual;
  MemoryStatus();
};

struct EffectParam
{
  std::string strType;
  int nFlags;
  int nInterval;
  int nDegreeStep;
  int nShakingWidth;
  int nMeshSize;
  int nMeshDivision;
  int nFrequency;
  Size sizeView;
  Point ptSpeed;
  int nAlphaRange;
  int nMilliSecPerDegree;
  Point ptSmashPoint;
  double rSmashDelay;
  double rSmashPower;
  double rRandomPower;
  double rDeceleration;
  Vector vVelocity;
  Vector vGravity;
  Vector vRevSpeed;
  Vector vRevRandom;
  EffectParam();
};

struct ParticleFlick
{
  double rAmplitude;
  double rAmplitudeRange;
  double rFrequency;
  double rFrequencyRange;
  ParticleFlick();
};

struct ParticleParam
{
  int nFlags;
  int nDuration;
  int nAnimationSpeed;
  int nFadein;
  int nFadeout;
  int nFadeTransparency;
  double rFadeZoom;
  double rGenWidth;
  double rGenHeight;
  double rGenAngle;
  double rGenAngleRange;
  double rGenVelocity;
  double rGenVelocityRange;
  double rShrink;
  double rRevSpeed;
  double rRevSpeedRange;
  double rZoom;
  double rZoomRange;
  ParticleFlick pfFlickness[2];
  Vector2D vGenSpeed;
  double rGenSpeedRange;
  Vector2D vStream;
  Vector2D vGravity;
  ParticleParam();
};

struct ParticleParam3D
{
  int nFlags;
  int nDuration;
  int nAnimationSpeed;
  int nFadein;
  int nFadeout;
  int nFadeTransparency;
  double rFadeZoom;
  Vector vGenWidth;
  Vector vGenAngle;
  double rGenAngleRange;
  double rGenVelocity;
  double rGenVelocityRange;
  double rShrink;
  Vector vRevBaseAxis;
  double rRevSpeed;
  double rRevSpeedRange;
  Vector vRevRevAxis;
  double rRevRevRange;
  double rZoom;
  double rZoomRange;
  ParticleFlick pfFlickness[2];
  Vector vGenSpeed;
  double rGenSpeedRange;
  Vector vStream;
  Vector vGravity;
  ParticleParam3D();
};

struct BezierR64
{
  double cp[4];
  void SetLinear(double r0, double r1);
  void SetAcceleration(double a0, double a1);
  double pt(double t);
};

/*
 * Standalone functions (headers)
 */

Point IPoint(int x, int y);
Size ISize(int w, int h);
Rect IRect(int left, int top, int right, int bottom);
Vector2D IVector2D(double x, double y);
Vector IVector(double x, double y, double z);

#endif // __COTOPHA_H__
