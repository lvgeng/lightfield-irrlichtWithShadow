#pragma once
#include <vector>
#include <irrlicht.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class PlaneSimulator
{
private:
	std::vector< std::vector<vector2df> > coordinatesInSubimagesList;
	std::vector< std::vector<vector2df> > centerCoordinatesOfTargetPixelList;
	vector3df cameraPosition;
	int widDisplayzoneByPixel;
	int heiDisplayzoneByPixel;
	int widSubimageByPixel;
	int heiSubimageByPixel;
	double widSubimageBymm;
	double heiSubimageBymm;
	double thickness;
	double n;

public:
	vector2df getCoorinatesInSubimage(int subimageCountX, int subimageCountY);
	PlaneSimulator(vector3df cameraPositionInput, int widthOfRenderzoneByPixel, int heightOfRenderzoneByPixel, int widthOfSubimageByPixel, int heightOfSubimageByPixel, double widthOfSubimageBymm, double heightOfSubimageBymm, double thicknessOfTransparentMaterialBetweenDevices, double refractionIndexOfTransparentMaterial, int widthOfHoleByPixel, int HeightOfHoleByPixle);
	~PlaneSimulator();
};

