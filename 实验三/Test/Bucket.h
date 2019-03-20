// Bucket.h: interface for the Bucket class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Edge.h"

class Bucket
{
public:
	int y;
	Edge *edgeList;
	Bucket *next;
};
