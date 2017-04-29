#include "Cotopha.h"
#include "Runtime.h"

/*
 * Standalone functions (bodies)
 */

Real fabs(Real x)
{
  return x.Abs();
}

Real log(Real x)
{
  return x.Log();
}

Real log10(Real x)
{
  return x.Log(10.000000);
}

Real pow(Real x, Real y)
{
  return x.Power(y);
}

Real sqrt(Real x)
{
  return x.Sqrt();
}

Real sin(Real x)
{
  return x.Sin();
}

Real cos(Real x)
{
  return x.Cos();
}

Real tan(Real x)
{
  return x.Tan();
}

Real asin(Real x)
{
  return x.ASin();
}

Real acos(Real x)
{
  return x.ACos();
}

Real atan(Real x)
{
  return x.ATan();
}

Real atan2(Real x, Real y)
{
  return x.ATan(y);
}

Point IPoint(Integer x, Integer y)
{
    Point point;
  point.x = x;
  point.y = y;
  return point;
}

Size ISize(Integer w, Integer h)
{
    Size size;
  size.w = w;
  size.h = h;
  return size;
}

Rect IRect(Integer left, Integer top, Integer right, Integer bottom)
{
    Rect rect;
  rect.left = left;
  rect.top = top;
  rect.right = right;
  rect.bottom = bottom;
  return rect;
}

Vector2D IVector2D(Real x, Real y)
{
    Vector2D v;
  v.x = x;
  v.y = y;
  return v;
}

