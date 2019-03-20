#pragma once

#include "vec.h"

class Transform3D {
public:
	double value[4][4];

	friend Transform3D operator* (const Transform3D &a, const Transform3D &b){
		Transform3D res;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				double r = 0;
				for(int k=0;k<4;k++){
					r += (a.value[i][k]) * (b.value[k][j]);
				}
				res.value[i][j] = r;
			}
		}
		return res;
	}
	friend vec<3> operator* (const Transform3D &a, const vec<3> &b){
		vec<4> _b, c;
		_b.x = b.x;
		_b.y = b.y;
		_b.z = b.z;
		_b.w = 1;

		for(int i=0;i<4;i++){
			double r = 0;
			for(int k=0;k<4;k++){
				r += (a.value[i][k]) * (_b.comp[k]);
			}
			c.comp[i] = r;
		}

		vec<3> res;
		res.x = c.x/c.w;
		res.y = c.y/c.w;
		res.z = c.z/c.w;
		return res;
	}

	void compositeWith(const Transform3D &transform){
		*this = transform * (*this);
	}

	static Transform3D Zero(){
		Transform3D transform;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				transform.value[i][j] = 0;
			}
		}
		return transform;
	}

	static Transform3D Identity(){
		Transform3D transform = Zero();
		for(int i=0;i<4;i++){
			transform.value[i][i] = 1;
		}
		return transform;
	}

	static Transform3D Translate(const vec<3> &t){
		Transform3D transform = Identity();
		transform.value[0][3] = t.x;
		transform.value[1][3] = t.y;
		transform.value[2][3] = t.z;
		return transform;
	}

	static Transform3D Scale(const vec<3> &s){
		Transform3D transform = Identity();
		transform.value[0][0] = s.x;
		transform.value[1][1] = s.y;
		transform.value[2][2] = s.z;
		return transform;
	}

	static Transform3D RotateX(double angle){
		Transform3D transform = Identity();
		transform.value[1][1] = +cos(angle);
		transform.value[1][2] = -sin(angle);
		transform.value[2][1] = +sin(angle);
		transform.value[2][2] = +cos(angle);
		return transform;
	}

	static Transform3D RotateX(double angle, const vec<3> &p){
		return Translate(p)*(RotateX(angle)*Translate(-p));
	}

	static Transform3D RotateY(double angle){
		Transform3D transform = Identity();
		transform.value[0][0] = +cos(angle);
		transform.value[0][2] = +sin(angle);
		transform.value[2][0] = -sin(angle);
		transform.value[2][2] = +cos(angle);
		return transform;
	}

	static Transform3D RotateY(double angle, const vec<3> &p){
		return Translate(p)*(RotateY(angle)*Translate(-p));
	}

	static Transform3D RotateZ(double angle){
		Transform3D transform = Identity();
		transform.value[0][0] = +cos(angle);
		transform.value[0][1] = -sin(angle);
		transform.value[1][0] = +sin(angle);
		transform.value[1][1] = +cos(angle);
		return transform;
	}

	static Transform3D RotateZ(double angle, const vec<3> &p){
		return Translate(p)*(RotateZ(angle)*Translate(-p));
	}

	static Transform3D ObliqueProject(){
		Transform3D transform = Identity();
		transform.value[0][2] = -1/sqrt(2);
		transform.value[1][2] = -1/sqrt(2);
		return transform;
	}

	static Transform3D ReflectOrigin(){
		vec<3> s;
		s.x = -1;
		s.y = -1;
		s.z = -1;
		return Scale(s);
	}
	static Transform3D ReflectX(){
		vec<3> s;
		s.x = +1;
		s.y = -1;
		s.z = -1;
		return Scale(s);
	}
	static Transform3D ReflectY(){
		vec<3> s;
		s.x = -1;
		s.y = +1;
		s.z = -1;
		return Scale(s);
	}
	static Transform3D ReflectZ(){
		vec<3> s;
		s.x = -1;
		s.y = -1;
		s.z = +1;
		return Scale(s);
	}
	static Transform3D ReflectXOY(){
		vec<3> s;
		s.x = +1;
		s.y = +1;
		s.z = -1;
		return Scale(s);
	}
	static Transform3D ReflectYOZ(){
		vec<3> s;
		s.x = -1;
		s.y = +1;
		s.z = +1;
		return Scale(s);
	}
	static Transform3D ReflectZOX(){
		vec<3> s;
		s.x = +1;
		s.y = -1;
		s.z = +1;
		return Scale(s);
	}

	static Transform3D ShearX(const double d, const double g){
		Transform3D Transform3D = Identity();
		Transform3D.value[0][1] = d;
		Transform3D.value[0][2] = g;
		return Transform3D;
	}
	static Transform3D ShearY(const double b, const double h){
		Transform3D Transform3D = Identity();
		Transform3D.value[1][0] = b;
		Transform3D.value[1][2] = h;
		return Transform3D;
	}
	static Transform3D ShearZ(const double c, const double f){
		Transform3D Transform3D = Identity();
		Transform3D.value[2][0] = c;
		Transform3D.value[2][1] = f;
		return Transform3D;
	}

};
