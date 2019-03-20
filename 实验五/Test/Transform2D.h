#pragma once

#include "vec.h"

class Transform{
public:
	double value[3][3];

	friend Transform operator* (const Transform &a, const Transform &b){
		Transform res;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				double r = 0;
				for(int k=0;k<3;k++){
					r += (a.value[i][k]) * (b.value[k][j]);
				}
				res.value[i][j] = r;
			}
		}
		return res;
	}
	friend vec<2> operator* (const Transform &a, const vec<2> &b){
		vec<3> _b, c;
		_b.x = b.x;
		_b.y = b.y;
		_b.z = 1;

		for(int i=0;i<3;i++){
			double r = 0;
			for(int k=0;k<3;k++){
				r += (a.value[i][k]) * (_b.comp[k]);
			}
			c.comp[i] = r;
		}

		vec<2> res;
		res.x = c.x/c.z;
		res.y = c.y/c.z;
		return res;
	}

	void compositeWith(const Transform &transform){
		*this = transform * (*this);
	}

	static Transform Zero(){
		Transform transform;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				transform.value[i][j] = 0;
			}
		}
		return transform;
	}

	static Transform Identity(){
		Transform transform = Zero();
		for(int i=0;i<3;i++){
			transform.value[i][i] = 1;
		}
		return transform;
	}

	static Transform Translate(const vec<2> &t){
		Transform transform = Identity();
		transform.value[0][2] = t.x;
		transform.value[1][2] = t.y;
		return transform;
	}

	static Transform Scale(const vec<2> &s){
		Transform transform = Identity();
		transform.value[0][0] = s.x;
		transform.value[1][1] = s.y;
		return transform;
	}

	static Transform Sacle(const vec<2> &s, const vec<2> &point){
		return Translate(point)*(Scale(s)*Translate(-point));
	}

	static Transform Rotate(double angle){
		Transform transform = Identity();
		transform.value[0][0] = +cos(angle);
		transform.value[0][1] = -sin(angle);
		transform.value[1][0] = +sin(angle);
		transform.value[1][1] = +cos(angle);
		return transform;
	}

	static Transform Rotate(double angle, const vec<2> &point){
		return Translate(point)*(Rotate(angle)*Translate(-point));
	}

	static Transform ReflectOrigin(){
		vec<2> s;
		s.x = -1;
		s.y = -1;
		return Scale(s);
	}

	static Transform ReflectX(){
		vec<2> s;
		s.x = +1;
		s.y = -1;
		return Scale(s);
	}

	static Transform ReflectY(){
		vec<2> s;
		s.x = -1;
		s.y = +1;
		return Scale(s);
	}

	static Transform Shear(const double b, const double c){
		Transform transform = Identity();
		transform.value[0][1] = b;
		transform.value[1][0] = c;
		return transform;
	}
};
