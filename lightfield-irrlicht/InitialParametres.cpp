#include "InitialParametres.h"
#include <iostream>

void InitialParametres::defaultValuesInitializing()
{
	widthOfRenderzoneByPixel = 3840;
	heightOfRenderzoneByPixel = 2160;
	isFullscreen = false;
	widthOfSubimageByPixel = 36;
	heightOfSubimageByPixel = 36;

	xOffsetByPixel = 10;
	yOffsetByPixel = 0;
	/*widthOfSubimageBymm = 5.6;
	heightOfSubimageBymm = 5.6;*/
	widthOfRenderzoneBymm = 597.0;
	heightOfRenderzoneBymm = 335.7;

	thicknessOfTransparentMaterialBetweenDevices = 2.9;
	refractionIndexOfTransparentMaterial = 1.31520778;
	/*refractionIndexOfTransparentMaterial = 1.491756;*/
	//The data comes from the data sheet is 1.491756. Do not change it if unnecessary.
	backgroundColorR = 0;
	backgroundColorG = 0;
	backgroundColorB = 0;

	isAmbientLightEnabled = true;
	ambientLightR = 0.5f;
	ambientLightG = 0.5f;
	ambientLightB = 0.5f;

	isPointLightOneEnabled = true;
	pointLightOnePositionX = -80;
	pointLightOnePositionY = 100;
	pointLightOnePositionZ = -150;
	pointLightOneR = 0.5;
	pointLightOneG = 0.5;
	pointLightOneB = 0.5;
	pointLightOneRange = 500;

	isPointLightTwoEnabled = false;
	pointLightTwoPositionX = 0;
	pointLightTwoPositionY = 0;
	pointLightTwoPositionZ = 0;
	pointLightTwoR = 0;
	pointLightTwoG = 0;
	pointLightTwoB = 0;
	pointLightTwoRange = 0;

	isMeshOneEnabled = true;
	meshOneModelPath = "../media/SceneBoxes.obj";
	meshOneScale = 1;
	meshOneRotationX = 0;
	meshOneRotationY = 0;
	meshOneRotationZ = 0;
	meshOnePositionX = 0;
	meshOnePositionY = -0.15;
	meshOnePositionZ = 0.5;

	isMeshTwoEnabled = true;
	meshTwoModelPath = "../media/Floor.obj";
	meshTwoScale = 1;
	meshTwoRotationX = -90;
	meshTwoRotationY = 0;
	meshTwoRotationZ = 0;
	meshTwoPositionX = 0;
	meshTwoPositionY = 0;
	meshTwoPositionZ = 1.1;

	isMeshThreeEnabled = true;
	meshThreeModelPath = "../media/Floor.obj";
	meshThreeScale = 1;
	meshThreeRotationX = 0;
	meshThreeRotationY = 0;
	meshThreeRotationZ = 0;
	meshThreePositionX = 0;
	meshThreePositionY = -0.8;
	meshThreePositionZ = 0.5;

	isTestSubjectSpinning = false;
	isAimmingAssistantEnabled = false;
	//isSimulating = false;
	isSingleFrameRenderingAndQuitMode = true;

	isLightField = true;

	virtualCameraPosR = 1500;
	virtualCameraPosH = 300;
	virtualCameraPosTheta = 0.0;
	virtualCameraFOV = 30.0;

	widthOfSubimageBymm = widthOfRenderzoneBymm*widthOfSubimageByPixel/widthOfRenderzoneByPixel;
	heightOfSubimageBymm = heightOfRenderzoneBymm*heightOfSubimageByPixel/heightOfRenderzoneByPixel;

	heightOfProjectionPanelInScene = 2;
	widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfRenderzoneByPixel / heightOfRenderzoneByPixel;

	xSubimageCountMax = widthOfRenderzoneByPixel / widthOfSubimageByPixel;
	ySubimageCountMax = heightOfRenderzoneByPixel / heightOfSubimageByPixel;
}

InitialParametres::~InitialParametres()
{
}

InitialParametres::InitialParametres()
{
	defaultValuesInitializing();
}

