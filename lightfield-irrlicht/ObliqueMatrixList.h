#pragma once

#include <vector>
#include <irrlicht.h>

class ObliqueMatrixList
{
private:
	double wInScene;
	double hInScene;
	int wByPixel;
	int hByPixel;
	double wBymm;
	double hBymm;
	double rWidthBymm;
	double rHeightBymm;
	double tBymm;

	double refractionI;

	std::vector< std::vector<irr::core::matrix4*> > viewMatrixList;
	std::vector< std::vector<irr::core::matrix4*> > projectionMatrixList;

public:
	ObliqueMatrixList(
		double widthInScene = 2, 
		double heightInScene =2, 
		int widthByPixel = 20, 
		int heightByPixel = 20, 
		double widthBymm = 20, 
		double heightBymm = 20,
		double renderzoneWidthBymm = 800,
		double renderzoneHeightBymm = 600,
		double thicknessBymm = 20, 
		double refractionIndex = 1);
	~ObliqueMatrixList();

	irr::core::matrix4* getViewMatrixByPixel(int x, int y);
	irr::core::matrix4* getProjectionMatrixByPixel(int x, int y);
};

