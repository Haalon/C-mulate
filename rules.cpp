#include "automata.h"
#include "CImg.h"

struct Cell
{
	unsigned char val;
	unsigned char hst;
	Cell() : val(0), hst(0){}
	Cell(unsigned char v, unsigned char h) : val(v), hst(h){}
};

Cell init(int x, int y)
{
	if(rand()%100<5)
		return Cell(1,0);
	return Cell(0,0);
}

void visualize(CImg<unsigned char>& img, Field<Cell>& f, int x, int y)
{
	img(x,y,0,0) = 255*(1-f(x,y).val);
	img(x,y,0,1) = 255*(1-f(x,y).val);
	img(x,y,0,2) = 255*(1-f(x,y).val);
}

// Cell rule(Field<Cell>& f, int x, int y)
// {

// 	unsigned char h = f(x,y).hst < 111 ? f(x,y).hst + 1 : f(x,y).hst ;
// 	unsigned char sum = f(x+1,y).val + f(x+2,y).val + f(x+3, y).val +
// 						f(x-1,y).val + f(x-2,y).val + f(x-3, y).val +
// 						f(x,y+1).val + f(x,y+2).val + f(x, y+3).val +
// 						f(x,y-1).val + f(x,y-2).val + f(x, y-3).val;

// 	if(f(x,y).val == 1 && (sum > 5 || sum == 3))
// 		return Cell(1,h);
// 	if(f(x,y).val == 0 && (sum > 7 || sum == 2))
// 		return Cell(1,h);
// 	return Cell(0,0);
// }



// typedef Cell = double

// double init(int x, int y)
// {
// 	if(x ==  N/2 && y == M/2) 
// 		return 1.0; 
// 	return 0.0;
// }

// double rule(Field<double>& f, int x, int y)
// {
// 	double sum = f(x-1,y-1) + f(x,y-1) + f(x+1, y-1) +
// 				 f(x-1,y) +      f(x+1, y)   +
// 				 f(x-1,y+1) + f(x,y+1) + f(x+1, y+1);
// 	if(sum == 0)
// 		return 0;
// 	// return asin( sin(sum/3.2))/PI*2;
// 	return sin(sum/3);

// }

// void visualize(CImg<unsigned char>& img, Field<double>& f, int x, int y)
// {
// 	img(x,y,0,0) = (unsigned char) 127 + 127*f(x,y);
// 	img(x,y,0,1) = (unsigned char) 127 + 127*f(x,y);
// 	img(x,y,0,2) = (unsigned char) 127 + 127*f(x,y);
// }

// GoL
// unsigned char rule(Field<unsigned char>& f, int x, int y)
// {
// 	unsigned char sum = f(x-1,y-1) + f(x,y-1) + f(x+1, y-1) +
// 				 f(x-1,y) +              f(x+1, y)   +
// 				 f(x-1,y+1) + f(x,y+1) + f(x+1, y+1);

// 	if(sum == 3)
// 		return 1;
// 	if(sum == 2 && f(x,y) == 1)
// 		return 1;
// 	return 0;
// }

// unsigned char idk_rule(Field<unsigned char>& f, int x, int y)
// {
// 	unsigned char sum = f(x-1,y-1) + f(x,y-1) + f(x+1, y-1) +
// 				 f(x-1,y) +              f(x+1, y)   +
// 				 f(x-1,y+1) + f(x,y+1) + f(x+1, y+1)+
// 				 f(x,y+2)+f(x,y-2)+f(x+2,y)+f(x-2,y) -
// 				 f(x-2,y-2)-f(x+2,y+2)-f(x-2,y+2)-f(x+2,y-2);

// 	if(f(x,y) == 0 && sum > 4 && sum < 10)
// 		return 1;
// 	if(f(x,y) == 1 && ((sum > 2 && sum < 9) || sum == 12))
// 		return 1;
// 	return 0;
// }

Cell rule(Field<Cell>& f, int x, int y)
{

	unsigned char h = 0;
	unsigned char sum = f(x+1,y+1).val + f(x+2,y+2).val + f(x+3, y+3).val +
						f(x-1,y-1).val + f(x-2,y-2).val + f(x-3, y-3).val +
						f(x-1,y+1).val + f(x-2,y+2).val + f(x-3, y+3).val +
						f(x+1,y-1).val + f(x+2,y-2).val + f(x+3, y-3).val;
	unsigned char sum2 = f(x+1,y).val + f(x+2,y).val + f(x+3, y).val +
						f(x-1,y).val + f(x-2,y).val + f(x-3, y).val +
						f(x,y+1).val + f(x,y+2).val + f(x, y+3).val +
						f(x,y-1).val + f(x,y-2).val + f(x, y-3).val;
	if(x >= f.width/3 && x < f.width/3*2 && y >= f.height/3 && y < f.height/3*2)
	{
		if(f(x,y).val == 1 && (sum2 > 5 || sum2 == 3))
			return Cell(1,h);
		if(f(x,y).val == 0 && (sum2 > 7 || sum2 == 2))
			return Cell(1,h);
		return Cell(0,0);
	}
	else
	{
		if(f(x,y).val == 1 && (sum > 5 || sum == 3))
			return Cell(1,h);
		if(f(x,y).val == 0 && (sum > 7 || sum == 2))
			return Cell(1,h);
		return Cell(0,0);
	}
}