InitialParametres::InitialParametres(char* xmlConfigFilePath)
{
	pugi::xml_document doc;
	pugi::xml_parse_result resultConfigfile = doc.load_file(xmlConfigFilePath);
	if (!resultConfigfile)
	{
		defaultValuesInitializing();
    //pugi::xml_document doc;
    // add node with some name
    pugi::xml_node nodeSettings = doc.append_child("Settings");
		pugi::xml_node nodeDisplaySetting = nodeSettings.append_child("displaySetting");
			nodeDisplaySetting.append_child("widthOfRenderzoneByPixel").append_attribute("value") = widthOfRenderzoneByPixel;
			nodeDisplaySetting.append_child("heightOfRenderzoneByPixel").append_attribute("value") = heightOfRenderzoneByPixel;
			nodeDisplaySetting.append_child("isFullscreen").append_attribute("value") = isFullscreen;
			nodeDisplaySetting.append_child("widthOfSubimageByPixel").append_attribute("value") = widthOfSubimageByPixel;
			nodeDisplaySetting.append_child("heightOfSubimageByPixel").append_attribute("value") = heightOfSubimageByPixel;

			nodeDisplaySetting.append_child("xOffsetByPixel").append_attribute("value") = xOffsetByPixel;
			nodeDisplaySetting.append_child("yOffsetByPixel").append_attribute("value") = yOffsetByPixel;

		pugi::xml_node nodeRealworldSetting = nodeSettings.append_child("realworldSetting");
			//nodeRealworldSetting.append_child("widthOfSubimageBymm").append_attribute("value") = widthOfSubimageBymm;
			//nodeRealworldSetting.append_child("heightOfSubimageBymm").append_attribute("value") = heightOfSubimageBymm;

			nodeRealworldSetting.append_child("widthOfRenderzoneBymm").append_attribute("value") = widthOfRenderzoneBymm;
			nodeRealworldSetting.append_child("heightOfRenderzoneBymm").append_attribute("value") = heightOfRenderzoneBymm;

			nodeRealworldSetting.append_child("thicknessOfTransparentMaterialBetweenDevices").append_attribute("value") = thicknessOfTransparentMaterialBetweenDevices;
			nodeRealworldSetting.append_child("refractionIndexOfTransparentMaterial").append_attribute("value") = refractionIndexOfTransparentMaterial;

		pugi::xml_node nodeFunctionSetting = nodeSettings.append_child("functionSetting");
			
			nodeFunctionSetting.append_child("backgroundColorR").append_attribute("value") = backgroundColorR;
			nodeFunctionSetting.append_child("backgroundColorG").append_attribute("value") = backgroundColorG;
			nodeFunctionSetting.append_child("backgroundColorB").append_attribute("value") = backgroundColorB;

			pugi::xml_node nodeIsAmbientLightEnabled = nodeFunctionSetting.append_child("isAmbientLightEnabled");
				nodeIsAmbientLightEnabled.append_attribute("value") = isAmbientLightEnabled;
				nodeIsAmbientLightEnabled.append_child("ambientLightR").append_attribute("value") = ambientLightR;
				nodeIsAmbientLightEnabled.append_child("ambientLightG").append_attribute("value") = ambientLightG;
				nodeIsAmbientLightEnabled.append_child("ambientLightB").append_attribute("value") = ambientLightB;
			
			pugi::xml_node nodeIsPointLightOneEnabled = nodeFunctionSetting.append_child("isPointLightOneEnabled");
				nodeIsPointLightOneEnabled.append_attribute("value") = isPointLightOneEnabled;
				nodeIsPointLightOneEnabled.append_child("pointLightOnePositionX").append_attribute("value") = pointLightOnePositionX;
				nodeIsPointLightOneEnabled.append_child("pointLightOnePositionY").append_attribute("value") = pointLightOnePositionY;
				nodeIsPointLightOneEnabled.append_child("pointLightOnePositionZ").append_attribute("value") = pointLightOnePositionZ;

				nodeIsPointLightOneEnabled.append_child("pointLightOneR").append_attribute("value") = pointLightOneR;
				nodeIsPointLightOneEnabled.append_child("pointLightOneG").append_attribute("value") = pointLightOneG;
				nodeIsPointLightOneEnabled.append_child("pointLightOneB").append_attribute("value") = pointLightOneB;

				nodeIsPointLightOneEnabled.append_child("pointLightOneRange").append_attribute("value") = pointLightOneRange;

			pugi::xml_node nodeIsPointLightTwoEnabled = nodeFunctionSetting.append_child("isPointLightTwoEnabled");
				nodeIsPointLightTwoEnabled.append_attribute("value") = isPointLightTwoEnabled;
				nodeIsPointLightTwoEnabled.append_child("pointLightTwoPositionX").append_attribute("value") = pointLightTwoPositionX;
				nodeIsPointLightTwoEnabled.append_child("pointLightTwoPositionY").append_attribute("value") = pointLightTwoPositionY;
				nodeIsPointLightTwoEnabled.append_child("pointLightTwoPositionZ").append_attribute("value") = pointLightTwoPositionZ;

				nodeIsPointLightTwoEnabled.append_child("pointLightTwoR").append_attribute("value") = pointLightTwoR;
				nodeIsPointLightTwoEnabled.append_child("pointLightTwoG").append_attribute("value") = pointLightTwoG;
				nodeIsPointLightTwoEnabled.append_child("pointLightTwoB").append_attribute("value") = pointLightTwoB;

				nodeIsPointLightTwoEnabled.append_child("pointLightTwoRange").append_attribute("value") = pointLightTwoRange;
			
			pugi::xml_node nodeIsMeshOneEnabled = nodeFunctionSetting.append_child("isMeshOneEnabled");
				nodeIsMeshOneEnabled.append_attribute("value") = isMeshOneEnabled;
					nodeIsMeshOneEnabled.append_child("meshOneModelPath").append_attribute("value") = meshOneModelPath.c_str();
					nodeIsMeshOneEnabled.append_child("meshOneScale").append_attribute("value") = meshOneScale;
					nodeIsMeshOneEnabled.append_child("meshOneRotationX").append_attribute("value") = meshOneRotationX;
					nodeIsMeshOneEnabled.append_child("meshOneRotationY").append_attribute("value") = meshOneRotationY;
					nodeIsMeshOneEnabled.append_child("meshOneRotationZ").append_attribute("value") = meshOneRotationZ;

					nodeIsMeshOneEnabled.append_child("meshOnePositionX").append_attribute("value") = meshOnePositionX;
					nodeIsMeshOneEnabled.append_child("meshOnePositionY").append_attribute("value") = meshOnePositionY;
					nodeIsMeshOneEnabled.append_child("meshOnePositionZ").append_attribute("value") = meshOnePositionZ;

			pugi::xml_node nodeIsMeshTwoEnabled = nodeFunctionSetting.append_child("isMeshTwoEnabled");
				nodeIsMeshTwoEnabled.append_attribute("value") = isMeshTwoEnabled;
					nodeIsMeshTwoEnabled.append_child("meshTwoModelPath").append_attribute("value") = meshTwoModelPath.c_str();
					nodeIsMeshTwoEnabled.append_child("meshTwoScale").append_attribute("value") = meshTwoScale;
					nodeIsMeshTwoEnabled.append_child("meshTwoRotationX").append_attribute("value") = meshTwoRotationX;
					nodeIsMeshTwoEnabled.append_child("meshTwoRotationY").append_attribute("value") = meshTwoRotationY;
					nodeIsMeshTwoEnabled.append_child("meshTwoRotationZ").append_attribute("value") = meshTwoRotationZ;

					nodeIsMeshTwoEnabled.append_child("meshTwoPositionX").append_attribute("value") = meshTwoPositionX;
					nodeIsMeshTwoEnabled.append_child("meshTwoPositionY").append_attribute("value") = meshTwoPositionY;
					nodeIsMeshTwoEnabled.append_child("meshTwoPositionZ").append_attribute("value") = meshTwoPositionZ;

			pugi::xml_node nodeIsMeshThreeEnabled = nodeFunctionSetting.append_child("isMeshThreeEnabled");
				nodeIsMeshThreeEnabled.append_attribute("value") = isMeshThreeEnabled;
					nodeIsMeshThreeEnabled.append_child("meshThreeModelPath").append_attribute("value") = meshThreeModelPath.c_str();
					nodeIsMeshThreeEnabled.append_child("meshThreeScale").append_attribute("value") = meshThreeScale;
					nodeIsMeshThreeEnabled.append_child("meshThreeRotationX").append_attribute("value") = meshThreeRotationX;
					nodeIsMeshThreeEnabled.append_child("meshThreeRotationY").append_attribute("value") = meshThreeRotationY;
					nodeIsMeshThreeEnabled.append_child("meshThreeRotationZ").append_attribute("value") = meshThreeRotationZ;

					nodeIsMeshThreeEnabled.append_child("meshThreePositionX").append_attribute("value") = meshThreePositionX;
					nodeIsMeshThreeEnabled.append_child("meshThreePositionY").append_attribute("value") = meshThreePositionY;
					nodeIsMeshThreeEnabled.append_child("meshThreePositionZ").append_attribute("value") = meshThreePositionZ;
			//nodeFunctionSetting.append_child("isFighterEnabled").append_attribute("value") = isFighterEnabled;
			nodeFunctionSetting.append_child("isTestSubjectSpinning").append_attribute("value") = isTestSubjectSpinning;
			nodeFunctionSetting.append_child("isAimmingAssistantEnabled").append_attribute("value") = isAimmingAssistantEnabled;
			//nodeFunctionSetting.append_child("isSimulating").append_attribute("value") = isSimulating;
			nodeFunctionSetting.append_child("isSingleFrameRenderingAndQuitMode").append_attribute("value") = isSingleFrameRenderingAndQuitMode;

			pugi::xml_node nodeIsLightField = nodeFunctionSetting.append_child("isLightField");
				nodeIsLightField.append_attribute("value") = isLightField;
					nodeIsLightField.append_child("virtualCameraPosR").append_attribute("value") = virtualCameraPosR;
					nodeIsLightField.append_child("virtualCameraPosH").append_attribute("value") = virtualCameraPosH;
					nodeIsLightField.append_child("virtualCameraPosTheta").append_attribute("value") = virtualCameraPosTheta;
					nodeIsLightField.append_child("virtualCameraFOV").append_attribute("value") = virtualCameraFOV;

		doc.save_file(xmlConfigFilePath);
	}
	else
	{
		widthOfRenderzoneByPixel = doc.child("Settings").child("displaySetting").child("widthOfRenderzoneByPixel").attribute("value").as_int();
		heightOfRenderzoneByPixel = doc.child("Settings").child("displaySetting").child("heightOfRenderzoneByPixel").attribute("value").as_int();
		isFullscreen = doc.child("Settings").child("displaySetting").child("isFullscreen").attribute("value").as_bool();
		widthOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("widthOfSubimageByPixel").attribute("value").as_int();
		heightOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("heightOfSubimageByPixel").attribute("value").as_int();

		xOffsetByPixel = doc.child("Settings").child("displaySetting").child("xOffsetByPixel").attribute("value").as_int();
		yOffsetByPixel = doc.child("Settings").child("displaySetting").child("yOffsetByPixel").attribute("value").as_int();

		//widthOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("widthOfSubimageBymm").attribute("value").as_double();
		//heightOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("heightOfSubimageBymm").attribute("value").as_double();

		// std::cout << " Loading XML widthOfSubimageBymm = " << widthOfSubimageBymm << "\n\n";

		widthOfRenderzoneBymm = doc.child("Settings").child("realworldSetting").child("widthOfRenderzoneBymm").attribute("value").as_double();
		heightOfRenderzoneBymm = doc.child("Settings").child("realworldSetting").child("heightOfRenderzoneBymm").attribute("value").as_double();

		// std::cout << " Loading XML widthOfRenderzoneBymm = " << widthOfRenderzoneBymm << "\n\n";
		
		thicknessOfTransparentMaterialBetweenDevices = doc.child("Settings").child("realworldSetting").child("thicknessOfTransparentMaterialBetweenDevices").attribute("value").as_double();
		refractionIndexOfTransparentMaterial = doc.child("Settings").child("realworldSetting").child("refractionIndexOfTransparentMaterial").attribute("value").as_double();

		backgroundColorR = doc.child("Settings").child("functionSetting").child("backgroundColorR").attribute("value").as_int();
		backgroundColorG = doc.child("Settings").child("functionSetting").child("backgroundColorG").attribute("value").as_int();
		backgroundColorB = doc.child("Settings").child("functionSetting").child("backgroundColorB").attribute("value").as_int();


		isAmbientLightEnabled = doc.child("Settings").child("functionSetting").child("isAmbientLightEnabled").attribute("value").as_bool();
		ambientLightR = doc.child("Settings").child("functionSetting").child("isAmbientLightEnabled").child("ambientLightR").attribute("value").as_float();
		ambientLightG = doc.child("Settings").child("functionSetting").child("isAmbientLightEnabled").child("ambientLightG").attribute("value").as_float();
		ambientLightB = doc.child("Settings").child("functionSetting").child("isAmbientLightEnabled").child("ambientLightB").attribute("value").as_float();

		isPointLightOneEnabled = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").attribute("value").as_bool();
		pointLightOnePositionX = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOnePositionX").attribute("value").as_float();
		pointLightOnePositionY = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOnePositionY").attribute("value").as_float();
		pointLightOnePositionZ = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOnePositionZ").attribute("value").as_float();
		pointLightOneR = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOneR").attribute("value").as_float();
		pointLightOneG = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOneG").attribute("value").as_float();
		pointLightOneB = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOneB").attribute("value").as_float();
		pointLightOneRange = doc.child("Settings").child("functionSetting").child("isPointLightOneEnabled").child("pointLightOneRange").attribute("value").as_float();

		isPointLightTwoEnabled = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").attribute("value").as_bool();
		pointLightTwoPositionX = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoPositionX").attribute("value").as_float();
		pointLightTwoPositionY = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoPositionY").attribute("value").as_float();
		pointLightTwoPositionZ = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoPositionZ").attribute("value").as_float();
		pointLightTwoR = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoR").attribute("value").as_float();
		pointLightTwoG = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoG").attribute("value").as_float();
		pointLightTwoB = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoB").attribute("value").as_float();
		pointLightTwoRange = doc.child("Settings").child("functionSetting").child("isPointLightTwoEnabled").child("pointLightTwoRange").attribute("value").as_float();


		isMeshOneEnabled = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").attribute("value").as_bool();
		meshOneModelPath = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOneModelPath").attribute("value").as_string();
		meshOneScale = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOneScale").attribute("value").as_float();		
		meshOneRotationX = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOneRotationX").attribute("value").as_float();
		meshOneRotationY = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOneRotationY").attribute("value").as_float();
		meshOneRotationZ = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOneRotationZ").attribute("value").as_float();
		meshOnePositionX = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOnePositionX").attribute("value").as_float();
		meshOnePositionY = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOnePositionY").attribute("value").as_float();
		meshOnePositionZ = doc.child("Settings").child("functionSetting").child("isMeshOneEnabled").child("meshOnePositionZ").attribute("value").as_float();

		isMeshTwoEnabled = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").attribute("value").as_bool();
		meshTwoModelPath = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoModelPath").attribute("value").as_string();
		meshTwoScale = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoScale").attribute("value").as_float();
		meshTwoRotationX = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoRotationX").attribute("value").as_float();
		meshTwoRotationY = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoRotationY").attribute("value").as_float();
		meshTwoRotationZ = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoRotationZ").attribute("value").as_float();
		meshTwoPositionX = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoPositionX").attribute("value").as_float();
		meshTwoPositionY = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoPositionY").attribute("value").as_float();
		meshTwoPositionZ = doc.child("Settings").child("functionSetting").child("isMeshTwoEnabled").child("meshTwoPositionZ").attribute("value").as_float();

		isMeshThreeEnabled = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").attribute("value").as_bool();
		meshThreeModelPath = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreeModelPath").attribute("value").as_string();
		meshThreeScale = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreeScale").attribute("value").as_float();
		meshThreeRotationX = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreeRotationX").attribute("value").as_float();
		meshThreeRotationY = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreeRotationY").attribute("value").as_float();
		meshThreeRotationZ = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreeRotationZ").attribute("value").as_float();
		meshThreePositionX = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreePositionX").attribute("value").as_float();
		meshThreePositionY = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreePositionY").attribute("value").as_float();
		meshThreePositionZ = doc.child("Settings").child("functionSetting").child("isMeshThreeEnabled").child("meshThreePositionZ").attribute("value").as_float();

		isTestSubjectSpinning = doc.child("Settings").child("functionSetting").child("isTestSubjectSpinning").attribute("value").as_bool();
		isAimmingAssistantEnabled = doc.child("Settings").child("functionSetting").child("isAimmingAssistantEnabled").attribute("value").as_bool();
		//isSimulating = doc.child("Settings").child("functionSetting").child("isSimulating").attribute("value").as_bool();
		isSingleFrameRenderingAndQuitMode = doc.child("Settings").child("functionSetting").child("isSingleFrameRenderingAndQuitMode").attribute("value").as_bool();
		
		isLightField = doc.child("Settings").child("functionSetting").child("isLightField").attribute("value").as_bool();
		virtualCameraPosR = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosR").attribute("value").as_float();
		virtualCameraPosH = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosH").attribute("value").as_float();
		virtualCameraPosTheta = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosTheta").attribute("value").as_float();
		virtualCameraFOV = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraFOV").attribute("value").as_float();

		heightOfProjectionPanelInScene = 2;
		widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfRenderzoneByPixel / heightOfRenderzoneByPixel;
		xSubimageCountMax = widthOfRenderzoneByPixel / widthOfSubimageByPixel;
		ySubimageCountMax = heightOfRenderzoneByPixel / heightOfSubimageByPixel;
		widthOfSubimageBymm = widthOfRenderzoneBymm*widthOfSubimageByPixel / widthOfRenderzoneByPixel;
		heightOfSubimageBymm = heightOfRenderzoneBymm*heightOfSubimageByPixel / heightOfRenderzoneByPixel;
	}
}
