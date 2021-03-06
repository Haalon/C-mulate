#include "CImg.h"
#include <iostream>
#include <math.h> 
#include <omp.h>
#include <random>
#include <ctime>
#include "automata.h"
#include "rules.cpp"

using namespace std;
using namespace cimg_library;

#define WIDTH 500
#define HEIGHT 500
#define SKIP 10
#define SCALE 2
				 

int nthreads=8;
int main(int argc, char const *argv[])
{
	// mask = CImg<unsigned char>("mask.jpg");

	srand(time(0));

	Automata<Cell> atmt(WIDTH, HEIGHT, init, rule, visualize);

	atmt.initialize();
	auto img = atmt.show();

	CImgDisplay main_disp(img,"C-mulate");
	main_disp.resize(WIDTH*SCALE, HEIGHT*SCALE);


	double start = omp_get_wtime();
	bool flag  = true;
    while (!main_disp.is_closed() )
    {
    	cout << ""; // somehow it disables strange delay after unpausing
    	if(main_disp.key() == cimg::keySPACE)
    	{
    		flag = !flag;
    		main_disp.flush();
    	}

    	if(main_disp.key() == cimg::keyP)
    	{
    		img.save("img/c.png", atmt.step, 12);
    		main_disp.flush();
    	}

 		if(flag)
 		{
	    	atmt.next();
	    	if(atmt.step % SKIP ==0)
	    	{
	    		img = atmt.show();
	    		cout<<atmt.step << " in: " << (omp_get_wtime() - start)*1000 << '\n' << flush;

	    		start = omp_get_wtime();
	    	}
    	}

    	if(atmt.step % 500 == 1)
    		img.save("img/c.png", atmt.step, 12);
		main_disp.display(img);		

    }
	return 0;
}