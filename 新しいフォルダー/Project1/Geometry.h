#pragma once


//サイズを表す構造体
struct Size {
	float w;//幅
	float h;//高さ
};

//2D座標・ベクトルを表す構造体
struct Vector2 {
	Vector2():x(0),y(0){}
	Vector2(float inx,float iny):x(inx),y(iny){}
	float x, y;
	///ベクトルの大きさを返します
	float Magnitude()const;
	//
	float SQMagnitude()const;
	
	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector2 Normalized()const;

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	void operator/=(float div);
	bool operator == (const Vector2& val)const;

	void Rotate90();
	Vector2 Rotated90()const;

	static const Vector2 Zero() {
		return Vector2(0.0f,0.0f);
	}

	Vector2 operator*(float scale);
	Vector2 operator-() const{
		return Vector2(-x, -y);
	}
};


Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);
Vector2 operator*(const Vector2& va,float scale);
Vector2 operator/(const Vector2& va,float div);

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

//とりあえず「座標」って意味だとベクタより
//Positionのほうがよくね？って理由でこの名前
typedef Vector2 Position2;


//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0) ,z(0){}
	Vector3(float inx, float iny,float inz) :x(inx), y(iny) ,z(inz){}
	float x, y,z;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector3 Normalized()const;

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	//Vector3 operator*(const Vector3& v)const;
	Vector3 operator-()const {
		return Vector3(-x, -y,-z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

Vector3 operator*(float f, const Vector3 vb);

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///内積演算子
float operator*(const Vector3& va, const Vector3& vb);

///外積演算子
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

// Max
Vector3 Max(const Vector3& v, const Vector3 b);

///円を表す構造体
struct Circle {
	float radius;//半径
	Position2 pos; //中心座標
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///球を表す構造体
//struct Sphere {
//	float radius;//半径
//	Position3 pos; //中心座標
//	Sphere() :radius(0), pos(0, 0,0) {}
//	Sphere(float r, Position3& p) :radius(r), pos(p) {}
//};
//
//// 平面
//struct Plane
//{
//	Vector3 N;	//法線ベクトル
//	float d;	// 原点からのオフセット(ただし-方向)
//	Plane(const Vector3& n,float offset = 0.0f);
//};

///矩形を表す構造体
struct Rect {
	Position2 center; //中心座標
	int w, h;//幅,高さ
	Rect() : center(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		center(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		center(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		center.x = x;
		center.y = y;
	}
	void SetCenter(const Position2& inpos) {
		center.x = inpos.x;
		center.y = inpos.y;
	}
	Vector2 Center() {
		return center;
	}
	float Left() { return center.x - w / 2; }
	float Top() { return center.y - h / 2; }
	float Right() { return center.x + w / 2; }
	float Bottom() { return center.y + h / 2; }
	void Draw();//自分の矩形を描画する
	void Draw(Vector2& offset);//自分の矩形を描画する(オフセット付き)
};

