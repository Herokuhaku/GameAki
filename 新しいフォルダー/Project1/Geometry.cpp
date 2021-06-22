#include"Geometry.h"
#include<DxLib.h>
#include<cmath>
#include <algorithm>

void
Rect::Draw() {
	DxLib::DrawBox(Left()*2, Top()*2, Right()*2, Bottom()*2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left()+offset.x)*2, (Top()+offset.y)*2, (Right()+offset.x)*2, (Bottom()+offset.y)*2, 0xffffffff, false);
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

void Vector2::operator/=(float div)
{
	x /= div;
	y /= div;
}

bool Vector2::operator==(const Vector2& val)const
{
	return ((x == val.x) && (y == val.y));
}

void Vector2::Rotate90()
{
	std::swap(x,y);
	x = -x;
}

Vector2 Vector2::Rotated90()const
{
	return Vector2(-y,x);
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x*scale, y*scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb){
	return Vector2(va.x - vb.x, va.y - vb.y);
}

Vector2 operator*(const Vector2& va, float scale)
{
	return Vector2(va.x * scale,va.y * scale);
}

Vector2 operator/(const Vector2& va, float div)
{
	return Vector2(va.x / div, va.y / div);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}

float Vector2::SQMagnitude() const
{
	return x*x + y*y;
}


void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized()const {
	Vector2 ret = {x,y};
	ret.Normalize();
	return ret;
}


///内積を返す
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///外積を返す
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///内積演算子
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///外積演算子
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


//-------ここから3Dのターン------
void
Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

//Vector3
//Vector3::operator*(const Vector3& v)const
//{
//	return Vector3(x * v.x, y * v.y, z * v.z);
//}

Vector3
Vector3::operator*(float scale)const {
	return Vector3(x*scale, y*scale,z*scale);
}

Vector3 operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y,va.z+vb.z);
}

Vector3 operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y,va.z-vb.z);
}

Vector3 operator*(float f, const Vector3 vb)
{
	return Vector3(f* vb.x,f * vb.y,f * vb.z);
}

float
Vector3::Magnitude()const {
	return sqrt(x*x+y*y+z*z);
}


void
Vector3::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3
Vector3::Normalized() const{
	float mag = Magnitude();
	return Vector3(x / mag, y / mag,z/mag);
}


///内積を返す
float
Dot(const Vector3& va, const Vector3& vb){
	return va.x*vb.x + va.y*vb.y+va.z*vb.z;
}

///外積を返す
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z*vb.y-va.y*vb.z,va.z*vb.x-va.x*vb.z,va.x*vb.y - vb.x*va.y);
}

///内積演算子
float
operator*(const Vector3& va, const Vector3& vb) {
	return Dot(va, vb);
}

///外積演算子
Vector3
operator%(const Vector3& va, const Vector3& vb) {
	return Cross(va, vb);
}

Vector3 Max(const Vector3& v, const Vector3 b)
{
	Vector3 d;
	d.x = max(v.x, b.x);
	d.y = max(v.y, b.y);
	d.z = max(v.z, b.z);
	return d;
}

void
Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void
Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
