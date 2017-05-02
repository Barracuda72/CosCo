#include <string>
#include <cmath>

#include "Cotopha.h"

/*
 * Standalone functions (bodies)
 */

Point IPoint(int x, int y)
{
    Point point;
  point.x = x;
  point.y = y;
  return point;
}

Size ISize(int w, int h)
{
    Size size;
  size.w = w;
  size.h = h;
  return size;
}

Rect IRect(int left, int top, int right, int bottom)
{
    Rect rect;
  rect.left = left;
  rect.top = top;
  rect.right = right;
  rect.bottom = bottom;
  return rect;
}

Vector2D IVector2D(double x, double y)
{
    Vector2D v;
  v.x = x;
  v.y = y;
  return v;
}

Vector IVector(double x, double y, double z)
{
    Vector v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
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

Vector2D Vector2D::Revolve(double r)
{
    Vector2D v;
    double rad;
  rad = ((r * 3.141593) / 180);
  v.x = ((this->x * cos(rad)) - (this->y * sin(rad)));
  v.y = ((this->x * sin(rad)) + (this->y * cos(rad)));
  return v;
}

double Vector2D::Abs()
{
  return sqrt((this->x * this->x) + (this->y * this->y));
}

Vector2D Vector2D::RoundTo1()
{
    double r;
  r = Abs();
  this->x = (this->x / r);
  this->y = (this->y / r);
  return *this;
}

Vector::Vector()
{
}

double Vector::Abs()
{
  return sqrt(((this->x * this->x) + (this->y * this->y)) + (this->z * this->z));
}

Vector Vector::RoundTo1()
{
  double r;
  r = Abs();
  this->x = (this->x / r);
  this->y = (this->y / r);
  this->z = (this->z / r);
  return *this;
}

InputEvent::InputEvent()
{
}

Bezier1D::Bezier1D()
{
  parent[0] = 0.0;
  parent[1] = 0.0;
  parent[2] = 0.0;
  parent[3] = 0.0;
}

void Bezier1D::SetLinear(double r0, double r1)
{
    double rDelta;
  rDelta = ((r1 - r0) / 3.000000);
  parent[0] = r0;
  parent[1] = (r0 + rDelta);
  parent[2] = (r1 - rDelta);
  parent[3] = r1;
}

void Bezier1D::SetAcceleration(double a0, double a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

double Bezier1D::pt(double t)
{
  double f[4];
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    double r;
    r = 0.000000;
    int i;
    i = 0;
  do {
      double b;
    b = ((f[i] * pow(t, i)) * pow(1.000000 - t, 3 - i));
    r = (r + (parent[i] * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return r;
}

Bezier2D::Bezier2D()
{
  parent[0] = Vector2D();
  parent[1] = Vector2D();
  parent[2] = Vector2D();
  parent[3] = Vector2D();
}

void Bezier2D::SetLinear(double x0, double y0, double x1, double y1)
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

void Bezier2D::SetAcceleration(double a0, double a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

void Bezier2D::SetCurve(double r0, double r1)
{
  parent[1] = ((parent[1] - parent[0]).Revolve(r0) + parent[0]);
  parent[2] = ((parent[2] - parent[3]).Revolve(r1) + parent[3]);
}

Vector2D Bezier2D::pt(double t)
{
  double f[4];
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Vector2D v;
    int i;
    i = 0;
  do {
      double b;
    b = ((f[i] * pow(t, i)) * pow(1.000000 - t, 3 - i));
    v.x = (v.x + (parent[i].x * b));
    v.y = (v.y + (parent[i].y * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return v;
}

Bezier3D::Bezier3D()
{
  parent[0] = Vector();
  parent[1] = Vector();
  parent[2] = Vector();
  parent[3] = Vector();
}

void Bezier3D::SetLinear(double x0, double y0, double z0, double x1, double y1, double z1)
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

void Bezier3D::SetAcceleration(double a0, double a1)
{
  parent[1] = (((parent[1] - parent[0]) * a0) + parent[0]);
  parent[2] = (((parent[2] - parent[3]) * a1) + parent[3]);
}

Vector Bezier3D::pt(double t)
{
  double f[4];
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    Vector v;
    int i;
    i = 0;
  do {
      double b;
    b = ((f[i] * pow(t, i)) * pow(1.000000 - t, 3 - i));
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
  this->pfFlickness[0] = ParticleFlick();
  this->pfFlickness[1] = ParticleFlick();
}

ParticleParam3D::ParticleParam3D()
{
  nAnimationSpeed = 256;
  rFadeZoom = 1.000000;
  rZoom = 1.000000;
  this->pfFlickness[0] = ParticleFlick();
  this->pfFlickness[1] = ParticleFlick();
}

void BezierR64::SetLinear(double r0, double r1)
{
    double rDelta;
  rDelta = ((r1 - r0) / 3.000000);
  this->cp[0] = r0;
  this->cp[1] = (r0 + rDelta);
  this->cp[2] = (r1 - rDelta);
  this->cp[3] = r1;
}

void BezierR64::SetAcceleration(double a0, double a1)
{
  this->cp[1] = (((this->cp[1] - this->cp[0]) * a0) + this->cp[0]);
  this->cp[2] = (((this->cp[2] - this->cp[3]) * a1) + this->cp[3]);
}

double BezierR64::pt(double t)
{
  double f[4];
  f[0] = 1.000000;
  f[1] = 3.000000;
  f[2] = 3.000000;
  f[3] = 1.000000;
    double r;
    r = 0.000000;
    int i;
    i = 0;
  do {
      double b;
    b = ((f[i] * pow(t, i)) * pow((1.000000 - t), (3 - i)));
    r = (r + (this->cp[i] * b));
    i = (i + 1);
  } while (!((i >= 4)));
  return r;
}

/*
 * Extra: vector operators
 */
/* Vector2D */
Vector2D operator+(const Vector2D& one, const Vector2D& other)
{
  Vector2D res;

  res.x = one.x + other.x;
  res.y = one.y + other.y;

  return res;
}

Vector2D operator-(const Vector2D& one, const Vector2D& other)
{
  Vector2D res;

  res.x = one.x - other.x;
  res.y = one.y - other.y;

  return res;
}

Vector2D operator*(const Vector2D& one, double other)
{
  Vector2D res;

  res.x = one.x * other;
  res.y = one.y * other;

  return res;
}

Vector2D operator/(const Vector2D& one, double other)
{
  Vector2D res;

  res.x = one.x / other;
  res.y = one.y / other;

  return res;
}

/* Vector */
Vector operator+(const Vector& one, const Vector& other)
{
  Vector res;

  res.x = one.x + other.x;
  res.y = one.y + other.y;
  res.z = one.z + other.z;

  return res;
}

Vector operator-(const Vector& one, const Vector& other)
{
  Vector res;

  res.x = one.x - other.x;
  res.y = one.y - other.y;
  res.z = one.z - other.z;

  return res;
}

Vector operator*(const Vector& one, double other)
{
  Vector res;

  res.x = one.x / other;
  res.y = one.y / other;
  res.z = one.z / other;

  return res;
}

Vector operator/(const Vector& one, double other)
{
  Vector res;

  res.x = one.x / other;
  res.y = one.y / other;
  res.z = one.z / other;

  return res;
}

