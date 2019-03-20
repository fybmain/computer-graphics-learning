// Edge.h: interface for the Edge class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "vec.h"
#include "line.h"

class Edge
{
public:
	double x;
	double invK; // 1/k
	line<2> l;
	Edge *next;

	inline double getMaxY()const{
		return max(l.a.y, l.b.y);
	}
};
