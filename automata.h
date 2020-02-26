#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

#include "CImg.h"
#include <omp.h>

const double PI = 3.14159265358979323846;

using namespace cimg_library;

template <class T>
struct Field
{
	T * body;
	int width;
	int height;
	Field(int w, int h) : width(w), height(h)
	{
		body = new T [w*h];
	}
	~Field()
	{
		delete[] body;
	}

	T& operator()(int x, int y)
	{
		int x0 = (x < 0 ? x + width : x) % width;
		int y0 = (y < 0 ? y + height : y) % height;
		return body[x0 + width*y0];
	}

	Field<T>& operator=(Field<T>& other)
	{
		width = other.width;
		height = other.height;
		body = other.body;

		return *this;
	} 
	
};

template <class T>
class Automata
{
	using Init = T(*)(int,int);
	using Rule = T(*)(Field<T>&,int,int);
	using Draw = void (*)(CImg<unsigned char>&, Field<T>&, int, int);

	Init init;
	Rule rule;

	Draw draw;

	Field<T>* f1 = NULL;
	Field<T>* f2 = NULL;

	CImg<unsigned char>* img;
public:
	int width;
	int height;
	int step;

	Automata(int w, int h, Init i, Rule r, Draw d)
	{
		width = w;
		height = h;
		init =i;
		rule =r;
		draw = d;
		step = 0;
		f1 = new Field<T>(w,h);
		f2 = new Field<T>(w,h);
		img = new CImg<unsigned char>(w,h,1,3);
	}

	CImg<unsigned char>& show()
	{
		int x,y;
		#pragma omp parallel for private(x,y) num_threads(8)
		for (x = 0; x < width; ++x)
			for (y = 0; y < height; ++y)
				draw(*img, *f1, x, y);
		return *img;
	}

	void next()
	{
		int x,y;
		#pragma omp parallel for private(x,y) num_threads(8)
		for (x = 0; x < width; ++x)
			for (y = 0; y < height; ++y)
				(*f2)(x,y) = rule(*f1, x, y);

		auto f3 = f1;
		f1 = f2;
		f2 = f3;
		step++;
	}

	void initialize()
	{
		int x,y;
		#pragma omp parallel for private(x,y) num_threads(8)
		for (x = 0; x < width; ++x)
			for (y = 0; y < height; ++y)
				(*f1)(x,y) = init(x,y);
	}

	T& operator()(int x, int y)
	{
		return (*f1)(x,y);
	}
};

#endif