#ifndef _GLINFACE_H_
#define _GLINFACE_H_

#include <time.h>
#include <vector>

using namespace std;
/*
GL Interface
*/


class GLINface {
	public:
		//-- Constructor
		GLINface();

		//-- Destructor
		~GLINface();

      	//-- GLINface drawCube
		void drawCube(float size);

		//--GLINface drawCubeAxis
		void theAxis();

		//--GLINface drawGrid
		void drawGrid();

		//--GLINface main
		void GLmain(int argc, char **argv);

		vector<double> GLpos;

		vector<double> GLgyro;

	private:
		clock_t rec_time;

};

#endif

