#pragma once

#include <cmath>

template<unsigned dim>
class vec {
public:
	double comp[dim];
};

template<>
class vec<1> {
public:
	union {
		double comp[1];
		struct {
			double x;
		};
	};
	static vec<1> unit() {
		vec<1> v;
		v.x = 1;
		return v;
	}
};

template<>
class vec<2> {
public:
	union {
		double comp[2];
		struct {
			double x, y;
		};
	};
	static vec<2> unit(double angle) {
		vec<2> v;
		v.x = cos(angle);
		v.y = sin(angle);
		return v;
	}
	inline operator POINT () const {
		POINT p;
		p.x = (LONG)round(this->x);
		p.y = (LONG)round(this->y);
		return p;
	}
};

template<>
class vec<3> {
public:
	union {
		double comp[3];
		struct {
			double x, y, z;
		};
		struct {
			double r, g, b;
		};
	};
};

template<>
class vec<4> {
public:
	union {
		double comp[4];
		struct {
			double x, y, z, w;
		};
		struct {
			double r, g, b, a;
		};
	};
};

typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

template<unsigned dim>
inline vec<dim> operator* (const vec<dim> a, const double b) {
	vec<dim> res;
	for (int i = 0; i < dim; i++) {
		res.comp[i] = a.comp[i] * b;
	}
	return res;
}
