#pragma once

#include <math.h>

const double PI = acos(-1);

template<unsigned dim>
class vec {
public:
	union {
		struct {
			double comp[dim];
		};
	};
	inline double length()const{
		double sum=0;
		for(int i=0;i<dim;i++){
			double c=this->comp[i];
			sum+=c*c;
		}
		return sqrt(sum);
	}
	inline vec<dim> normalized()const;
	inline vec<dim> operator- ()const{
		vec<dim> res;
		for(int i=0;i<dim;i++){
			res.comp[i] = -(this->comp[i]);
		}
		return res;
	}
	inline static vec<dim> zero(){
		vec<dim> res;
		for(int i=0;i<dim;i++){
			res[i] = 0;
		}
		return res;
	}
};

template<>
class vec<1> {
public:
	union {
		struct {
			double comp[1];
		};
		struct {
			double x;
		};
	};
	inline double length()const{
		return this->comp[0];
	}
	inline vec<1> normalized()const;
	inline vec<1> operator- ()const{
		vec<1> res;
		res.x = -(this->x);
		return res;
	}
	inline static vec<1> zero(){
		vec<1> res;
		res.x = 0;
		return res;
	}
	inline static vec<1> unit() {
		vec<1> v;
		v.x = 1;
		return v;
	}
};

template<>
class vec<2> {
public:
	union {
		struct{
			double comp[2];
		};
		struct {
			double x, y;
		};
	};
	inline double length()const{
		double sum=0;
		for(int i=0;i<2;i++){
			double c=this->comp[i];
			sum+=c*c;
		}
		return sqrt(sum);
	}
	inline vec<2> normalized()const;
	inline vec<2> operator- ()const{
		vec<2> res;
		res.x = -(this->x);
		res.y = -(this->y);
		return res;
	}
	inline static vec<2> zero(){
		vec<2> res;
		res.x = 0;
		res.y = 0;
		return res;
	}
	inline static vec<2> unit(double angle) {
		vec<2> v;
		v.x = cos(angle);
		v.y = sin(angle);
		return v;
	}
	inline operator POINT ()const{
		POINT p;
		p.x = (LONG)floor(this->x+0.5);
		p.y = (LONG)floor(this->y+0.5);
		return p;
	}
	inline vec<2>& operator= (const CPoint point){
		this->x = point.x;
		this->y = point.y;
		return (*this);
	}
};

template<>
class vec<3> {
public:
	union {
		struct {
			double comp[3];
		};
		struct {
			double x, y, z;
		};
		struct {
			double red, green, blue;
		};
		struct {
			double r, g, b;
		};
	};
	inline double length()const{
		double sum=0;
		for(int i=0;i<3;i++){
			double c=this->comp[i];
			sum+=c*c;
		}
		return sqrt(sum);
	}
	inline vec<3> normalized()const;
	inline vec<3> operator- ()const{
		vec<3> res;
		res.x = -(this->x);
		res.y = -(this->y);
		res.z = -(this->z);
		return res;
	}
	inline static vec<3> zero(){
		vec<3> res;
		res.x = 0;
		res.y = 0;
		res.z = 0;
		return res;
	}
	inline vec<2> toVec2()const{
		vec<2> res;
		res.x = this->x;
		res.y = this->y;
		return res;
	}
	inline operator COLORREF()const{
		return RGB(this->red*255, this->green*255, this->blue*255);
	}
	inline static vec<3> fromColorRef(const COLORREF colorRef){
		vec<3> res;
		res.red = GetRValue(colorRef)/255.0;
		res.green = GetGValue(colorRef)/255.0;
		res.blue = GetBValue(colorRef)/255.0;
		return res;
	}
};

template<>
class vec<4> {
public:
	union {
		struct {
			double comp[4];
		};
		struct {
			double x, y, z, w;
		};
		struct {
			double red, green, blue, alpha;
		};
		struct {
			double r, g, b, a;
		};
	};
	inline double length()const{
		double sum=0;
		for(int i=0;i<4;i++){
			double c=this->comp[i];
			sum+=c*c;
		}
		return sqrt(sum);
	}
	inline vec<4> normalized()const;
	inline vec<4> operator- ()const{
		vec<4> res;
		res.x = -(this->x);
		res.y = -(this->y);
		res.z = -(this->z);
		res.w = -(this->w);
		return res;
	}
	inline static vec<4> zero(){
		vec<4> res;
		res.x = 0;
		res.y = 0;
		res.z = 0;
		res.w = 0;
		return res;
	}
};

typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

typedef vec<3> rgb;
typedef vec<4> rgba;

template<unsigned dim>
inline vec<dim> operator+ (const vec<dim> a, const vec<dim> b) {
	vec<dim> res;
	for (int i = 0; i < dim; i++) {
		res.comp[i] = a.comp[i] + b.comp[i];
	}
	return res;
}

template<unsigned dim>
inline vec<dim> operator- (const vec<dim> a, const vec<dim> b) {
	return a+(-b);
}

template<unsigned dim>
inline vec<dim> operator* (const vec<dim> a, const double b) {
	vec<dim> res;
	for (int i = 0; i < dim; i++) {
		res.comp[i] = a.comp[i] * b;
	}
	return res;
}

template<unsigned dim>
inline vec<dim> operator* (const vec<dim> a, const vec<dim> b) {
	vec<dim> res;
	for (int i = 0; i < dim; i++) {
		res.comp[i] = a.comp[i] * b.comp[i];
	}
	return res;
}

template<unsigned dim>
inline vec<dim> operator/ (const vec<dim> a, const double b) {
	vec<dim> res;
	for (int i = 0; i < dim; i++) {
		res.comp[i] = a.comp[i] / b;
	}
	return res;
}

template<unsigned dim>
inline vec<dim> vec<dim>::normalized()const{
	return (*this)/(this->length());
}

template<unsigned dim>
inline vec<dim> floor(const vec<dim> v){
	vec<dim> result;
	for(int i=0;i<dim;i++){
		result.comp[i] = floor(v.comp[i]);
	}
	return result;
}

template<unsigned dim>
inline vec<dim> round(const vec<dim> v){
	vec<dim> result;
	for(int i=0;i<dim;i++){
		result.comp[i] = floor(v.comp[i]+0.5);
	}
	return result;
}

inline double gradient(const vec<2> a, const vec<2> b){
	return (b.y-a.y)/(b.x-a.x);
}

inline double cross(const vec<2> &a, const vec<2> &b){
	return a.x*b.y-b.x*a.y;
}
