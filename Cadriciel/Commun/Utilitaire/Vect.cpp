#include "Vect.h"
#include <cmath>

//float Vect2::getMagnitude() const {
//   return sqrt((x * x) + (y * y));
//}
//
//void Vect2::normalize() {
//   float magnitude = getMagnitude();
//
//   x /= magnitude;
//   y /= magnitude;
//}
//
//float Vect3::getMagnitude() const {
//   return sqrt((x * x) + (y * y) + (z * z));
//}
//
//void Vect3::normalize() {
//   float magnitude = getMagnitude();
//
//   x /= magnitude;
//   y /= magnitude;
//   z /= magnitude;
//}

//float* Vect2::toArray() const {
//   return reinterpret_cast<float*>(const_cast<Vect2*>(this));
//}
//
//float* Vect3::toArray() const {
//   return reinterpret_cast<float*>(const_cast<Vect3*>(this));
//}
//
//Vect2::operator float*() {
//   return toArray();
//}
//
//Vect3::operator float*() {
//   return toArray();
//}


/*Vect2 operator+(const Vect2& a, const Vect2& b) {
   return Vect2(a.x+b.x, a.y+b.y);
}

Vect3 operator+(const Vect3& a, const Vect3& b) {
   return Vect3(a.x+b.x, a.y+b.y, a.z+b.z);
}

void operator+=(Vect2& a, const Vect2& b) {
   a.x += b.x;
   a.y += b.y;
}
void operator+=(Vect3& a, const Vect3& b) {
   a.x += b.x;
   a.y += b.y;
   a.z += b.z;
}

Vect2 operator-(const Vect2& a, const Vect2& b) {
   return Vect2(a.x-b.x, a.y-b.y);
}

Vect3 operator-(const Vect3& a, const Vect3& b) {
   return Vect3(a.x-b.x, a.y-b.y, a.z-b.z);
}

void operator-=(Vect2& a, const Vect2& b) {
   a.x -= b.x;
   a.y -= b.y;
}
void operator-=(Vect3& a, const Vect3& b) {
   a.x -= b.x;
   a.y -= b.y;
   a.z -= b.z;
}

bool operator<(const Vect2& a, const Vect2& b) {
   return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator<(const Vect3& a, const Vect3& b) {
   return a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
}

Vect2 operator*(const Vect2& a, const float& b) {
   return Vect2(a.x * b, a.y * b);
}

Vect3 operator*(const Vect3& a, const float& b) {
   return Vect3(a.x * b, a.y * b, a.z * b);
}


void operator*=(Vect2& a, const float& b) {
   a.x *= b;
   a.y *= b;
}

void operator*=(Vect3& a, const float& b) {
   a.x *= b;
   a.y *= b;
   a.z *= b;
}

float operator*(const Vect2& a, const Vect2& b) {
   return a.x * b.x + a.y * b.y;
}

float operator*(const Vect3& a, const Vect3& b) {
   return a.x * b.x + a.y * b.y + a.z * b.z;
}*/

