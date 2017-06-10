#include "InitialParametres.h"
#include <iostream>

void InitialParametres::defaultValuesInitializing()
{
	widthOfRenderzoneByPixel = 3840/4;
	heightOfRenderzoneByPixel = 2160/4;
	isFullscreen = false;
	widthOfSubimageByPixel = 36;
	heightOfSubimageByPixel = 36;

	xOffsetByPixel = 0;
	yOffsetByPixel = 0;
	/*widthOfSubimageBymm = 5.6;
	heightOfSubimageBymm = 5.6;*/
	widthOfRenderzoneBymm = 597.0/4;
	heightOfRenderzoneBymm = 335.7/4;

	thicknessOfTransparentMaterialBetweenDevices = 3.0;
	refractionIndexOfTransparentMaterial = 1.208125;
	/*refractionIndexOfTransparentMaterial = 1.491756;*/
	//The data comes from the data sheet is 1.491756. Do not change it if unnecessary.
	backgroundColorR = 0;
	backgroundColorG = 0;
	backgroundColorB = 0;

	isMeshOneEnabled = true;
	meshOneModelPath = "../media/cube.dae";
	meshOneScale = 0.4;
	meshOneRotationX = 0;
	meshOneRotationY = 30;
	meshOneRotationZ = 0;
	meshOnePositionX = 0;
	meshOnePositionY = 0;
	meshOnePositionZ = 0.3;

	isMeshTwoEnabled = false;
	meshTwoModelPath = "../media/bun_zipper-blender.obj";
	meshTwoScale = 1;
	meshTwoRotationX = 0;
	meshTwoRotationY = 0;
	meshTwoRotationZ = 0;
	meshTwoPositionX = 0;
	meshTwoPositionY = -0.2;
	meshTwoPositionZ = 0.3;

	isMeshThreeEnabled = false;
	meshThreeModelPath = "../media/bun_zipper-blender.obj";
	meshThreeScale = 1;
	meshThreeRotationX = 0;
	meshThreeRotationY = 0;
	meshThreeRotationZ = 0;
	meshThreePositionX = 0;
	meshThreePositionY = -0.2;
	meshThreePositionZ = 0.3;

	isTestSubjectSpinning = false;
	isAimmingAssistantEnabled = false;
	//isSimulating = false;
	isSingleFrameRenderingAndQuitMode = false;

	isLightField = true;

	virtualCameraPosX = 0.0;
	virtualCameraPosY = 0.0;
	virtualCameraPosZ = -1500.0/4;
	virtualCameraFOV = 90.0;

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

			pugi::xml_node isAmbientLightEnabled = nodeFunctionSetting.append_child("isAmbientLightEnabled");
			isAmbientLightEnabled.append_attribute("value") = isAmbientLightEnabled;
			isAmbientLightEnabled.append_child("AmbientLightR").append_attribute("value") = ambientLightR;
			isAmbientLightEnabled.append_child("AmbientLightG").append_attribute("value") = ambientLightG;
			isAmbientLightEnabled.append_child("AmbientLightB").append_attribute("value") = ambientLightB;

			//isAmbientLightEnabled;
			//ambientLightR;
			//ambientLightG;
			//ambientLightB;

			// isPointLightOneEnabled;
			// pointLightOnePosistionX;
			// pointLightOnePosistionY;
			// pointLightOnePosistionZ;
			// pointLightOneR;
			// pointLightOneG;
			// pointLightOneB;

			// isPointLightTwoEnabled;
			// pointLightTwoPosistionX;
			// pointLightTwoPosistionY;
			// pointLightTwoPosistionZ;
			// pointLightTwoR;
			// pointLightTwoG;
			// pointLightTwoB;
			
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
					nodeIsLightField.append_child("virtualCameraPosX").append_attribute("value") = virtualCameraPosX;
					nodeIsLightField.append_child("virtualCameraPosY").append_attribute("value") = virtualCameraPosY;
					nodeIsLightField.append_child("virtualCameraPosZ").append_attribute("value") = virtualCameraPosZ;
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
		virtualCameraPosX = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosX").attribute("value").as_float();
		virtualCameraPosY = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosY").attribute("value").as_float();
		virtualCameraPosZ = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraPosZ").attribute("value").as_float();
		virtualCameraFOV = doc.child("Settings").child("functionSetting").child("isLightField").child("virtualCameraFOV").attribute("value").as_float();

		heightOfProjectionPanelInScene = 2;
		widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfRenderzoneByPixel / heightOfRenderzoneByPixel;
		xSubimageCountMax = widthOfRenderzoneByPixel / widthOfSubimageByPixel;
		ySubimageCountMax = heightOfRenderzoneByPixel / heightOfSubimageByPixel;
		widthOfSubimageBymm = widthOfRenderzoneBymm*widthOfSubimageByPixel / widthOfRenderzoneByPixel;
		heightOfSubimageBymm = heightOfRenderzoneBymm*heightOfSubimageByPixel / heightOfRenderzoneByPixel;
	}
}