Vector IVector(Real x, Real y, Real z)
{
    Vector v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

void op_init()
{
}


/*
 * Class implementations
 */

Point::Point()
{
}

Size::Size()
{
}

Rect::Rect()
{
}

SpriteParam::SpriteParam()
{
  rHorzUnit = 1.000000;
  rVertUnit = 1.000000;
  rCrossingAngle = 90.000000;
  rgbLightColor = 16777215;
}

ImageInfo::ImageInfo()
{
}

SoundInfo::SoundInfo()
{
}

WndSpriteCmd::WndSpriteCmd()
{
}

Vector2D::Vector2D()
{
}
/*
String Vector2D::op_dispatcher(Integer nType, Reference v)
{
  if ((nType == csotAdd))
  {
    this->x = (this->x + v.x);
    this->y = (this->y + v.y);
  }
  else {
    if ((nType == csotSub))
    {
      this->x = (this->x - v.x);
      this->y = (this->y - v.y);
    }
    else {
      if ((nType == csotMul))
      {
        this->x = (this->x * v);
        this->y = (this->y * v);
      }
      else {
        if ((nType == csotDiv))
        {
          this->x = (this->x / v);
          this->y = (this->y / v);
        }
        else {
            return "Vector2D Œ^‚Ì’è‹`‚³‚ê‚Ä‚¢‚È‚¢‰‰Zq‚Å‚·B";
        }
      }
    }
  }
}
*/

Vector2D Vector2D::Revolve(Real r)
{
    Vector2D v;
    Real rad;
  rad = ((r * 3.141593) / 180);
  v.x = ((this->x * rad.Cos()) - (this->y * rad.Sin()));
  v.y = ((this->x * rad.Sin()) + (this->y * rad.Cos()));
  return v;
}

Real Vector2D::Abs()
{
  return ((this->x * this->x) + (this->y * this->y)).Sqrt();
}

Vector2D Vector2D::RoundTo1()
{
    Real r;
  r = Abs();
  this->x = (this->x / r);
  this->y = (this->y / r);
  return this;
}

Vector::Vector()
{
}
/*
String Vector::op_dispatcher(Integer nType, Reference v)
{
  if ((nType == csotAdd))
  {
    this->x = (this->x + v.x);
    this->y = (this->y + v.y);
    this->z = (this->z + v.z);
  }
  else {
    if ((nType == csotSub))
    {
      this->x = (this->x - v.x);
      this->y = (this->y - v.y);
      this->z = (this->z - v.z);
    }
    else {
      if ((nType == csotMul))
      {
        this->x = (this->x * v);
        this->y = (this->y * v);
        this->z = (this->z * v);
      }
      else {
        if ((nType == csotDiv))
        {
          this->x = (this->x / v);
          this->y = (this->y / v);
          this->z = (this->z / v);
        }
        else {
            return "Vector Œ^‚Ì’è‹`‚³‚ê‚Ä‚¢‚È‚¢‰‰Zq‚Å‚·B";
        }
      }
    }
  }
}
*/
Real Vector::Abs()
{
  return (((this->x * this->x) + (this->y * this->y)) + (this->z * this->z)).Sqrt();
}

Vector Vector::RoundTo1()
{
    Real r;
  r = Abs();
  this->x = (this->x / r);
  this->y = (this->y / r);
  this->z = (this->z / r);
  return this;
}

InputEvent::InputEvent()
{
}

Bezier1D::Bezier1D()
{
  parent[0] = Real;
  parent[1] = Real;
  parent[2] = Real;
  parent[3] = Real;
}

void Bezier1D::SetLinear(Real r0, Real r1)
{
    Real rDelta;
  rDelta = ((r1 - r0) / 3.000000);
  parent[0] = r0;
  parent[1] = (r0 + rDelta);
  parent[2] = (r1 - rDelta);
  parent[3] = r1;
}

void Bezier1D::SetAcceleration(Real a0, Real a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

Real Bezier1D::pt(Real t)
{
    Array f;
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Real r;
    r = 0.000000;
    Integer i;
    i = 0;
  do {
      Real b;
    b = ((f[i] * t.Power(i)) * Real((1.000000 - t)).Power((3 - i)));
    r = (r + (parent[i] * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return r;
}

Bezier2D::Bezier2D()
{
  parent[0] = Vector2D;
  parent[1] = Vector2D;
  parent[2] = Vector2D;
  parent[3] = Vector2D;
}

void Bezier2D::SetLinear(Real x0, Real y0, Real x1, Real y1)
{
    Vector2D vDelta;
  vDelta.x = ((x1 - x0) / 3.000000);
  vDelta.y = ((y1 - y0) / 3.000000);
  parent[0].x = x0;
  parent[0].y = y0;
  parent[1].x = (x0 + vDelta.x);
  parent[1].y = (y0 + vDelta.y);
  parent[2].x = (x1 - vDelta.x);
  parent[2].y = (y1 - vDelta.y);
  parent[3].x = x1;
  parent[3].y = y1;
}

void Bezier2D::SetAcceleration(Real a0, Real a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

void Bezier2D::SetCurve(Real r0, Real r1)
{
  parent[1] = ((parent[1] - parent[0]).Revolve(r0) + parent[0]);
  parent[2] = ((parent[2] - parent[3]).Revolve(r1) + parent[3]);
}

Vector2D Bezier2D::pt(Real t)
{
    Array f;
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Vector2D v;
    Integer i;
    i = 0;
  do {
      Real b;
    b = ((f[i] * t.Power(i)) * Real((1.000000 - t)).Power((3 - i)));
    v.x = (v.x + (parent[i].x * b));
    v.y = (v.y + (parent[i].y * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return v;
}

Bezier3D::Bezier3D()
{
  parent[0] = Vector;
  parent[1] = Vector;
  parent[2] = Vector;
  parent[3] = Vector;
}

void Bezier3D::SetLinear(Real x0, Real y0, Real z0, Real x1, Real y1, Real z1)
{
    Vector vDelta;
  vDelta.x = ((x1 - x0) / 3.000000);
  vDelta.y = ((y1 - y0) / 3.000000);
  vDelta.z = ((z1 - z0) / 3.000000);
  parent[0].x = x0;
  parent[0].y = y0;
  parent[0].z = z0;
  parent[1].x = (x0 + vDelta.x);
  parent[1].y = (y0 + vDelta.y);
  parent[1].z = (z0 + vDelta.z);
  parent[2].x = (x1 - vDelta.x);
  parent[2].y = (y1 - vDelta.y);
  parent[2].z = (z1 - vDelta.z);
  parent[3].x = x1;
  parent[3].y = y1;
  parent[3].z = z1;
}

void Bezier3D::SetAcceleration(Real a0, Real a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

Vector Bezier3D::pt(Real t)
{
    Array f;
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Vector v;
    Integer i;
    i = 0;
  do {
      Real b;
    b = ((f[i] * t.Power(i)) * Real((1.000000 - t)).Power((3 - i)));
    v.x = (v.x + (parent[i].x * b));
    v.y = (v.y + (parent[i].y * b));
    v.z = (v.z + (parent[i].z * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return v;
}

SurfaceAttribute::SurfaceAttribute()
{
  rgbColorMul = 16777215;
}

E3DColor::E3DColor()
{
  rgbMul = 16777215;
}

LightEntry::LightEntry()
{
}

Time::Time()
{
}

MemoryStatus::MemoryStatus()
{
}

EffectParam::EffectParam()
{
}

ParticleFlick::ParticleFlick()
{
}

ParticleParam::ParticleParam()
{
  nAnimationSpeed = 256;
  rFadeZoom = 1.000000;
  rZoom = 1.000000;
  this->pfFlickness[0] = ParticleFlick;
  this->pfFlickness[1] = ParticleFlick;
}

ParticleParam3D::ParticleParam3D()
{
  nAnimationSpeed = 256;
  rFadeZoom = 1.000000;
  rZoom = 1.000000;
  this->pfFlickness[0] = ParticleFlick;
  this->pfFlickness[1] = ParticleFlick;
}

void BezierR64::SetLinear(Real r0, Real r1)
{
    Real rDelta;
  rDelta = ((r1 - r0) / 3.000000);
  this->cp[0] = r0;
  this->cp[1] = (r0 + rDelta);
  this->cp[2] = (r1 - rDelta);
  this->cp[3] = r1;
}

void BezierR64::SetAcceleration(Real a0, Real a1)
{
  this->cp[1] = (((this->cp[1] - this->cp[0]) * a0) + this->cp[0]);
  this->cp[2] = (((this->cp[2] - this->cp[3]) * a1) + this->cp[3]);
}

Real BezierR64::pt(Real t)
{
    Array f;
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Real r;
    r = 0.000000;
    Integer i;
    i = 0;
  do {
      Real b;
    b = ((f[i] * t.Power(i)) * Real((1.000000 - t)).Power((3 - i)));
    r = (r + (this->cp[i] * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return r;
}

