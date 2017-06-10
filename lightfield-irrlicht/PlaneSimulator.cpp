#include "PlaneSimulator.h"
#include <math.h>


vector2df PlaneSimulator::getCoorinatesInSubimage(int subimageCountX, int subimageCountY)
{
	return coordinatesInSubimagesList[subimageCountX][subimageCountY];
}

PlaneSimulator::PlaneSimulator(vector3df cameraPositionInput, int widthOfRenderzoneByPixel, int heightOfRenderzoneByPixel, int widthOfSubimageByPixel, int heightOfSubimageByPixel, double widthOfSubimageBymm, double heightOfSubimageBymm, double thicknessOfTransparentMaterialBetweenDevices, double refractionIndexOfTransparentMaterial, int widthOfHoleByPixel, int HeightOfHoleByPixle)
{
	cameraPosition = cameraPositionInput;
	widDisplayzoneByPixel = widthOfRenderzoneByPixel;
	heiDisplayzoneByPixel = heightOfRenderzoneByPixel;
	widSubimageByPixel = widthOfSubimageByPixel;
	heiSubimageByPixel = heightOfSubimageByPixel;
	widSubimageBymm = widthOfSubimageBymm;
	heiSubimageBymm = heightOfSubimageBymm;
	thickness = thicknessOfTransparentMaterialBetweenDevices;
	n = refractionIndexOfTransparentMaterial;

	coordinatesInSubimagesList.resize(widDisplayzoneByPixel / widSubimageByPixel);
	centerCoordinatesOfTargetPixelList.resize(widDisplayzoneByPixel / widSubimageByPixel);
	for (int subimageCountX = 0; subimageCountX < widDisplayzoneByPixel / widSubimageByPixel; subimageCountX++)
	{
		coordinatesInSubimagesList[subimageCountX].resize(heiDisplayzoneByPixel / heiSubimageByPixel);
		centerCoordinatesOfTargetPixelList[subimageCountX].resize(heiDisplayzoneByPixel / heiSubimageByPixel);
		for (int subimageCountY = 0; subimageCountY < heiDisplayzoneByPixel / heiSubimageByPixel; subimageCountY++)
		{
			int coordinateX = widSubimageByPixel * (subimageCountX + 0.5);//The center of the subimage.
			int coordinateY = heiSubimageByPixel * (subimageCountY + 0.5);

			double x = cameraPosition.X - (2 * (double)coordinateX / (double)heiDisplayzoneByPixel - (double)widDisplayzoneByPixel / (double)heiDisplayzoneByPixel);
			double y = cameraPosition.Y - (1 - 2 * (double)coordinateY / (double)heiDisplayzoneByPixel);
			double z = cameraPosition.Z;

			double h = thickness / sqrt(pow(n,2) + (pow(n, 2)-1)*((pow(x,2)+pow(y,2))/pow(z,2)));//By mm

			centerCoordinatesOfTargetPixelList[subimageCountX][subimageCountY] = vector2df((double)widSubimageByPixel*(0.5+h*x/z/widSubimageBymm), (double)heiSubimageByPixel*(0.5 -h*y/z/heiSubimageBymm));
			coordinatesInSubimagesList[subimageCountX][subimageCountY] = vector2df((int)(widSubimageByPixel * subimageCountX + centerCoordinatesOfTargetPixelList[subimageCountX][subimageCountY].X - 0.5 + 0.5), (int)(heiSubimageByPixel * subimageCountY + centerCoordinatesOfTargetPixelList[subimageCountX][subimageCountY].Y -0.5 + 0.5)); //The following 0.5 is for the closest int. Well... positive only.
		}
	}
	//n = refractionIndexOfTransparentMaterial;
}

PlaneSimulator::~PlaneSimulator()
{
}
