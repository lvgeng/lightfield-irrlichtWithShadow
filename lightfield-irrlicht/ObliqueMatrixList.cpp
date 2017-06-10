#include "ObliqueMatrixList.h"
#include <irrlicht.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


ObliqueMatrixList::ObliqueMatrixList(
	double widthInScene, 
	double heightInScene, 
	int widthByPixel, 
	int heightByPixel, 
	double widthBymm, 
	double heightBymm, 
	double renderzoneWidthBymm,
	double renderzoneHeightBymm,
	double thicknessBymm, 
	double refractionIndex)
{
	wInScene = widthInScene;	//Decided by the WH ratio and heightInScene.
	hInScene = heightInScene;	//Usually it would be 2. 
	wByPixel = widthByPixel;	//It is for the subimages, not the entire display zone.
	hByPixel = heightByPixel;	//It is for the subimages, not the entire display zone.
	wBymm = widthBymm;			//It is for the subimages, not the entire display zone.
	hBymm = heightBymm;			//It is for the subimages, not the entire display zone.
	rWidthBymm = renderzoneWidthBymm;
	rHeightBymm = renderzoneHeightBymm;
	tBymm = thicknessBymm;		//It is for the subimages, not the entire display zone.
	refractionI = refractionIndex;

	projectionMatrixList.resize(wByPixel);
	viewMatrixList.resize(wByPixel);
	for (int i = 0; i < wByPixel; i++)
	{
		projectionMatrixList[i].resize(hByPixel);
		viewMatrixList[i].resize(hByPixel);
		for (int j = 0; j < hByPixel; j++)
		{
			projectionMatrixList[i][j] = new irr::core::matrix4();
			irr::core::matrix4* projectionMatrix = new irr::core::matrix4();
			projectionMatrix->buildProjectionMatrixOrthoLH(wInScene, hInScene, -10000, 10000);
			irr::core::matrix4* obliqueMatrix = new irr::core::matrix4();

			double x = wBymm / 2 + (-0.5 - (double)i) * wBymm / wByPixel;
			double y = ((double)j + 0.5) * hBymm / hByPixel - hBymm / 2;
			double h2 = (pow(x,2) + pow(y,2)) * (1 - refractionI) * (1 + refractionI) + pow(tBymm,2);
			double h = 0;
			if(h2 >= 0)
			{
				h = sqrt(h2) / refractionI;
			}
			// double h = sqrt((pow(x,2) + pow(y,2)) * (1 - refractionI) * (1 + refractionI) + pow(tBymm,2)) / refractionI; //The interesting thing is, there will still be some outputs even if the input is a negative value... Not so sure if it is a good thing. but for test it is enough.


			irr::f32 valueOfMatrixElement[16] = {
				1,0,0,0,
				0,1,0,0,
				x / h,
				y / h,
				1,0,
				0,0,0,1 };
			obliqueMatrix->setM(valueOfMatrixElement);
			projectionMatrixList[i][j]->setbyproduct(*projectionMatrix, *obliqueMatrix); //Something need to be aware of is that irr::core::matrix4::setbyproduct(A,B) will return the result of BA, rather than AB.
			// if (i%10==0&&j%10==0)
			// {
			// 	std::cout << "X=" << x << "\n" << "Y=" << y << "\n" << "h=" << h << "\n\n";
			// }
			
			viewMatrixList[i][j] = new irr::core::matrix4();
			viewMatrixList[i][j]->buildCameraLookAtMatrixLH(vector3df(0, 0, 2 * h / rHeightBymm), vector3df(0, 0, 100), vector3df(0, 1, 0));;
			// std::cout << "X=" << x << "\n" << "Y=" << y << "\n" << "h=" << h << "\n\n" << rWidthBymm <<"\n\n";

		}
	}
}

ObliqueMatrixList::~ObliqueMatrixList()
{
}

irr::core::matrix4 * ObliqueMatrixList::getProjectionMatrixByPixel(int x, int y)
{
	return projectionMatrixList[x][y];
}

irr::core::matrix4 * ObliqueMatrixList::getViewMatrixByPixel(int x, int y)
{
	return viewMatrixList[x][y];
}