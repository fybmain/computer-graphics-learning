// FillContext.h: interface for the FillContext class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <vector>
#include <string>

#include "Edge.h"
#include "Bucket.h"

class FillContext  
{
protected:
	Edge *edge;
	Bucket *bucket;

public:
	std::vector<vec<2> > p;
	vec<3> color;

	FillContext(){
		edge = NULL;
		bucket = NULL;
	}
	~FillContext(){
		FreeMemory();
	}

	void CreateBucket(){
		int minY = (int)floor(p[0].y);
		int maxY = (int)ceil(p[0].y);
		int minYind, i;
		for(i=1;i<p.size();i++){
			double y = p[i].y;
			if(y<minY){
				minY = (int)floor(y);
				minYind = i;
			}
			if(y>maxY){
				maxY = (int)ceil(y);
			}
		}

		Bucket **pNext = &(this->bucket);
		int y;
		for(y=minY;y<=maxY;y++){
			Bucket *current = new Bucket();
			current->y = y;
			current->edgeList = NULL;
			current->next = NULL;
			*pNext = current;
			pNext = &(current->next);
		}
	}

	void CreateEdge(){
		const int s = p.size();
		int i;
		for(i=0;i<s;i++){
			const int j = (i+1)%s;
			Bucket *currentBucket = this->bucket;
			Edge *currentEdge;

			if(p[i].y<p[j].y){
				currentEdge = new Edge();
				currentEdge->x = p[i].x;
				currentEdge->invK = 1/gradient(p[i], p[j]);
				currentEdge->l.a = p[i];
				currentEdge->l.b = p[j];
				while(currentBucket->y<p[i].y){
					currentBucket = currentBucket->next;
				}
			}else if(p[i].y>p[j].y){
				currentEdge = new Edge();
				currentEdge->x = p[j].x;
				currentEdge->invK = 1/gradient(p[j], p[i]);
				currentEdge->l.a = p[i];
				currentEdge->l.b = p[j];
				while(currentBucket->y<p[j].y){
					currentBucket = currentBucket->next;
				}
			}
			if((p[i].y<p[j].y)||(p[i].y>p[j].y)){
				Edge **pNext = &(currentBucket->edgeList);
				while(*pNext!=NULL){
					pNext=&((*pNext)->next);
				}
				*pNext = currentEdge;
				currentEdge->next = NULL;
			}
		}
	}

	void Fill(CDC *dc){
		Edge *p1=NULL, *p2=NULL;
		Bucket *currentBucket=this->bucket;
		for(;currentBucket!=NULL;currentBucket=currentBucket->next){
			/*
			char buf[1000];
			sprintf(buf, "y=%d", currentBucket->y);
			MessageBox(NULL, buf, "TT", 0);
			*/
			Edge *currentEdge = currentBucket->edgeList;
			for(;currentEdge!=NULL;currentEdge=currentEdge->next){
				Edge *pEdge = new Edge();
				*pEdge = *currentEdge;
				AddET(pEdge);
			}
			ETOrder();
			p1=this->edge;
			if(p1==NULL){
				return;
			}
			while(currentBucket->y>=p1->getMaxY()){
				Edge *tmp = p1;
				p1=p1->next;
				delete tmp;
				this->edge = p1;
				if(this->edge==NULL){
					return;
				}
			}
			if(p1->next!=NULL){
				p2=p1;
				p1=p2->next;
			}
			while(p1!=NULL){
				if(currentBucket->y>=p1->getMaxY()){
					Edge *temp = p1;
					p2->next = p1->next;
					p1 = p2->next;
					delete temp;
				}else{
					p2=p1;
					p1=p2->next;
				}
			}
			bool inSection = false;
			double xb,xe;
			for(p1=this->edge;p1!=NULL;p1=p1->next){
				if(!inSection){
					xb = p1->x;
					inSection = true;
				}else{
					xe = p1->x;
					double x;
					for(x=xb;x<xe;x++){
						vec<2> point;
						point.x = x;
						point.y = currentBucket->y;
						dc->SetPixelV(round(point), this->color);
					}
					inSection=false;
				}
			}
			for(p1=this->edge;p1!=NULL;p1=p1->next){
				p1->x = p1->x+p1->invK;
			}
		}
	}

	void AddET(Edge *newEdge){
		Edge **pNext = &(this->edge);
		while(*pNext!=NULL){
			pNext = &((*pNext)->next);
		}
		*pNext = newEdge;
		newEdge->next = NULL;
	}

	void ETOrder(){
		Edge *p1=this->edge;
		Edge *p2;
		int count=1;

		if(p1==NULL){
			return;
		}
		if(p1->next==NULL){
			return;
		}
		while(p1->next!=NULL){
			count++;
			p1=p1->next;
		}
		for(int i=0;i<count-1;i++){
			Edge **pre = &(this->edge);
			p1 = this->edge;
			for(int j=0;j<count-1;j++){
				p2 = p1->next;
				if((p1->x>p2->x)||((p1->x==p2->x)&&(p1->invK>p2->invK))){
					p1->next = p2->next;
					p2->next = p1;
					*pre = p2;
					pre = &(p2->next);
				}else{
					pre = &(p1->next);
					p1 = p1->next;
				}
			}
		}
	}

	inline void FreeMemory(){
		this->DeleteEdgeList(this->edge);

		Bucket *currentBucket = this->bucket;
		while(currentBucket!=NULL){
			Bucket *tmp = currentBucket->next;
			this->DeleteEdgeList(currentBucket->edgeList);
			delete currentBucket;
			currentBucket = tmp;
		}
		this->bucket = NULL;
		this->edge = NULL;
	}

	inline void DeleteEdgeList(Edge *head){
		Edge *currentEdge = head;
		while(currentEdge!=NULL){
			Edge *tmp = currentEdge->next;
			delete currentEdge;
			currentEdge = tmp;
		}
	}

};
