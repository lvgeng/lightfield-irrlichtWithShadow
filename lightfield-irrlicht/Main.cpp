#include <irrlicht.h>
#include <GL/freeglut.h>
#include "ObliqueMatrixList.h"
#include "InitialParametres.h"
#include "EventReceiverForKeyboard.h"
//#include "PlaneSimulator.h"


#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//This is the main method. We can now use main() on every platform.
void savetex(ITexture *texture, std::string filename, IVideoDriver* videoDriver) {
	video::IImage* image = videoDriver->createImageFromData(
		texture->getColorFormat(),
		texture->getSize(),
		texture->lock(irr::video::E_TEXTURE_LOCK_MODE::ETLM_READ_WRITE),
		true  //copy mem
		);
	videoDriver->writeImageToFile(image, path(filename.c_str()));
	texture->unlock();
}

int main()
{

	//The data use for initializing. It is static since there is no need to update after initializing.
	static InitialParametres *initialParametres = new InitialParametres("setting.xml");
	//The oblique projection matrix list. Only related to the projection configuration.
	static ObliqueMatrixList* obliqueMatrixList = new ObliqueMatrixList(
		initialParametres->widthOfProjectionPanelInScene,					//Width in scene. Relative.
		initialParametres->heightOfProjectionPanelInScene,					//Height in scene. Relative.
		initialParametres->widthOfSubimageByPixel,							//Width of the subimage. (pixel)
		initialParametres->heightOfSubimageByPixel,							//Height of the subimage. (pixel)
		initialParametres->widthOfSubimageBymm,								//Width of the subimage. (mm)
		initialParametres->heightOfSubimageBymm,							//Height of the subimage. (mm)
		initialParametres->widthOfRenderzoneBymm,
		initialParametres->heightOfRenderzoneBymm,
		initialParametres->thicknessOfTransparentMaterialBetweenDevices,	//Thickness of the transparent material between the light barriers and the screen. It will affect the result because of the refraction.
		initialParametres->refractionIndexOfTransparentMaterial				//Rafraction index of the transparent material.
		);

	IrrlichtDevice *device =
		createDevice(
			video::EDT_OPENGL,				//- deviceType: Type of the device. This can currently be the Null-device,one of the two software renderers, D3D8, D3D9, or OpenGL.In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
											//video::EDT_DIRECT3D9,
			dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel),
			//- windowSize: Size of the Window or screen in FullScreenMode to be created.
			16,								//- bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			initialParametres->isFullscreen,//- fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			true,							//- stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			true,							//- vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0								//- eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
			);


	device->setWindowCaption(L"Light field display");

	IVideoDriver* videoDriver = device->getVideoDriver();
	ISceneManager* sceneManager = device->getSceneManager();
	IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();


	//Preparing for the renderTarget.
	video::IRenderTarget* renderTargetAllSubimages = 0;
	video::ITexture* renderTargetTex = 0;
	renderTargetTex = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel), "RTT1", video::ECF_A8R8G8B8);
	video::ITexture* renderTargetDepth = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel), "DepthStencil", video::ECF_D24S8);
	renderTargetAllSubimages = videoDriver->addRenderTarget();
	renderTargetAllSubimages->setTexture(renderTargetTex, renderTargetDepth);

	video::IRenderTarget* renderTargetParallel = 0;

	video::ITexture* renderTargetTexParallel = 0;
	renderTargetTexParallel =
		videoDriver->addRenderTargetTexture(
			core::dimension2d<u32>(
				initialParametres->widthOfRenderzoneByPixel / initialParametres->widthOfSubimageByPixel + 1,
				initialParametres->heightOfRenderzoneByPixel / initialParametres->heightOfSubimageByPixel + 1),
			"RTT1", video::ECF_A8R8G8B8);
	video::ITexture* renderTargetDepthParallel =
		videoDriver->addRenderTargetTexture(
			core::dimension2d<u32>(
				initialParametres->widthOfRenderzoneByPixel / initialParametres->widthOfSubimageByPixel + 1,
				initialParametres->heightOfRenderzoneByPixel / initialParametres->heightOfSubimageByPixel + 1),
			"DepthStencil", video::ECF_D24S8);
	renderTargetParallel = videoDriver->addRenderTarget();
	renderTargetParallel->setTexture(renderTargetTexParallel, renderTargetDepthParallel);


	device->setEventReceiver(new EventReceiverForKeyboard(device, renderTargetTex));

	//Set shadow color.
	sceneManager->setShadowColor(video::SColor(150, 0, 0, 0));

	if (!device)
	{
		return 1;
	}

	//Set the caption of the window to some nice text. Note that there is an
	//'L' in front of the string. The Irrlicht Engine uses wide character
	//strings when displaying text.


	//===========================================================================================================================
	//===========================================================================================================================
	//===========================================================================================================================

	if (initialParametres->isMeshOneEnabled)
	{
		//char filepath[] = "../media/cube.dae";
		//IAnimatedMesh* mesh = sceneManager->getMesh(filepath);
		IAnimatedMesh* mesh = sceneManager->getMesh(initialParametres->meshOneModelPath.c_str());
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* meshOneModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (meshOneModel)
		{
			meshOneModel->setMaterialFlag(EMF_LIGHTING, true);
			meshOneModel->addShadowVolumeSceneNode();
			meshOneModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

			meshOneModel->setScale(vector3df(initialParametres->meshOneScale, initialParametres->meshOneScale, initialParametres->meshOneScale));
			meshOneModel->setRotation(vector3df(initialParametres->meshOneRotationX, initialParametres->meshOneRotationY, initialParametres->meshOneRotationZ));
			meshOneModel->setPosition(vector3df(initialParametres->meshOnePositionX, initialParametres->meshOnePositionY, initialParametres->meshOnePositionZ));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			meshOneModel->addAnimator(anim);
		}
	}

	if (initialParametres->isMeshTwoEnabled)
	{
		IAnimatedMesh* mesh = sceneManager->getMesh(initialParametres->meshTwoModelPath.c_str());
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* meshTwoModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (meshTwoModel)
		{
			meshTwoModel->setMaterialFlag(EMF_LIGHTING, true);
			meshTwoModel->addShadowVolumeSceneNode();
			meshTwoModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

			meshTwoModel->setScale(vector3df(initialParametres->meshTwoScale, initialParametres->meshTwoScale, initialParametres->meshTwoScale));
			meshTwoModel->setRotation(vector3df(initialParametres->meshTwoRotationX, initialParametres->meshTwoRotationY, initialParametres->meshTwoRotationZ));
			meshTwoModel->setPosition(vector3df(initialParametres->meshTwoPositionX, initialParametres->meshTwoPositionY, initialParametres->meshTwoPositionZ));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			meshTwoModel->addAnimator(anim);
		}
	}

	if (initialParametres->isMeshThreeEnabled)
	{
		IAnimatedMesh* mesh = sceneManager->getMesh(initialParametres->meshThreeModelPath.c_str());
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* meshThreeModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (meshThreeModel)
		{
			meshThreeModel->setMaterialFlag(EMF_LIGHTING, true);
			meshThreeModel->addShadowVolumeSceneNode();
			meshThreeModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

			meshThreeModel->setScale(vector3df(initialParametres->meshThreeScale, initialParametres->meshThreeScale, initialParametres->meshThreeScale));
			meshThreeModel->setRotation(vector3df(initialParametres->meshThreeRotationX, initialParametres->meshThreeRotationY, initialParametres->meshThreeRotationZ));
			meshThreeModel->setPosition(vector3df(initialParametres->meshThreePositionX, initialParametres->meshThreePositionY, initialParametres->meshThreePositionZ));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			meshThreeModel->addAnimator(anim);
		}
	}
	//If the light field mode is disabled, draw a frame to show the relative location of the objectes and the display.
	if (!initialParametres->isLightField)
	{
		scene::ISceneNode* nodeTopLine = sceneManager->addCubeSceneNode(1.0, 0, -1,
			core::vector3df(0, 1, 0),
			core::vector3df(0, 0, 0),
			core::vector3df((float)(initialParametres->widthOfRenderzoneByPixel) / (float)(initialParametres->heightOfRenderzoneByPixel) * 2, 0.01, 0.01));
		scene::ISceneNode* nodeBottomLine = sceneManager->addCubeSceneNode(1.0, 0, -1,
			core::vector3df(0, -1, 0),
			core::vector3df(0, 0, 0),
			core::vector3df((float)(initialParametres->widthOfRenderzoneByPixel) / (float)(initialParametres->heightOfRenderzoneByPixel) * 2, 0.01, 0.01));
		scene::ISceneNode* nodeLeftLine = sceneManager->addCubeSceneNode(1.0, 0, -1,
			core::vector3df(-(float)(initialParametres->widthOfRenderzoneByPixel) / (float)(initialParametres->heightOfRenderzoneByPixel), 0, 0),
			core::vector3df(0, 0, 0),
			core::vector3df(0.01, 2, 0.01));
		scene::ISceneNode* nodeRightLine = sceneManager->addCubeSceneNode(1.0, 0, -1,
			core::vector3df((float)(initialParametres->widthOfRenderzoneByPixel) / (float)(initialParametres->heightOfRenderzoneByPixel), 0, 0),
			core::vector3df(0, 0, 0),
			core::vector3df(0.01, 2, 0.01));

	}

	//Add a light source to make the cube visable.
	sceneManager->addLightSceneNode(0, core::vector3df(-80, 100, -150), video::SColorf(0.5f, 0.5f, 0.5f), 500);
	sceneManager->setAmbientLight(video::SColorf(0.5f, 0.5f, 0.5f));

	//Setting the Affector and the testData will change the render parametres.
	matrix4* viewProjectionMatrixAffector = new matrix4();
	viewProjectionMatrixAffector->buildCameraLookAtMatrixLH(vector3df(0, 0, 0), vector3df(0, 0, 10), vector3df(0, 1, 0));

	ICameraSceneNode* currentCamera = sceneManager->addCameraSceneNode();

	if (initialParametres->isLightField)
	{
		// currentCamera->setViewMatrixAffector(*viewProjectionMatrixAffector);
		currentCamera->setViewMatrixAffector(*obliqueMatrixList->getViewMatrixByPixel(0, 0));
		currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(0, 0), true);
	}
	else
	{
		//matrix4* viewMatrixAffector = new matrix4();
		//matrix4* projectionMatrixAffector = new matrix4();
		//viewMatrixAffector->buildCameraLookAtMatrixLH(vector3df(0, 0, 0), vector3df(0, 0, 10), vector3df(0, 1, 0));
		//projectionMatrixAffector->buildProjectionMatrixPerspectiveFovLH(
		//	PI*initialParametres->virtualCameraFOV / 180,
		//	(float)(initialParametres->widthOfRenderzoneByPixel)/(float)(initialParametres->heightOfRenderzoneByPixel),
		//	0,
		//	1000
		//	);
		//
		//currentCamera->setProjectionMatrix();

		currentCamera->setPosition(
			core::vector3df(
				initialParametres->virtualCameraPosX / initialParametres->heightOfRenderzoneBymm * 2,
				initialParametres->virtualCameraPosY / initialParametres->heightOfRenderzoneBymm * 2,
				initialParametres->virtualCameraPosZ / initialParametres->heightOfRenderzoneBymm * 2
				)
			);
		currentCamera->setFOV(PI*initialParametres->virtualCameraFOV / 180);
		currentCamera->setUpVector(core::vector3df(0, 1, 0));
		currentCamera->setTarget(core::vector3df(0, 0, 0));
		currentCamera->setAspectRatio((float)(initialParametres->widthOfRenderzoneByPixel) / (float)(initialParametres->heightOfRenderzoneByPixel));
	}


	//===========================================================================================================================
	//===========================================================================================================================
	//===========================================================================================================================


	while (device->run())
	{
		//Update the stencil buffer to prepare for next step===================================================================================================
		
		if (initialParametres->isLightField)
		{
			videoDriver->setRenderTargetEx(renderTargetAllSubimages,
				video::ECBF_COLOR | video::ECBF_DEPTH,
				SColor(255,
					initialParametres->backgroundColorR,
					initialParametres->backgroundColorG,
					initialParametres->backgroundColorB));
			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, initialParametres->backgroundColorR, initialParametres->backgroundColorG, initialParametres->backgroundColorB));//If it is SColor(0), the background will be transparent
			
			/*videoDriver->setRenderTargetEx(renderTargetAllSubimages, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, initialParametres->backgroundColorR, initialParametres->backgroundColorG, initialParametres->backgroundColorB));*/
			
			int xCountMax = initialParametres->widthOfRenderzoneByPixel / initialParametres->widthOfSubimageByPixel;
			int yCountMax = initialParametres->heightOfRenderzoneByPixel / initialParametres->heightOfSubimageByPixel;

			for (int xInSubimageByPixel = 0; xInSubimageByPixel < initialParametres->widthOfSubimageByPixel; xInSubimageByPixel++)
			{
				for (int yInSubimageByPixel = 0; yInSubimageByPixel < initialParametres->heightOfSubimageByPixel; yInSubimageByPixel++)
				{
			
					currentCamera->setViewMatrixAffector(*obliqueMatrixList->getViewMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel));
					currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
					currentCamera->setPosition(//Position should be a key factor that affecting the performance
						core::vector3df(
							((float)xInSubimageByPixel - (float)(initialParametres->widthOfSubimageByPixel) / 2) / ((float)(initialParametres->heightOfRenderzoneByPixel) / 2),
							((float)(initialParametres->heightOfSubimageByPixel) / 2 - (float)yInSubimageByPixel) / ((float)(initialParametres->heightOfRenderzoneByPixel) / 2),
							0
							)
						);

					//Set rendering target
					videoDriver->setRenderTargetEx(renderTargetParallel, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, initialParametres->backgroundColorR, initialParametres->backgroundColorG, initialParametres->backgroundColorB));
					sceneManager->drawAll();			
					
					videoDriver->setRenderTargetEx(renderTargetAllSubimages,
						video::ECBF_DEPTH,
						//video::ECBF_COLOR | video::ECBF_DEPTH,
						SColor(255,
							initialParametres->backgroundColorR,
							initialParametres->backgroundColorG,
							initialParametres->backgroundColorB));
					for (int xSubimageCount = 0; xSubimageCount < initialParametres->xSubimageCountMax; xSubimageCount++)
					{
						for (int ySubimageCount = 0; ySubimageCount < initialParametres->ySubimageCountMax; ySubimageCount++)
						{


							videoDriver->draw2DImage(renderTargetTexParallel,
								//core::position2d<s32>(xInSubimageByPixel*10, yInSubimageByPixel*10),
								core::position2d<s32>(
									(initialParametres->widthOfSubimageByPixel) * xSubimageCount + xInSubimageByPixel,
									(initialParametres->heightOfSubimageByPixel) * ySubimageCount + yInSubimageByPixel),

								core::rect<s32>(
									xSubimageCount,
									ySubimageCount,
									xSubimageCount+1,
									ySubimageCount+1
									),
								0,
								video::SColor(255,
									255 - initialParametres->backgroundColorR,
									255 - initialParametres->backgroundColorG,
									255 - initialParametres->backgroundColorB), true);

						}
					}


					//Render the parellel views to the entire elemental image array
					//videoDriver->setRenderTargetEx(renderTargetAllSubimages,
					//	video::ECBF_COLOR | video::ECBF_DEPTH,
					//	SColor(255,
					//		initialParametres->backgroundColorR,
					//		initialParametres->backgroundColorG,
					//		initialParametres->backgroundColorB));

					//videoDriver->draw2DImage(renderTargetTexParallel, core::position2d<s32>(0, 0),
					//	/*videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(0, 0),*/
					//	core::rect<s32>(
					//		0,
					//		0,
					//		initialParametres->heightOfRenderzoneByPixel / initialParametres->heightOfSubimageByPixel,
					//		initialParametres->heightOfRenderzoneByPixel / initialParametres->heightOfSubimageByPixel
					//		),
					//	0,
					//	video::SColor(255,
					//		255 - initialParametres->backgroundColorR,
					//		255 - initialParametres->backgroundColorG,
					//		255 - initialParametres->backgroundColorB), true);



					//currentCamera->setViewMatrixAffector(*obliqueMatrixList->getViewMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel));
					//currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
					//sceneManager->drawAll();
				}
			}
			videoDriver->endScene();
		}
		else
		{
			//glDisable(GL_STENCIL_TEST);

			//currentCamera->setPosition(core::vector3df(initialParametres->virtualCameraPosX, initialParametres->virtualCameraPosY, initialParametres->virtualCameraPosZ));
			//currentCamera->setFOV(PI*initialParametres->virtualCameraFOV/180);
			//currentCamera->setUpVector(core::vector3df(0, 1, 0));
			//currentCamera->setTarget(core::vector3df(0, 0, 0));

			//currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, initialParametres->backgroundColorR, initialParametres->backgroundColorG, initialParametres->backgroundColorB));//If it is SColor(0), the background will be transparent
			videoDriver->setRenderTargetEx(renderTargetAllSubimages, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, initialParametres->backgroundColorR, initialParametres->backgroundColorG, initialParametres->backgroundColorB));
			sceneManager->drawAll();

			videoDriver->endScene();

		}
		//===================================================================================================
		//glDisable(GL_STENCIL_TEST);
		//===================================================================================================
		if (initialParametres->isAimmingAssistantEnabled)
		{
			for (int leftToRightCount = 0; leftToRightCount < initialParametres->xSubimageCountMax; leftToRightCount++)
			{
				videoDriver->draw2DRectangle(
					SColor(255, 0, 0, 0),
					core::rect<s32>(
						leftToRightCount * initialParametres->widthOfSubimageByPixel,
						0,
						(leftToRightCount + 1) * initialParametres->widthOfSubimageByPixel,
						initialParametres->heightOfSubimageByPixel
						)
					);
				videoDriver->draw2DRectangle(
					SColor(255, 0, 0, 0),
					core::rect<s32>(
						leftToRightCount * initialParametres->widthOfSubimageByPixel,
						(initialParametres->ySubimageCountMax) * initialParametres->heightOfSubimageByPixel,
						(leftToRightCount + 1) * initialParametres->widthOfSubimageByPixel,
						(initialParametres->ySubimageCountMax + 1) * initialParametres->heightOfSubimageByPixel
						)
					);

				if (initialParametres->widthOfSubimageByPixel % 2 == 0)
				{
					videoDriver->draw2DRectangle(
						SColor(255, 255, 255, 255),
						core::rect<s32>(
							(leftToRightCount + 0.5 - 0.05) * initialParametres->widthOfSubimageByPixel,
							(0.5 - 0.05) * initialParametres->heightOfSubimageByPixel,
							(leftToRightCount + 0.5 + 0.0) * initialParametres->widthOfSubimageByPixel,
							(0.5 + 0.0) * initialParametres->heightOfSubimageByPixel
							)
						);
					videoDriver->draw2DRectangle(
						SColor(255, 255, 255, 255),
						core::rect<s32>(
							(leftToRightCount + 0.5 - 0.05) * initialParametres->widthOfSubimageByPixel,
							(initialParametres->ySubimageCountMax - 0.5 - 0.05) * initialParametres->heightOfSubimageByPixel,
							(leftToRightCount + 0.5 + 0.0) * initialParametres->widthOfSubimageByPixel,
							(initialParametres->ySubimageCountMax - 0.5 + 0.0) * initialParametres->heightOfSubimageByPixel
							)
						);
				}
				else
				{
					videoDriver->draw2DRectangle(
						SColor(255, 255, 255, 255),
						core::rect<s32>(
							(leftToRightCount + 0.5 - 0.05) * initialParametres->widthOfSubimageByPixel + 1,
							(0.5 - 0.05) * initialParametres->heightOfSubimageByPixel + 1,
							(leftToRightCount + 0.5 + 0.05) * initialParametres->widthOfSubimageByPixel,
							(0.5 + 0.05) * initialParametres->heightOfSubimageByPixel
							)
						);
					videoDriver->draw2DRectangle(
						SColor(255, 255, 255, 255),
						core::rect<s32>(
							(leftToRightCount + 0.5 - 0.05) * initialParametres->widthOfSubimageByPixel + 1,
							(initialParametres->ySubimageCountMax + 0.5 - 0.05) * initialParametres->heightOfSubimageByPixel + 1,
							(leftToRightCount + 0.5 + 0.05) * initialParametres->widthOfSubimageByPixel,
							(initialParametres->ySubimageCountMax + 0.5 + 0.05) * initialParametres->heightOfSubimageByPixel
							)
						);
				}

			}
		}
		//===================================================================================================
		//===================================================================================================
		videoDriver->setRenderTargetEx(0, 0, SColor(0));

		//Draw the rendered texture to the screen
		videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(initialParametres->xOffsetByPixel, initialParametres->yOffsetByPixel),
			/*videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(0, 0),*/
			core::rect<s32>(
				0,
				0,
				initialParametres->widthOfRenderzoneByPixel,
				initialParametres->heightOfRenderzoneByPixel
				),
			0,
			video::SColor(255,
				255 - initialParametres->backgroundColorR,
				255 - initialParametres->backgroundColorG,
				255 - initialParametres->backgroundColorB), true);

		//Save the rendering result to a png file.
		if (initialParametres->isSingleFrameRenderingAndQuitMode)
		{
			video::IRenderTarget* renderTargetToSave = 0;
			video::ITexture* renderTargetTexToSave = 0;
			//scene::ICameraSceneNode* fixedCam = 0;
			renderTargetTexToSave =
				videoDriver->addRenderTargetTexture(
					core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel),
					"RTT1", video::ECF_A8R8G8B8);
			video::ITexture* renderTargetDepthToSave =
				videoDriver->addRenderTargetTexture(
					core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel),
					"DepthStencil", video::ECF_D24S8);

			renderTargetToSave = videoDriver->addRenderTarget();
			renderTargetToSave->setTexture(renderTargetTexToSave, renderTargetDepthToSave);

			videoDriver->setRenderTargetEx(renderTargetToSave,
				video::ECBF_COLOR | video::ECBF_DEPTH,
				SColor(255,
					initialParametres->backgroundColorR,
					initialParametres->backgroundColorG,
					initialParametres->backgroundColorB));

			videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(initialParametres->xOffsetByPixel, initialParametres->yOffsetByPixel),
			//videoDriver->draw2DImage(renderTargetTexParallel, core::position2d<s32>(initialParametres->xOffsetByPixel, initialParametres->yOffsetByPixel),
				/*videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(0, 0),*/
				core::rect<s32>(
					0,
					0,
					initialParametres->widthOfRenderzoneByPixel - initialParametres->xOffsetByPixel,
					initialParametres->heightOfRenderzoneByPixel - initialParametres->yOffsetByPixel
					),
				0,
				video::SColor(255,
					255 - initialParametres->backgroundColorR,
					255 - initialParametres->backgroundColorG,
					255 - initialParametres->backgroundColorB), true);

			std::string filename = "SFR";
			if (initialParametres->isLightField) filename += "-LF";
			filename += "-" + to_string(initialParametres->widthOfRenderzoneByPixel) + "-" + to_string(initialParametres->heightOfRenderzoneByPixel);
			filename += "-Elemental-" + to_string(initialParametres->widthOfSubimageByPixel) + "-" + to_string(initialParametres->heightOfSubimageByPixel);
			if (initialParametres->isMeshOneEnabled)
			{
				filename += "-1";
			}
			else
			{
				filename += "-0";
			}
			if (initialParametres->isMeshTwoEnabled)
			{
				filename += "1";
			}
			else
			{
				filename += "0";
			}
			if (initialParametres->isMeshThreeEnabled)
			{
				filename += "1";
			}
			else
			{
				filename += "0";
			}

			filename += ".png";
			savetex(renderTargetTexToSave, filename, videoDriver);
			break;
		}

		//glEnable(GL_STENCIL_TEST);
		videoDriver->endScene();
	}
	//=================================================================================
	//=================================================================================
	//=================================================================================


	//End by deleting the device.
	device->drop();
	return 0;
}
