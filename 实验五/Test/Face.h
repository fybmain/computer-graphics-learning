#pragma once

#include <vector>

#include "vec.h"
#include "Transform3D.h"

class Face {
public:
	std::vector<vec<3> > p;

	friend Face operator* (const Transform3D &transform, const Face &f){
		Face res;
		res.p.resize(f.p.size());
		for(size_t i=0;i<f.p.size();i++){
			res.p[i] = transform*(f.p[i]);
		}
		return res;
	}
};
